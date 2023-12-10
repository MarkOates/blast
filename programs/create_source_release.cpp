#include <allegro5/allegro.h>

#include <Blast/Project/SourceReleaseBuilder.hpp>
#include <Blast/DirectoryExistenceChecker.hpp>
#include <sstream>
#include <vector>
#include <iostream>


#define CONSOLE_COLOR_RED "\033[1;31m"
#define CONSOLE_COLOR_YELLOW "\033[1;33m"
#define CONSOLE_COLOR_GREEN "\033[1;32m"
#define CONSOLE_COLOR_DEFAULT "\033[0m"
#define CONSOLE_COLOR_CYAN "\033[1;36m"



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
      std::cout << " ^ This will: " << std::endl;
      std::cout << "   - CREATE a \"Releases\" folder in the home directory (\"~/\" folder)" << std::endl;
      std::cout << "   - CREATE a \"Releases/SolitareSourceRelease\" folder" << std::endl;
      std::cout << "   - COPY the following source files into \"releases/SolitareSourceRelease\":" << std::endl;
      std::cout << "      - source from \"/Users/markoates/Repos/Solitare/src\"" << std::endl;
      std::cout << "      - includes from \"/Users/markoates/Repos/Solitare/include\"" << std::endl;
      std::cout << "      - \"/Users/markoates/Repos/allegro_flare/include/*.*\"" << std::endl;
      std::cout << "      - \"/Users/markoates/Repos/allegro_flare/src/*.*\"" << std::endl;
      std::cout << "      - \"/Users/markoates/Repos/allegro_flare/include/lib/nlohmann/json.hpp\"" << std::endl;
      std::cout << "   - COPY the data/ folder from \"/Users/markoates/Repos/Solitare\"" << std::endl;
      std::cout << "   - REMOVE the following from \"SolitareSourceRelease\":" << std::endl;
      std::cout << "      - \"/include/AllegroFlare/Network/\" (because it requires asio.hpp)" << std::endl;
      std::cout << "      - \"/src/AllegroFlare/Network/\" (because it requires asio.hpp)" << std::endl;
      std::cout << "      - \"/include/AllegroFlare/Testing/\" (because it requires Google Test)" << std::endl;
      std::cout << "      - \"/src/AllegroFlare/Testing/\" (because it requires Google Test)" << std::endl;
      std::cout << "   - CREATE a \"Makefile\" that can be used to `make` on cross-platform" << std::endl;
      std::cout << "   - INCREMENT the \"version.yml\" to create a release version" << std::endl;
      std::cout << "   - INCREMENT the \"version.yml\" a second time to a development version" << std::endl;
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
   std::string destination_directory = "/Users/markoates/Releases";
   std::string main_program_filename = "programs/main.cpp";
   std::string project_appinfo_yaml_filename = "appinfo.yml";
   bool link_with_opengl = true;
   bool link_with_yaml_cpp = false;
   bool copy_allegro_flare_source = true;
   bool exclude_yaml_files_from_allegro_flare_source = true;
   bool copy_nlohmann_json_from_allegro_flare_source = true;
   bool remove_AllegroFlare_Network_from_allegro_flare_copy = true;
   bool remove_AllegroFlare_Testing_from_allegro_flare_copy = true;

   // TODO: Remove this list from the constructor and assign each after declaring the object
   Blast::Project::SourceReleaseBuilder source_release_builder(
         destination_directory,
         project_name,
         source_project_directory,
         main_program_filename,
         project_appinfo_yaml_filename,
         link_with_opengl,
         link_with_yaml_cpp,
         copy_allegro_flare_source,
         exclude_yaml_files_from_allegro_flare_source,
         copy_nlohmann_json_from_allegro_flare_source,
         remove_AllegroFlare_Network_from_allegro_flare_copy,
         remove_AllegroFlare_Testing_from_allegro_flare_copy
      );
   source_release_builder.set_prompt_before_deleting_unneeded_folders(false);
   source_release_builder.generate_source_release();

   if (!source_release_builder.get_build_process_completed_successfully())
   {
      std::stringstream error_message;
      error_message << "create_source_release: error: directory does not exist named \"" << complete_folder_path_to_project_folder << "\"";
      throw std::runtime_error(error_message.str().c_str());
      exit(1);
   }
   else
   {
      std::string released_version_number = source_release_builder.get_released_version_string();
      std::string generated_release_folder_name = source_release_builder.get_generated_release_folder_name();
      std::string generated_source_release_zip_filename = source_release_builder.get_generated_source_release_zip_filename();
      std::stringstream command_to_make_macos_release;
         command_to_make_macos_release << "make macos_release RELEASE_PROJECT_NAME=" << project_name << " RELEASE_VERSION_NUMBER=" << released_version_number << " RELEASE_FOLDER_NAME=" << generated_release_folder_name;
      std::stringstream command_to_make_win64_release;
         command_to_make_win64_release << "make win64_release EXPECTED_RELEASE_FOLDER_NAME=" << generated_release_folder_name;
      //std::string project_testing_src_folder_name << 
      //std::string project_testing_include_folder_name << 
      std::stringstream success_message;

      success_message << std::endl;
      success_message << "===============================================" << std::endl;
      success_message << "==    Source Release Created Successfully!   ==" << std::endl;
      success_message << "===============================================" << std::endl;
      success_message << std::endl;
      success_message << "                   ~Releases base folder: \"" << destination_directory << "\"" << std::endl;
      success_message << "   Command to go to the ~Releases folder: \"cd " << destination_directory << "\"" << std::endl;
      success_message << "                     Release folder name: \"" << generated_release_folder_name << "\"" << std::endl;
      success_message << "                        Release zip file: \"" << generated_source_release_zip_filename << "\"" << std::endl;
      success_message << std::endl;
      success_message << "Note that a zip file was automatically crated.  The following command can be used to zip it up if you wish to modify the folder and re-zip it:" << std::endl;
      success_message << std::endl;
      //success_message << "(cd " << destination_directory << " && rm " << generated_source_release_zip_filename << ")" << std::endl;
      //success_message << "(cd " << destination_directory << "/" << generated_release_folder_name << " && rm -rdf " << project_testing_src_folder_name.str() << ")" << std::endl;
      //success_message << "(cd " << destination_directory << "/" << generated_release_folder_name << " && rm -rdf " << project_testing_include_folder_name.str() << ")" << std::endl;
      success_message << "zip -r " << generated_source_release_zip_filename << " " << generated_release_folder_name << std::endl;
      success_message << std::endl;
      success_message << "If you wish to upload the file to a bucket on google cloud, run the following command:" << std::endl;
      success_message << "gcloud storage cp ~/Releases/" << generated_source_release_zip_filename << " gs://clubcatt-games-bucket/" << std::endl;
      success_message << std::endl;
      success_message << "Your zip release file should then be available on the web at:" << std::endl;
      success_message << "https://storage.googleapis.com/clubcatt-games-bucket/" << generated_source_release_zip_filename << std::endl;
      success_message << std::endl;
      success_message << "For help setting up gcloud, then please reference me/installing_and_setting_up_google_cloud.md" << std::endl;
      success_message << std::endl;
      success_message << std::endl;
      success_message << std::endl;
      success_message << "===============================================" << std::endl;
      success_message << "==          Create Binary Releases           ==" << std::endl;
      success_message << "===============================================" << std::endl;
      success_message << std::endl;
      success_message << "   Command to make MacOS release: \"" << command_to_make_macos_release.str() << "\"" << std::endl;
      success_message << "   Command to make Win64 release: \"" << command_to_make_win64_release.str() << "\"" << std::endl;
      success_message << std::endl;
      std::cout << CONSOLE_COLOR_CYAN << success_message.str() << CONSOLE_COLOR_DEFAULT << std::endl;
   }

   return 0;
}
