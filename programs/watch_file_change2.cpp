#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <functional>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

#include <allegro5/allegro.h> // To prevent mangled main

#include <lib/nlohmann/json.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/String/Trimmer.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

struct WatchTask
{
   std::string file_path;
   std::vector<std::string> commands;
   std::chrono::milliseconds interval;
};

// Helper function to replace all occurrences of a substring.
std::string replace_all(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

std::string timestamp_now()
{
   auto now = std::chrono::system_clock::now();
   std::time_t now_time = std::chrono::system_clock::to_time_t(now);
   std::string time_str = std::ctime(&now_time);
   return Blast::String::Trimmer(time_str).trim();
}

void watch_file(const WatchTask& task)
{
   fs::path file_path(task.file_path);

   if (!fs::exists(file_path))
   {
      std::cerr << "Error: File to watch does not exist: " << file_path << "\n";
      return;
   }

   auto last_write_time = fs::last_write_time(file_path);
   std::this_thread::sleep_for(task.interval);

   while (true)
   {
      std::cout << "Checking \"" << file_path.filename().string() << "\" at " << timestamp_now();

      if (!fs::exists(file_path))
      {
         std::cout << " - FILE GONE." << std::endl;
         break;
      }

      auto current_write_time = fs::last_write_time(file_path);

      if (current_write_time != last_write_time)
      {
         std::cout << " - FILE CHANGE DETECTED." << std::endl;
         last_write_time = current_write_time;

         for (const auto& command_template : task.commands)
         {
            // Use the standard library helper function for replacement
            std::string command = replace_all(command_template, "%FILE%", task.file_path);
            Blast::ShellCommandExecutorWithCallback executor(command);
            executor.execute();
            if (executor.get_executed_successfully())
            {
               std::cout << "  - Executed: \"" << command << "\"" << std::endl;
            }
         }
      }
      else
      {
         std::cout << " (no change)." << std::endl;
      }

      std::this_thread::sleep_for(task.interval);
   }
}

std::vector<WatchTask> load_tasks_from_json(const std::string& json_path)
{
   std::vector<WatchTask> tasks;
   std::ifstream f(json_path);

   if (!f.is_open())
   {
      std::cerr << "Failed to open config file: " << json_path << std::endl;
      return tasks;
   }

   try
   {
      json data = json::parse(f);
      for (const auto& item : data["tasks"])
      {
         WatchTask task;
         task.file_path = item.at("file").get<std::string>();
         task.commands = item.at("commands").get<std::vector<std::string>>();
         task.interval = std::chrono::milliseconds(item.value("interval_ms", 1000));
         tasks.push_back(task);
      }
   }
   catch (json::exception& e)
   {
      std::cerr << "JSON parsing error: " << e.what() << '\n';
   }

   return tasks;
}

int main(int argc, char** argv)
{
   if (argc < 2)
   {
      std::cerr << "Usage: " << argv[0] << " <config.json>" << std::endl;
      return 1;
   }

   std::vector<WatchTask> tasks = load_tasks_from_json(argv[1]);
   if (tasks.empty())
   {
      std::cerr << "No valid tasks found in the configuration file." << std::endl;
      return 1;
   }

   std::vector<std::thread> watchers;
   for (const auto& task : tasks)
   {
      watchers.emplace_back(watch_file, task);
   }

   for (auto& watcher : watchers)
   {
      if (watcher.joinable())
      {
         watcher.join();
      }
   }

   return 0;
}
