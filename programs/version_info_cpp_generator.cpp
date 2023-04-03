#include <allegro5/allegro.h>

#include <Blast/DirectoryExistenceChecker.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   if (args.size() <= 1)
   {
      std::cout << "===================================" << std::endl;
      std::cout << "==    Create Version Info Cpp    ==" << std::endl;
      std::cout << "===================================" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "=== Instructions:" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "  Your first argument should be the name of the project." << std::endl;
      std::cout << "" << std::endl;
      std::cout << "=== Example Usage:" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "> /Users/markoates/Repos/blast/version_info_cpp_generator Solitare" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "" << std::endl;

      return 1;
   }

   std::string project_name = args[1]; // "Solitare";
   std::string expected_root_directory = "/Users/markoates/Repos";

   std::string complete_folder_path_to_project_folder = expected_root_directory + "/" + project_name;

   Blast::DirectoryExistenceChecker directory_existence_checker(complete_folder_path_to_project_folder);
   if (!directory_existence_checker.exists())
   {
      std::stringstream error_message;
      error_message << "version_info_cpp_generator: error: directory does not exist named \"" << complete_folder_path_to_project_folder << "\"";
      throw std::runtime_error(error_message.str().c_str());
   }

   return 0;
};
