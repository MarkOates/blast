#include <allegro5/allegro.h>

#include <Blast/Project/SourceReleaseBuilder.hpp>
#include <Blast/DirectoryExistenceChecker.hpp>
#include <sstream>
#include <vector>
#include <iostream>

std::string surround_with_box(std::string message)
{
   return message;
}

int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   if (args.size() <= 1)
   {
      std::cout << "=================================" << std::endl;
      std::cout << "==    Create Source Release    ==" << std::endl;
      std::cout << "=================================" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "=== Version:" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "v0.0.1" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "=== Instructions:" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "  Your first argument should be the name of the project." << std::endl;
      std::cout << "It's expected that the name of your project and the folder" << std::endl;
      std::cout << "name in which it resides are the same." << std::endl;
      std::cout << "" << std::endl;
      std::cout << "=== Example Usage:" << std::endl;
      std::cout << "" << std::endl;
      std::cout << "> /Users/markoates/Repos/blast/create_source_release Solitare" << std::endl;
      std::cout << "" << std::endl;
      std::cout << " ^ This will create a \"Release\" folder on the desktop and" << std::endl;
      std::cout << "place the files in there." << std::endl;
      std::cout << "" << std::endl;
      return 0;
   }

   // call from whatever project directory you're in, it will add the release to the "~/Desktop/Release/" folder.

   std::string project_name = args[1]; // "Solitare";

   // verify that the project_name is indeed a folder name located in the expected directory
   std::string expected_root_directory = "/Users/markoates/Repos";

   // folder exists
   std::string complete_folder_path_to_project_folder = expected_root_directory + "/" + project_name;
   Blast::DirectoryExistenceChecker directory_existence_checker(complete_folder_path_to_project_folder);
   if (!directory_existence_checker.exists())
   {
      std::stringstream error_message;
      error_message << "create_source_release: error: directory does not exist named \"" << complete_folder_path_to_project_folder << "\"";
      throw std::runtime_error(error_message.str().c_str());
   }

   std::string source_project_directory = complete_folder_path_to_project_folder;
   std::string destination_directory="/Users/markoates/Desktop/Release";
   Blast::Project::SourceReleaseBuilder source_release_builder(
         destination_directory,
         project_name,
         source_project_directory
      );
   source_release_builder.generate_source_release();

   return 0;
}
