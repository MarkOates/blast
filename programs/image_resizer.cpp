#include <allegro5/allegro.h>
#include <Blast/ShellCommandExecutorWithCallback.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>


int main(int argc, char** argv)
{
   if (argc < 2)
   {
      std::cout << "Usage: image_resizer <filename>" << std::endl;
      return 1;
   }

   std::string filename = argv[1];

   if (!std::filesystem::exists(filename))
   {
      throw std::runtime_error("The file \"" + filename + "\" does not exist.");
   }

   std::string command = "magick \"" + filename + "\" -resize 1920x1080 -filter Lanczos -define filter:blur=0.75 \"/Users/markoates/Desktop/screenshot_output_1920x1080.png\"";

   std::cout << "============== command begin ===============" << std::endl;
   std::cout << command << std::endl;
   std::cout << "============== command end ===============" << std::endl;

   Blast::ShellCommandExecutorWithCallback executor(command);

   std::cout << "============== execution begin ===============" << std::endl;
   executor.execute();
   std::cout << "============== execution end ===============" << std::endl;

   return 0;
}

