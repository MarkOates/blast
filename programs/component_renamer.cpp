#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile
#include <iostream>
#include <vector>
#include <string>


#include <Blast/Quintessence/ComponentGenerator.hpp>


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
you need to execute the steps yourself. Be sure that you are running the command(s) from within
the project where you want to rename the component.  Make sure your working tree is clean in case
something goes wrong and you need to reset.  For help with the process, view Hexagon's
documentation "Proceedure for Renaming a Component":

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
   if (args.size() != 2)
   {
      std::cout << build_help_error_message();
      return 1;
   }

   current_component_name = args[0];
   new_component_name = args[1];

   ComponentGenerator current_component_generator(current_component_name);
   ComponentGenerator new_component_generator(new_component_name);

   std::cout << std::endl;
   std::cout << "You are replacing \"" << current_component_name << "\" with \"" << new_component_name << "\"" << std::endl;
   std::cout << std::endl;

   // rename the symbols
   std::string current_symbol_name = current_component_generator.get_program_body_class_name();
   std::string new_symbol_name = new_component_generator.get_program_body_class_name();
   std::cout << "Replace the symbol recursively in all git-tracked files:" << std::endl;
   std::cout << "========================================================" << std::endl;
   std::cout << std::endl;
   //std::cout << "git grep -lz 'Wicked::Zones::Base3D' | xargs -0 perl -i'' -pE \"s/Wicked::Zones::Base3D/Wicked::Entities::Zones::Base3D/g\"" << std::endl;
   std::cout << "$ git grep -lz '" << current_symbol_name << "' | xargs -0 perl -i'' -pE \"s/" << current_symbol_name << "/" << new_symbol_name << "/g\"" << std::endl;

   return 0;
}


