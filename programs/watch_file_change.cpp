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
   std::this_thread::sleep_for(interval);

   while (true)
   {
      std::cout << "Checking " << file_path << " at " << timestamp_now();

      auto current_write_time = fs::last_write_time(file_path);

      if (current_write_time != last_write_time)
      {
         std::cout << " - FILE CHANGE DETECTED." << std::endl;
         last_write_time = current_write_time;
         callback();
      }
      else
      {
         std::cout << " (no change found)." << std::endl;
      }


      std::this_thread::sleep_for(interval);
   }
}



// Note this PSD->PNG conversion command does not respect photoshop's blending modes.
// For now, layers with different blending modes are simply disabled in the source file.
// For alternative approach, ChatGPT recommends using Photoshop in headless mode. see:
// https://chatgpt.com/c/681220e3-b61c-800f-8036-d26d0f0e7231
//

int main(int argc, char** argv)
{
   /*
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
   */

   std::string file_to_watch = "/Users/markoates/Desktop/hello_friend-environment-0n.obj";

   watch_file(file_to_watch, []()
   {
      std::cout << "File changed!" << std::endl;

      {
         Blast::ShellCommandExecutorWithCallback command(
               "cp "
               "/Users/markoates/Desktop/hello_friend-environment-0n.obj "
               "/Users/markoates/Repos/TINS2025/tests/fixtures/models/hello_friend-environment-0n.obj"
            );
         command.execute();
         if (command.get_executed_successfully())
         {
            std::cout << "  - Command 1 executed successfully" << std::endl;
         }
      }
      
      {
         Blast::ShellCommandExecutorWithCallback command(
               "cp "
               "/Users/markoates/Desktop/hello_friend-environment-0n.obj "
               "/Users/markoates/Repos/TINS2025/bin/data/models/hello_friend-environment-0n.obj"
            );
         command.execute();
         if (command.get_executed_successfully())
         {
            std::cout << "  - Command 2 executed successfully" << std::endl;
         }
      }

      {
         Blast::ShellCommandExecutorWithCallback command(
               "cp "
               "/Users/markoates/Desktop/Textures/hello_friend-environment-0n.png "
               "/Users/markoates/Repos/TINS2025/tests/fixtures/bitmaps/hello_friend-environment-0n.png"
            );
         command.execute();
         if (command.get_executed_successfully())
         {
            std::cout << "  - Command 1 executed successfully" << std::endl;
         }
      }
      
      {
         Blast::ShellCommandExecutorWithCallback command(
               "cp "
               "/Users/markoates/Desktop/Textures/hello_friend-environment-0n.png "
               "/Users/markoates/Repos/TINS2025/bin/data/bitmaps/hello_friend-environment-0n.png"
            );
         command.execute();
         if (command.get_executed_successfully())
         {
            std::cout << "  - Command 2 executed successfully" << std::endl;
         }
      }

   });

   return 0;
}


