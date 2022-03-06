#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile
#include <iostream>
#include <vector>
#include <string>


std::string build_help_error_message()
{
   return R"(
ERROR: You must pass two arguments, 1) a component name, and 2) the new name for the component.

Example Usage:
==============

$ rename_component Wicked/Zones/Base2D Wicked/Entities/Zones/Base2D


Important:
==========

Note that this is a very dangerous proceedure and can easily mangle your codebase if not done
properly. Running this program will NOT execute any side effects, but will provide the commands
you need to execute the steps yourself. For help with the process, view Hexagon's documentation
under "Proceedure for Renaming a Component":

https://github.com/MarkOates/hexagon/blob/master/documentation/rename_component_proceedure.md

   )";
};


int main(int argc, char **argv)
{
   std::vector<std::string> args;
   std::string current_component_name = "";
   std::string new_component_name = "";

   // parse the args into args
   for (int i=1; i<argc; i++) args.push_back(argv[i]);

   // validate invalid number of args
   if (args.size() != 2) { std::cout << build_help_error_message(); return 1; }

   return 0;
}
