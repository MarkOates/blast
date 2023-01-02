#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile


#include <Blast/Build/Celebrator.hpp>
#include <Blast/StringJoiner.hpp>
#include <Blast/CommandLineFlaggedArgumentsParser.hpp>
#include <iostream>
#include <stdlib.h> // for atoi

namespace AllegroFlare
{
   // thsee should probably be moved to string constants
#define CONSOLE_COLOR_RED "\033[1;31m"
#define CONSOLE_COLOR_YELLOW "\033[1;33m"
#define CONSOLE_COLOR_GREEN "\033[1;32m"
#define CONSOLE_COLOR_DEFAULT "\033[0m"
}


using Blast::CommandLineFlaggedArgumentsParser;


int main(int argc, char **argv)
{
   std::vector<std::string> raw_args;
   for (int i=0; i<argc; i++) raw_args.push_back(argv[i]);
   CommandLineFlaggedArgumentsParser args(raw_args);


   // extract shared params

   // "length"

   int length = 80;
   if (args.has_flag("-l"))
   {
      std::vector<std::vector<std::string>> number = args.get_flagged_args("-l");
      length = atoi(number[0][0].c_str());
   }


   // "color"

   std::string color_string = "";
   std::string closing_color_string = "";
   if (args.has_flag("-c"))
   {
      std::vector<std::vector<std::string>> number = args.get_flagged_args("-c");
      std::string color_arg = number[0][0].c_str();
      if (color_arg == "yellow")
      {
         color_string = CONSOLE_COLOR_YELLOW;
         closing_color_string = CONSOLE_COLOR_DEFAULT;
      }
   }


   if (args.has_flag("-m"))
   {
      std::string message = "";
      auto first_set = args.get_flagged_args("-m")[0];
      message = Blast::StringJoiner(first_set, " ").join();
      Blast::Build::Celebrator celebrator;
      std::cout
         << color_string
         << celebrator.generate_full_width_output_banner(message, length)
         << closing_color_string
         << std::endl;
   }
   else if (args.has_flag("-P"))
   {
      //std::string message = "";
      //auto first_set = args.get_flagged_args("-m")[0];
      //message = Blast::StringJoiner(first_set, " ").join();
      Blast::Build::Celebrator celebrator;
      std::cout
         << celebrator.generate_pass_banner(length)
         << std::endl;
   }
   else
   {
      throw std::runtime_error("you must pass a message behind a \"-m\" flag.");
   }

   return 0;
}
