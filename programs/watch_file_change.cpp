#include <iostream>
#include <filesystem>
#include <chrono>
#include <thread>
#include <functional>
#include <allegro5/allegro.h>


#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/String/Trimmer.hpp>



#include <filesystem>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <sstream>


std::string timestamp_now()
{
   std::stringstream result;
   auto end = std::chrono::system_clock::now();
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);
   result << std::ctime(&end_time);
   return Blast::String::Trimmer(result.str()).trim();
}





namespace fs = std::filesystem;

void watch_file(const fs::path &file_path,
                std::function<void()> callback,
                std::chrono::milliseconds interval = std::chrono::milliseconds(3000))
{
   if (!fs::exists(file_path))
   {
      std::cerr << "File does not exist: " << file_path << "\n";
      return;
   }

   auto last_write_time = fs::last_write_time(file_path);

   while (true)
   {
      std::cout << "watching " << file_path << " at " << timestamp_now() << std::endl;
      std::this_thread::sleep_for(interval);

      auto current_write_time = fs::last_write_time(file_path);

      if (current_write_time != last_write_time)
      {
         last_write_time = current_write_time;
         callback();
      }
   }
}



// Note this PSD->PNG conversion command does not respect photoshop's blending modes.
// For now, layers with different blending modes are simply disabled in the source file.
// For alternative approach, ChatGPT recommends using Photoshop in headless mode. see:
// https://chatgpt.com/c/681220e3-b61c-800f-8036-d26d0f0e7231
//

int main(int argc, char** argv)
{
   std::string file_to_watch = "/Users/markoates/Desktop/odeya/odeya_composite_tileset-0x.psd";

   watch_file(file_to_watch, []()
   {
      std::cout << "File changed!" << std::endl;

      {
         Blast::ShellCommandExecutorWithCallback command(
               "magick /Users/markoates/Desktop/odeya/odeya_composite_tileset-0x.psd "
               "-background none -flatten "
               "/Users/markoates/Desktop/odeya/odeya_composite_tileset-0x.png"
            );
         command.execute();
         if (command.get_executed_successfully())
         {
            std::cout << "  - Conversion command 1 appears to have executed successfully" << std::endl;
         }
      }

      {
         Blast::ShellCommandExecutorWithCallback command(
               "magick /Users/markoates/Desktop/odeya/odeya_composite_tileset-0x.psd "
               "-background none -flatten "
               "/Users/markoates/Repos/Atratus/bin/data/bitmaps/odeya_composite_tileset-0x.png"
            );
         command.execute();
         if (command.get_executed_successfully())
         {
            std::cout << "  - Conversion command 2 appears to have executed successfully" << std::endl;
         }
      }

   });

   return 0;
}


