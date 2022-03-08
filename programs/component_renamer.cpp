#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile
#include <iostream>
#include <vector>
#include <string>


#include <Blast/Quintessence/ComponentGenerator.hpp>


static void ___replace(std::string& str, std::string from, std::string to)
{
   //static const std::string from = "\t";
   //static const std::string to = std::string(3, ' ');

   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
}


std::string build_important_message()
{
   return R"(
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
}


std::string build_help_error_message()
{
   return R"(
ERROR: You must pass two arguments, 1) a component name, and 2) the new name for the component.

Example Usage:
==============

$ rename_component Wicked/Zones/Base2D Wicked/Entities/Zones/Base2D


)" + build_important_message();
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

   // TODO: assert there are only the expected characters in the input, e.g. [A-Za-z_0-9/]

   current_component_name = args[0];
   new_component_name = args[1];

   ComponentGenerator current_component_generator(current_component_name);
   ComponentGenerator new_component_generator(new_component_name);

   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << "============================" << std::endl;
   std::cout << "====  COMPONENT RENAMER ====" << std::endl;
   std::cout << "============================" << std::endl;
   std::cout << std::endl;
   std::cout << "NOTE:" << std::endl;
   std::cout << "=====" << std::endl;
   std::cout << "You are replacing \"" << current_component_name << "\" with \"" << new_component_name << "\"" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << build_important_message();
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;

   // remove the generated header and source files
   std::string quintessence_filename = current_component_generator.get_quintessence_path_and_filename();
   std::string header_filename = current_component_generator.get_header_path_and_filename();
   std::string source_filename = current_component_generator.get_source_path_and_filename();
   std::cout << "COMMAND: Remove the generated header and source files:" << std::endl;
   std::cout << "======================================================" << std::endl;
   std::cout << std::endl;
   std::cout
      << "if [[ -f \"" << quintessence_filename << "\" ]]; then" << std::endl
      << "   rm \"" << header_filename << "\"" << std::endl
      << "   rm \"" << source_filename << "\"" << std::endl
      << "fi" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;

   // move the fragments to the new locations, (or rename them or whatever)
   std::string current_quintessence_filename = current_component_generator.get_quintessence_path_and_filename();
   std::string current_header_filename = current_component_generator.get_header_path_and_filename();
   std::string current_source_filename = current_component_generator.get_source_path_and_filename();
   std::string current_test_filename = current_component_generator.get_test_path_and_filename();
   std::string current_documentation_filename = current_component_generator.get_documentation_path_and_filename();
   std::string new_quintessence_filename = new_component_generator.get_quintessence_path_and_filename();
   std::string new_header_filename = new_component_generator.get_header_path_and_filename();
   std::string new_source_filename = new_component_generator.get_source_path_and_filename();
   std::string new_test_filename = new_component_generator.get_test_path_and_filename();
   std::string new_documentation_filename = new_component_generator.get_documentation_path_and_filename();
   std::cout << "COMMAND: Move the files to the new locations:" << std::endl;
   std::cout << "=============================================" << std::endl;
   std::cout << std::endl;
   std::cout
      << "mv \"" << current_quintessence_filename << "\" \"" << new_quintessence_filename << "\"" << std::endl
      << "mv \"" << current_test_filename << "\" \"" << new_test_filename << "\"" << std::endl
      << "mv \"" << current_documentation_filename << "\" \"" << new_documentation_filename << "\"" << std::endl
      << "mv \"" << current_header_filename << "\" \"" << new_header_filename << "\"" << std::endl
      << "mv \"" << current_source_filename << "\" \"" << new_source_filename << "\"" << std::endl
      ;
   std::cout << std::endl;
   std::cout << std::endl;

   // rename the symbols
   // example:
   // std::cout << "git grep -lz 'Wicked::Zones::Base3D' | xargs -0 perl -i'' -pE \"s/Wicked::Zones::Base3D/Wicked::Entities::Zones::Base3D/g\"" << std::endl;
   //std::string current_symbol_name = current_component_generator.get_program_body_class_name();
   //std::string new_symbol_name = new_component_generator.get_program_body_class_name();
   std::cout << "COMMAND: Add all the updated file locations to the git working tree (so \"git grep\" can work):" << std::endl;
   std::cout << "===============================================================================================" << std::endl;
   std::cout << std::endl;
   std::cout
      << "git add \"" << new_quintessence_filename << "\"" << std::endl
      << "git add \"" << new_test_filename << "\"" << std::endl
      << "git add \"" << new_documentation_filename << "\"" << std::endl
      << "git add \"" << new_header_filename << "\"" << std::endl
      << "git add \"" << new_source_filename << "\"" << std::endl
      ;
   std::cout << std::endl;
   std::cout << std::endl;

   // rename the symbols
   // example:
   // std::cout << "git grep -lz 'Wicked::Zones::Base3D' | xargs -0 perl -i'' -pE \"s/Wicked::Zones::Base3D/Wicked::Entities::Zones::Base3D/g\"" << std::endl;
   std::string current_symbol_name = current_component_generator.get_program_body_class_name();
   std::string new_symbol_name = new_component_generator.get_program_body_class_name();
   std::cout << "COMMAND: Replace the symbol:" << std::endl;
   std::cout << "============================" << std::endl;
   std::cout << std::endl;
   std::cout << "git grep -lz '" << current_symbol_name << "' | xargs -0 perl -i'' -pE \"s/" << current_symbol_name << "/" << new_symbol_name << "/g\"" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;

   // rename the include directories
   // example:
   // std::cout << "git grep -lz 'Wicked/Zones/Base3D' | xargs -0 perl -i'' -pE \"s/Wicked\/Zones\/Base3D/Wicked\/Entities\/Zones\/Base3D/g\"" << std::endl;
   std::string current_include_string = current_component_generator.get_component_name();
   std::string new_include_string = new_component_generator.get_component_name();
   ___replace(current_include_string, "/", "\\/");
   ___replace(new_include_string, "/", "\\/");
   std::cout << "COMMAND: Replace the include directory paths:" << std::endl;
   std::cout << "============================================" << std::endl;
   std::cout << std::endl;
   std::cout << "git grep -lz '" << current_include_string << "' | xargs -0 perl -i'' -pE \"s/" << current_include_string << "/" << new_include_string << "/g\"" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;

   // rename the test names and test fixture class names
   // example:
   // std::cout << "git grep -lz 'Wicked/Zones/Base3D' | xargs -0 perl -i'' -pE \"s/Wicked\/Zones\/Base3D/Wicked\/Entities\/Zones\/Base3D/g\"" << std::endl;
   std::string current_test_name_string = current_component_generator.get_component_name();
   std::string new_test_name_string = new_component_generator.get_component_name();
   ___replace(current_test_name_string, "/", "_");
   ___replace(new_test_name_string, "/", "_");
   std::cout << "COMMAND: Replace the test names and test fixture class names:" << std::endl;
   std::cout << "=============================================================" << std::endl;
   std::cout << std::endl;
   std::cout << "git grep -lz '" << current_test_name_string << "' | xargs -0 perl -i'' -pE \"s/" << current_test_name_string << "/" << new_test_name_string << "/g\"" << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;
   std::cout << std::endl;


   return 0;
}


