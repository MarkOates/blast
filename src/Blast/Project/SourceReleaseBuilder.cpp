

#include <Blast/Project/SourceReleaseBuilder.hpp>

#include <Blast/DirectoryCreator.hpp>
#include <Blast/DirectoryExistenceChecker.hpp>
#include <Blast/Errors.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Blast/Project/ProjectSymlinkFixer.hpp>
#include <Blast/Project/SymlinkChecker.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/TimeStamper.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>


namespace Blast
{
namespace Project
{


SourceReleaseBuilder::SourceReleaseBuilder(std::string destination_directory, std::string project_name, std::string source_project_directory, std::string main_program_filename, bool link_with_opengl, bool copy_allegro_flare_source, bool copy_nlohmann_json_from_allegro_flare_source, bool copy_ordered_map_from_allegro_flare_source, bool remove_AllegroFlare_Network_from_allegro_flare_copy, bool remove_AllegroFlare_Network2_from_allegro_flare_copy, bool remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy, bool remove_AllegroFlare_Testing_from_allegro_flare_copy, bool prompt_before_deleting_unneeded_folders)
   : destination_directory(destination_directory)
   , project_name(project_name)
   , source_project_directory(source_project_directory)
   , main_program_filename(main_program_filename)
   , link_with_opengl(link_with_opengl)
   , copy_allegro_flare_source(copy_allegro_flare_source)
   , copy_nlohmann_json_from_allegro_flare_source(copy_nlohmann_json_from_allegro_flare_source)
   , copy_ordered_map_from_allegro_flare_source(copy_ordered_map_from_allegro_flare_source)
   , remove_AllegroFlare_Network_from_allegro_flare_copy(remove_AllegroFlare_Network_from_allegro_flare_copy)
   , remove_AllegroFlare_Network2_from_allegro_flare_copy(remove_AllegroFlare_Network2_from_allegro_flare_copy)
   , remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy(remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy)
   , remove_AllegroFlare_Testing_from_allegro_flare_copy(remove_AllegroFlare_Testing_from_allegro_flare_copy)
   , prompt_before_deleting_unneeded_folders(prompt_before_deleting_unneeded_folders)
{
}


SourceReleaseBuilder::~SourceReleaseBuilder()
{
}


void SourceReleaseBuilder::set_link_with_opengl(bool link_with_opengl)
{
   this->link_with_opengl = link_with_opengl;
}


void SourceReleaseBuilder::set_copy_allegro_flare_source(bool copy_allegro_flare_source)
{
   this->copy_allegro_flare_source = copy_allegro_flare_source;
}


void SourceReleaseBuilder::set_copy_nlohmann_json_from_allegro_flare_source(bool copy_nlohmann_json_from_allegro_flare_source)
{
   this->copy_nlohmann_json_from_allegro_flare_source = copy_nlohmann_json_from_allegro_flare_source;
}


void SourceReleaseBuilder::set_copy_ordered_map_from_allegro_flare_source(bool copy_ordered_map_from_allegro_flare_source)
{
   this->copy_ordered_map_from_allegro_flare_source = copy_ordered_map_from_allegro_flare_source;
}


void SourceReleaseBuilder::set_remove_AllegroFlare_Network_from_allegro_flare_copy(bool remove_AllegroFlare_Network_from_allegro_flare_copy)
{
   this->remove_AllegroFlare_Network_from_allegro_flare_copy = remove_AllegroFlare_Network_from_allegro_flare_copy;
}


void SourceReleaseBuilder::set_remove_AllegroFlare_Network2_from_allegro_flare_copy(bool remove_AllegroFlare_Network2_from_allegro_flare_copy)
{
   this->remove_AllegroFlare_Network2_from_allegro_flare_copy = remove_AllegroFlare_Network2_from_allegro_flare_copy;
}


void SourceReleaseBuilder::set_remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy(bool remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy)
{
   this->remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy = remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy;
}


void SourceReleaseBuilder::set_remove_AllegroFlare_Testing_from_allegro_flare_copy(bool remove_AllegroFlare_Testing_from_allegro_flare_copy)
{
   this->remove_AllegroFlare_Testing_from_allegro_flare_copy = remove_AllegroFlare_Testing_from_allegro_flare_copy;
}


void SourceReleaseBuilder::set_prompt_before_deleting_unneeded_folders(bool prompt_before_deleting_unneeded_folders)
{
   this->prompt_before_deleting_unneeded_folders = prompt_before_deleting_unneeded_folders;
}


std::string SourceReleaseBuilder::get_project_name() const
{
   return project_name;
}


std::string SourceReleaseBuilder::get_source_project_directory() const
{
   return source_project_directory;
}


std::string SourceReleaseBuilder::get_main_program_filename() const
{
   return main_program_filename;
}


bool SourceReleaseBuilder::get_link_with_opengl() const
{
   return link_with_opengl;
}


bool SourceReleaseBuilder::get_copy_allegro_flare_source() const
{
   return copy_allegro_flare_source;
}


bool SourceReleaseBuilder::get_copy_nlohmann_json_from_allegro_flare_source() const
{
   return copy_nlohmann_json_from_allegro_flare_source;
}


bool SourceReleaseBuilder::get_copy_ordered_map_from_allegro_flare_source() const
{
   return copy_ordered_map_from_allegro_flare_source;
}


bool SourceReleaseBuilder::get_remove_AllegroFlare_Network_from_allegro_flare_copy() const
{
   return remove_AllegroFlare_Network_from_allegro_flare_copy;
}


bool SourceReleaseBuilder::get_remove_AllegroFlare_Network2_from_allegro_flare_copy() const
{
   return remove_AllegroFlare_Network2_from_allegro_flare_copy;
}


bool SourceReleaseBuilder::get_remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy() const
{
   return remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy;
}


bool SourceReleaseBuilder::get_remove_AllegroFlare_Testing_from_allegro_flare_copy() const
{
   return remove_AllegroFlare_Testing_from_allegro_flare_copy;
}


bool SourceReleaseBuilder::get_prompt_before_deleting_unneeded_folders() const
{
   return prompt_before_deleting_unneeded_folders;
}


void SourceReleaseBuilder::write_file_contents(std::string filename, std::string file_contents)
{
   std::ofstream out(filename);
   out << file_contents;
   out.close();
}

std::string SourceReleaseBuilder::get_makefile_content()
{
   std::stringstream MAKEFILE_CONTENT;
   //std::string main_program_name = "main";
   // TODO throw error if project name contains invalid characters (spaces, etc)
   // TODO throw error if main program filename does not exist, or contains invalid characters (spaces, etc)
   std::string binary_name = project_name; //"FadeToWhite"; // project_name

   bool include_opengl = get_link_with_opengl();

   MAKEFILE_CONTENT
                    //<< "SRC_FILES := $(shell find src -type f)"
                    << "SRC_FILES := $(shell find src -type f -not -path '*/.*')"
                    << std::endl
                    << "ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog "
                    << "-lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro "
                    << "-lallegro_main" << std::endl
                    << std::endl;

   if (include_opengl)
   {
                 MAKEFILE_CONTENT
                    << "ifeq ($(OS), Windows_NT)" << std::endl
                    << "\tOPENGL_LIB=-lopengl32" << std::endl
                    << "\tWINDOWS_SUBSYSTEM_FLAGS=-Wl,--subsystem,windows" << std::endl
                    << "else" << std::endl
                    << "\tUNAME_S := $(shell uname -s)" << std::endl
                    << "\tifeq ($(UNAME_S),Linux)" << std::endl
                    << "\t\tOPENGL_LIB=-lGL" << std::endl
                    << "\tendif" << std::endl
                    << "\tifeq ($(UNAME_S),Darwin)" << std::endl
                    << "\t\tOPENGL_LIB=-framework OpenGL" << std::endl
                    << "\tendif" << std::endl
                    << "endif" << std::endl
                    << std::endl;
   }

   // the "main:" target
   MAKEFILE_CONTENT
                    << "main: $(SRC_FILES)" << std::endl
                    << "\t"
                    << "g++ -std=c++17 $(WINDOWS_SUBSYSTEM_FLAGS) $^ " << main_program_filename << " -o " << binary_name
                    << " -I./include $(ALLEGRO_LIBS)";
                    if (include_opengl) MAKEFILE_CONTENT << " $(OPENGL_LIB)" << std::endl;
                    MAKEFILE_CONTENT << std::endl;

   // the "list_objects:" target
   MAKEFILE_CONTENT
                    << "SOURCES := $(shell find src -name '*.cpp')" << std::endl
                    << "OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)" << std::endl
                    << "NUM_OF_OBJECTS := $(words $(OBJECTS))" << std::endl
                    << std::endl
                    << "list_objects:" << std::endl
                    << "\t@echo \"number of objects: $(NUM_OF_OBJECTS)\"" << std::endl
                    << "\t@for item in $(OBJECTS) ; do \\" << std::endl
                    << "\techo $$item ; \\" << std::endl
                    << "done" << std::endl;


   return MAKEFILE_CONTENT.str();
}

std::string SourceReleaseBuilder::get_pinfo_content()
{
   std::string PINFO_CONTENT = R"HEREDOC(
   <?xml version="1.0" encoding="UTF-8"?>
   <!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
   <plist version="1.0">
   <dict>
      <key>CFBundleDevelopmentRegion</key>
      <string>English</string>
      <key>CFBundleExecutable</key>
      <string>Hexagon</string>
      <key>CFBundleGetInfoString</key>
      <string>0.8, Copyright 2022 Mark Oates</string>
      <key>CFBundleIconFile</key>
      <string>Icon.icns</string>
      <key>CFBundleIdentifier</key>
      <string>org.markoates.Hexagon</string>
      <key>CFBundleInfoDictionaryVersion</key>
      <string>6.0</string>
      <key>CFBundleLongVersionString</key>
      <string>Hexagon</string>
      <key>CFBundleName</key>
      <string></string>
      <key>CFBundlePackageType</key>
      <string>APPL</string>
      <key>CFBundleShortVersionString</key>
      <string>0.8</string>
      <key>CFBundleSignature</key>
      <string>????</string>
      <key>CFBundleVersion</key>
      <string></string>
      <key>CSResourcesFileMapped</key>
      <true/>
      <key>LSRequiresCarbon</key>
      <true/>
      <key>NSHumanReadableCopyright</key>
      <string>Copyright 2022 Mark Oates</string>
   </dict>
   </plist>
   )HEREDOC";
   return PINFO_CONTENT;
}

void SourceReleaseBuilder::copy_file(std::string source_filename, std::string destination_filename)
{
   std::ifstream src(source_filename, std::ios::binary);
   std::ofstream dst(destination_filename,   std::ios::binary);
   dst << src.rdbuf();
}

std::vector<std::pair<std::string, std::string>> SourceReleaseBuilder::list_symlinks()
{
   std::string command = std::string("find ") + destination_directory;
   Blast::ShellCommandExecutorWithCallback executor(
      command,
      ShellCommandExecutorWithCallback::simple_silent_callback
   );
   std::string executor_result = executor.execute();
   StringSplitter splitter(executor_result, '\n');

   std::vector<std::string> filenames = splitter.split();
   std::vector<std::pair<std::string, std::string>> result;

   for (auto &filename : filenames)
   {
      Blast::Project::SymlinkChecker symlink_checker(filename);
      bool symlink_status = symlink_checker.is_symlink();

      if (symlink_status)
      {
         std::pair<std::string, std::string> this_symlink_info{ filename, symlink_checker.read_symlink_target() };
         result.push_back(this_symlink_info);
      }
   }

   std::sort(result.begin(), result.end());

   return result;
}

void SourceReleaseBuilder::fix_symlink_targets_from_relative_to_absolute()
{
   Blast::Project::ProjectSymlinkFixer symlink_fixer(destination_directory);
   symlink_fixer.run();
   return;
}

void SourceReleaseBuilder::replace_symlinks_with_copies_of_linked_files()
{
   //std::cout << "Reading symlinks... " << std::endl;
   std::vector<std::pair<std::string, std::string>> symlinks = list_symlinks();

   for (auto &symlink : symlinks)
   {
      std::string file_to_remove = symlink.first;
      std::string file_to_copy_source = symlink.second;
      std::string file_to_copy_destination = symlink.first;

      if (remove(file_to_remove.c_str()) != 0)
      {
         std::stringstream error_message;
         error_message << "There was an error trying to delete the file \"" << file_to_remove << "\"" << std::endl;
         throw std::runtime_error(error_message.str());
      }

      copy_file(file_to_copy_source, file_to_copy_destination);
   }

   std::cout << "Finished reading symlinks (" << symlinks.size() << " symlinked file(s) replaced)." << std::endl;
   return;
}

std::string SourceReleaseBuilder::get_source_release_folder_name()
{
   return get_project_name() + "-SourceRelease";
}

std::string SourceReleaseBuilder::get_macos_release_folder_name()
{
   return get_project_name() + "-MacOSRelease";
}

std::string SourceReleaseBuilder::get_win64_release_folder_name()
{
   return get_project_name() + "-Win64Release";
}

void SourceReleaseBuilder::generate_macos_release()
{
   // create folder "Flower.app/"
   return;
}

void SourceReleaseBuilder::recursively_remove_folder_with_prompt(std::string folder_to_remove)
{
   std::stringstream folder_removal_command;
   folder_removal_command << "rm -rdf \"" << folder_to_remove << "\"";

   std::cout << "Blast/Project/SourceReleaseBuilder will now attempt to delete the following folder:" << std::endl;
   std::cout << "   \"" << folder_to_remove << "\"" << std::endl;
   std::cout << "Using the command:" << std::endl;
   std::cout << "   " << folder_removal_command.str() << "" << std::endl;
   std::cout << "Do you wish to continue? (y/n) > ";
   char input = 'n';
   if (prompt_before_deleting_unneeded_folders) std::cin >> input;
   else input = 'y';

   if (input == 'y')
   {
      //std::stringstream folder_removal_command;
      //folder_removal_command << "rm -rdf " << folder_to_remove;
      Blast::ShellCommandExecutorWithCallback folder_removal_command_executor(
            folder_removal_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
         );

      std::cout << "Removing folder...";
      folder_removal_command_executor.execute();
      std::cout << "done." << std::endl;
   }
   return;
}

void SourceReleaseBuilder::generate_source_release()
{
   // options:
   bool validate_bin_programs_data_folder_from_source_exists = true;
   bool validate_readme_exists_in_source_folder = true;
   bool copy_allegro_flare_source_and_header_files_from_source = true;
   bool copy_allegro_flare_include_lib_nlohmann_json_from_source = true;
   bool copy_allegro_flare_include_lib_ordered_map_from_source = true;
   Blast::TimeStamper time_stamper;

   std::string source_directory = get_source_project_directory();

   // !! WARNING: local variable name shadows class instance variable name:
   std::string xxx = destination_directory
                   + "/"
                   + get_source_release_folder_name()
                   + "-" + time_stamper.generate_now_timestamp_utc();

   // create the directory
   std::vector<std::string> directories_that_will_exist = StringSplitter(xxx, '/').split();
   Blast::DirectoryCreator directory_creator(directories_that_will_exist, true);
   bool created = directory_creator.create();
   if (!created)
   {
      std::stringstream error_message;
      error_message << "Project/ReleaseBuilder error: could not create directory \""
                   << xxx
                   << "\"";
      throw std::runtime_error(error_message.str());
   }


   if (validate_bin_programs_data_folder_from_source_exists)
   {
      // TODO: test this condition
      std::string expected_data_folder_location = source_directory + "/bin/programs/data";
      Blast::DirectoryExistenceChecker checker(expected_data_folder_location);
      if (!checker.exists())
      {
         std::string message = "The expected bin/programs/data folder does not exist. Expected at "
                               "\"" + expected_data_folder_location + "\"";
         Blast::Errors::throw_error(
            "Blast::Project::SourceReleaseBuilder::generate_source_release()",
            message
         );
      }
   }


   if (validate_readme_exists_in_source_folder)
   {
      // TODO: test this condition
      std::string expected_readme_location = source_directory + "/README.md";
      Blast::FileExistenceChecker checker(expected_readme_location);
      if (!checker.exists())
      {
         std::string message = "The expected README.md file does not exist. Expected at "
                               "\"" + expected_readme_location + "\"";
         Blast::Errors::throw_error(
            "Blast::Project::SourceReleaseBuilder::generate_source_release()",
            message
         );
      }
   }



   std::string destination_directory = xxx;


   std::stringstream copy_include_files_command;
   copy_include_files_command << "cp -R " << source_directory << "/include " << destination_directory << "/include";
   std::stringstream copy_src_files_command;
   copy_src_files_command << "cp -R " << source_directory << "/src " << destination_directory << "/src";
   std::stringstream copy_data_files_command;
   copy_data_files_command << "cp -R " << source_directory << "/bin/programs/data " << destination_directory << "/data";
   std::stringstream copy_program_files_command;
   copy_program_files_command << "cp -R " << source_directory << "/programs " << destination_directory << "/programs";
   std::stringstream copy_readme_file_command;
   copy_readme_file_command << "cp " << source_directory << "/README.md " << destination_directory << "/README.md";


   // copy files
   Blast::ShellCommandExecutorWithCallback include_file_copy_executor(copy_include_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
   Blast::ShellCommandExecutorWithCallback src_file_copy_executor(copy_src_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
   Blast::ShellCommandExecutorWithCallback data_file_copy_executor(copy_data_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
   Blast::ShellCommandExecutorWithCallback program_file_copy_executor(copy_program_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);
   Blast::ShellCommandExecutorWithCallback readme_file_copy_executor(copy_readme_file_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback);

   std::cout << "Copying include files into \"" << destination_directory << "\"... ";
   include_file_copy_executor.execute();
   std::cout << "done." << std::endl;

   std::cout << "Copying src files into \"" << destination_directory << "\"... ";
   src_file_copy_executor.execute();
   std::cout << "done." << std::endl;

   std::cout << "Copying program files into \"" << destination_directory << "\"... ";
   program_file_copy_executor.execute();
   std::cout << "done." << std::endl;

   std::cout << "Copying data files into \"" << destination_directory << "\"... ";
   data_file_copy_executor.execute();
   std::cout << "done." << std::endl;

   std::cout << "Copying README.md file into \"" << destination_directory << "\"... ";
   readme_file_copy_executor.execute();
   std::cout << "done." << std::endl;

   std::cout << "Creating rudimentary Makefile...";
   std::string makefile_full_filename = destination_directory + "/Makefile";
   write_file_contents(makefile_full_filename, get_makefile_content());
   std::cout << "done." << std::endl;

   std::cout << "Fixing symlinks from relative to absolute...";
   fix_symlink_targets_from_relative_to_absolute();
   std::cout << "done." << std::endl;

   std::cout << "Replacing sylminked files with original copies.";
   replace_symlinks_with_copies_of_linked_files();
   std::cout << "done." << std::endl;


   bool manually_copy_allegro_flare_headers_and_source_files = this->get_copy_allegro_flare_source();
   if (manually_copy_allegro_flare_headers_and_source_files)
   {
      /// Build commands

      // headers
      std::string allegro_flare_include_directory = "/Users/markoates/Repos/allegro_flare/include/AllegroFlare";
      std::string allegro_flare_include_destination_directory = destination_directory + "/include/AllegroFlare";
      std::stringstream copy_allegro_flare_include_files_command;
      copy_allegro_flare_include_files_command << "cp -R " << allegro_flare_include_directory << " " << allegro_flare_include_destination_directory;

      // src
      std::string allegro_flare_src_directory = "/Users/markoates/Repos/allegro_flare/src/AllegroFlare";
      std::string allegro_flare_src_destination_directory = destination_directory + "/src/AllegroFlare";
      std::stringstream copy_allegro_flare_src_files_command;
      copy_allegro_flare_src_files_command << "cp -R " << allegro_flare_src_directory << " " << allegro_flare_src_destination_directory;


      // Create command executors

      Blast::ShellCommandExecutorWithCallback allegro_flare_include_files_copy_executor(
            copy_allegro_flare_include_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
         );
      Blast::ShellCommandExecutorWithCallback allegro_flare_src_files_copy_executor(
            copy_allegro_flare_src_files_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
         );


      // Execute command executors

      std::cout << "Copying AllegroFlare include files into \"" << destination_directory << "\"... ";
      allegro_flare_include_files_copy_executor.execute();
      std::cout << "done." << std::endl;

      std::cout << "Copying AllegroFlare src files into \"" << destination_directory << "\"... ";
      allegro_flare_src_files_copy_executor.execute();
      std::cout << "done." << std::endl;
   }


   bool manually_copy_allegro_flare_include_lib_nlohmann_json_from_source =
     this->get_copy_nlohmann_json_from_allegro_flare_source();
   if (manually_copy_allegro_flare_include_lib_nlohmann_json_from_source)
   {
      // build the command
      std::stringstream copy_nlohmann_json_file_command;
      std::string nlohmann_json_file_source = "/Users/markoates/Repos/allegro_flare/include/lib/nlohmann/json.hpp";
      std::string nlohmann_json_file_destination_directory = destination_directory + "/include/lib/nlohmann";
      std::string nlohmann_json_file_destination = nlohmann_json_file_destination_directory + "/json.hpp";
      // TODO: check for file existence
      copy_nlohmann_json_file_command << "cp -R " << nlohmann_json_file_source << " " << nlohmann_json_file_destination;

      // start the copy process
      std::cout << "Copying lib/nlohmann/json.hpp file from AllegroFlare into \"" << destination_directory << "\"... "
                << std::endl;

      // create the directory if it doesn't exist
      std::cout << "  Ensuring directory exists...";
      std::vector<std::string> directories_needed_for_nlohmann_json = StringSplitter(
         nlohmann_json_file_destination_directory, '/').split();
      Blast::DirectoryCreator directory_creator(directories_needed_for_nlohmann_json, true);
      bool created = directory_creator.create();
      if (!created)
      {
         std::stringstream error_message;
         error_message << "Project/ReleaseBuilder error: could not create directory \""
                      << nlohmann_json_file_destination_directory
                      << "\"";
         throw std::runtime_error(error_message.str());
      }
      std::cout << " directory exists.";

      // execute the copy command
      Blast::ShellCommandExecutorWithCallback nlohmann_json_file_copy_executor(
            copy_nlohmann_json_file_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
         );
      nlohmann_json_file_copy_executor.execute();
      std::cout << "done." << std::endl;
   }


   bool manually_copy_allegro_flare_include_lib_ordered_map_from_source =
     this->get_copy_ordered_map_from_allegro_flare_source();
   if (manually_copy_allegro_flare_include_lib_ordered_map_from_source)
   {
      // build the command
      std::stringstream copy_ordered_map_file_command;
      std::stringstream copy_ordered_hash_file_command;
      std::string ordered_map_file_source = "/Users/markoates/Repos/allegro_flare/include/lib/tsl/ordered_map.h";
      std::string ordered_hash_file_source = "/Users/markoates/Repos/allegro_flare/include/lib/tsl/ordered_hash.h";
      std::string ordered_map_file_destination_directory = destination_directory + "/include/lib/tsl";
      std::string ordered_map_file_destination = ordered_map_file_destination_directory + "/ordered_map.h";
      std::string ordered_hash_file_destination = ordered_map_file_destination_directory + "/ordered_hash.h";
      // TODO: check for file existence
      copy_ordered_map_file_command << "cp -R " << ordered_map_file_source << " " << ordered_map_file_destination;
      copy_ordered_hash_file_command << "cp -R " << ordered_hash_file_source << " " << ordered_hash_file_destination;

      // start the copy process
      std::cout << "Copying lib/tsl/ordered_map.h file from AllegroFlare into "
                << "\"" << destination_directory << "\"... "
                << std::endl;

      // create the directory if it doesn't exist
      std::cout << "  Ensuring directory exists...";
      std::vector<std::string> directories_needed_for_ordered_map = StringSplitter(
         ordered_map_file_destination_directory, '/').split();
      Blast::DirectoryCreator directory_creator(directories_needed_for_ordered_map, true);
      bool created = directory_creator.create();
      if (!created)
      {
         std::stringstream error_message;
         error_message << "[Project/ReleaseBuilder] error: could not create directory \""
                      << ordered_map_file_destination_directory
                      << "\"";
         throw std::runtime_error(error_message.str());
      }
      std::cout << " directory exists.";

      // execute the copy command for "ordered_map"
      Blast::ShellCommandExecutorWithCallback ordered_map_file_copy_executor(
            copy_ordered_map_file_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
         );
      ordered_map_file_copy_executor.execute();

      // execute the copy command for "ordered_hash"
      Blast::ShellCommandExecutorWithCallback ordered_hash_file_copy_executor(
            copy_ordered_hash_file_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
         );
      ordered_hash_file_copy_executor.execute();

      std::cout << "done." << std::endl;
   }


   if (get_remove_AllegroFlare_Network_from_allegro_flare_copy())
   {
      std::string include_folder_to_remove = destination_directory + "/include/AllegroFlare/Network";
      recursively_remove_folder_with_prompt(include_folder_to_remove);
      std::string src_folder_to_remove = destination_directory + "/src/AllegroFlare/Network";
      recursively_remove_folder_with_prompt(src_folder_to_remove);
   }


   if (get_remove_AllegroFlare_Network2_from_allegro_flare_copy())
   {
      std::string include_folder_to_remove = destination_directory + "/include/AllegroFlare/Network2";
      recursively_remove_folder_with_prompt(include_folder_to_remove);
      std::string src_folder_to_remove = destination_directory + "/src/AllegroFlare/Network2";
      recursively_remove_folder_with_prompt(src_folder_to_remove);
   }


   if (get_remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy())
   {
      std::string include_folder_to_remove = destination_directory + "/include/AllegroFlare/Integrations/Network.hpp";
      recursively_remove_folder_with_prompt(include_folder_to_remove);
      std::string src_folder_to_remove = destination_directory + "/src/AllegroFlare/Integrations/Network.cpp";
      recursively_remove_folder_with_prompt(src_folder_to_remove);
   }


   if (get_remove_AllegroFlare_Testing_from_allegro_flare_copy())
   {
      std::string include_folder_to_remove = destination_directory + "/include/AllegroFlare/Testing";
      recursively_remove_folder_with_prompt(include_folder_to_remove);
      std::string src_folder_to_remove = destination_directory + "/src/AllegroFlare/Testing";
      recursively_remove_folder_with_prompt(src_folder_to_remove);
   }


   return;
}


} // namespace Project
} // namespace Blast


