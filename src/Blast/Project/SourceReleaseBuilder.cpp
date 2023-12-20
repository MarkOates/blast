

#include <Blast/Project/SourceReleaseBuilder.hpp>

#include <Blast/BuildInfoCppFileGenerator.hpp>
#include <Blast/DirectoryCreator.hpp>
#include <Blast/DirectoryExistenceChecker.hpp>
#include <Blast/Errors.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Blast/Project/HardCodedPathInfrencer.hpp>
#include <Blast/Project/ProjectSymlinkFixer.hpp>
#include <Blast/Project/SourceReleaseAppInfoFile.hpp>
#include <Blast/Project/SymlinkChecker.hpp>
#include <Blast/ReleaseInfoBuilder.hpp>
#include <Blast/ReleaseInfoCppFileGenerator.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/TimeStamper.hpp>
#include <Blast/VersionYAMLLoaderEmitter.hpp>
#include <Blast/YAMLValidator.hpp>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Blast
{
namespace Project
{


SourceReleaseBuilder::SourceReleaseBuilder(std::string releases_base_folder, std::string project_name, std::string source_project_directory, std::string main_program_filename, std::string project_appinfo_yaml_filename, bool link_with_opengl, bool link_with_yaml_cpp, bool copy_allegro_flare_source, bool exclude_yaml_files_from_allegro_flare_source, bool copy_nlohmann_json_from_allegro_flare_source, bool copy_ordered_map_from_allegro_flare_source, bool remove_AllegroFlare_Network_from_allegro_flare_copy, bool remove_AllegroFlare_Network2_from_allegro_flare_copy, bool remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy, bool remove_AllegroFlare_Testing_from_allegro_flare_copy, bool remove_Testing_from_project_copy, bool prompt_before_deleting_unneeded_folders)
   : releases_base_folder(releases_base_folder)
   , project_name(project_name)
   , source_project_directory(source_project_directory)
   , main_program_filename(main_program_filename)
   , project_appinfo_yaml_filename(project_appinfo_yaml_filename)
   , link_with_opengl(link_with_opengl)
   , link_with_yaml_cpp(link_with_yaml_cpp)
   , build_process_completed_successfully(false)
   , generated_release_folder_name("")
   , release_info({})
   , build_info({})
   , copy_allegro_flare_source(copy_allegro_flare_source)
   , exclude_yaml_files_from_allegro_flare_source(exclude_yaml_files_from_allegro_flare_source)
   , copy_nlohmann_json_from_allegro_flare_source(copy_nlohmann_json_from_allegro_flare_source)
   , copy_ordered_map_from_allegro_flare_source(copy_ordered_map_from_allegro_flare_source)
   , remove_AllegroFlare_Network_from_allegro_flare_copy(remove_AllegroFlare_Network_from_allegro_flare_copy)
   , remove_AllegroFlare_Network2_from_allegro_flare_copy(remove_AllegroFlare_Network2_from_allegro_flare_copy)
   , remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy(remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy)
   , remove_AllegroFlare_Testing_from_allegro_flare_copy(remove_AllegroFlare_Testing_from_allegro_flare_copy)
   , remove_Testing_from_project_copy(remove_Testing_from_project_copy)
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


void SourceReleaseBuilder::set_link_with_yaml_cpp(bool link_with_yaml_cpp)
{
   this->link_with_yaml_cpp = link_with_yaml_cpp;
}


void SourceReleaseBuilder::set_copy_allegro_flare_source(bool copy_allegro_flare_source)
{
   this->copy_allegro_flare_source = copy_allegro_flare_source;
}


void SourceReleaseBuilder::set_exclude_yaml_files_from_allegro_flare_source(bool exclude_yaml_files_from_allegro_flare_source)
{
   this->exclude_yaml_files_from_allegro_flare_source = exclude_yaml_files_from_allegro_flare_source;
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


void SourceReleaseBuilder::set_remove_Testing_from_project_copy(bool remove_Testing_from_project_copy)
{
   this->remove_Testing_from_project_copy = remove_Testing_from_project_copy;
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


std::string SourceReleaseBuilder::get_project_appinfo_yaml_filename() const
{
   return project_appinfo_yaml_filename;
}


bool SourceReleaseBuilder::get_link_with_opengl() const
{
   return link_with_opengl;
}


bool SourceReleaseBuilder::get_link_with_yaml_cpp() const
{
   return link_with_yaml_cpp;
}


bool SourceReleaseBuilder::get_build_process_completed_successfully() const
{
   return build_process_completed_successfully;
}


std::string SourceReleaseBuilder::get_generated_release_folder_name() const
{
   return generated_release_folder_name;
}


Blast::ReleaseInfo SourceReleaseBuilder::get_release_info() const
{
   return release_info;
}


Blast::BuildInfo SourceReleaseBuilder::get_build_info() const
{
   return build_info;
}


bool SourceReleaseBuilder::get_copy_allegro_flare_source() const
{
   return copy_allegro_flare_source;
}


bool SourceReleaseBuilder::get_exclude_yaml_files_from_allegro_flare_source() const
{
   return exclude_yaml_files_from_allegro_flare_source;
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


bool SourceReleaseBuilder::get_remove_Testing_from_project_copy() const
{
   return remove_Testing_from_project_copy;
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

std::string SourceReleaseBuilder::get_released_version_string()
{
   if (!(build_process_completed_successfully))
   {
      std::stringstream error_message;
      error_message << "[SourceReleaseBuilder::get_released_version_string]: error: guard \"build_process_completed_successfully\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SourceReleaseBuilder::get_released_version_string: error: guard \"build_process_completed_successfully\" not met");
   }
   return release_info.build_project_version_string();
}

std::string SourceReleaseBuilder::get_makefile_content()
{
   std::stringstream MAKEFILE_CONTENT;
   //std::string main_program_name = "main";
   // TODO throw error if project name contains invalid characters (spaces, etc)
   // TODO throw error if main program filename does not exist, or contains invalid characters (spaces, etc)
   std::string binary_name = project_name; //"FadeToWhite"; // project_name

   bool include_opengl = get_link_with_opengl();
   bool include_yaml_cpp = get_link_with_yaml_cpp();
   //bool include_windows_app_icon_resource_variable = true;

   MAKEFILE_CONTENT
                    //<< "SRC_FILES := $(shell find src -type f)"
                    // NOTE: this line includes a '-not -name "*~"' clause that is intended to prevent emacs
                    // temp files from being included in the source. Note that this release Makefile is designed
                    // to be static (not for development context), so this may be removed in the future.
                    << "SRC_FILES := $(shell find src -type f -not -path '*/.*' -not -name \"*~\")"
                    // NOTE: the previous version without the clause is here:
                    //<< "SRC_FILES := $(shell find src -type f -not -path '*/.*')"
                    << std::endl
                    << "ALLEGRO_LIBS=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio "
                    << "-lallegro_acodec -lallegro_video -lallegro_primitives -lallegro_image -lallegro "
                    << "-lallegro_main" << std::endl;

   if (include_yaml_cpp)
   {
                 MAKEFILE_CONTENT
                    << "YAML_CPP_LIB=-lyaml-cpp" << std::endl
                    << std::endl;
   }

                 MAKEFILE_CONTENT
                    << std::endl;

   if (include_opengl)
   {
                 MAKEFILE_CONTENT
                    << "ifeq ($(OS), Windows_NT)" << std::endl
                    << "\tOPENGL_LIB=-lopengl32" << std::endl
        // NOTE: information regarding these subsystem flags:
        // https://www.allegro.cc/forums/thread/604546
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

   MAKEFILE_CONTENT
                    << "SOURCES := $(shell find src -name '*.cpp')" << std::endl
                    << "OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)" << std::endl
                    << "NUM_OF_OBJECTS := $(words $(OBJECTS))" << std::endl
                    << std::endl;


   // the "main:" target
   MAKEFILE_CONTENT
                    << "SOURCES := $(shell find src -name '*.cpp')" << std::endl
                    << "OBJECTS := $(SOURCES:src/%.cpp=build/obj/%.o)" << std::endl
                    << "NUM_OF_OBJECTS := $(words $(OBJECTS))" << std::endl
                    << "" << std::endl
                    << "" << std::endl
                    << "main: $(OBJECTS)" << std::endl
                    << "\t@g++ -std=c++17 $(WINDOWS_SUBSYSTEM_FLAGS) $(OBJECTS) "
                       << main_program_filename
                       << " $(WINDOWS_APP_ICON_RESOURCE_OBJECT_FILE)"
                       << " "
                       << "-o"
                       << " "
                       << binary_name
                       << " "
                       << "-I./include $(ALLEGRO_LIBS)";
                       if (include_opengl) MAKEFILE_CONTENT << " $(OPENGL_LIB)";
                       if (include_yaml_cpp) MAKEFILE_CONTENT << " $(YAML_CPP_LIB)";
                       //"-I./include $(ALLEGRO_LIBS) $(OPENGL_LIB)"
                       MAKEFILE_CONTENT << std::endl;
                    MAKEFILE_CONTENT << "\trm -rdf build" << std::endl
                    << "\trm -rdf build/obj" << std::endl
                    << "" << std::endl
                    << "" << std::endl
                    << "objects: $(OBJECTS)" << std::endl
                    << "" << std::endl
                    << "" << std::endl
                    << "fast:" << std::endl
                      << "\tmake objects -j3" << std::endl
                    << "\tmake main" << std::endl
                    << "" << std::endl
                    << "" << std::endl
                    << "build/obj/%.o: src/%.cpp" << std::endl
                    << "\t@mkdir -p build" << std::endl
                    << "\t@mkdir -p build/obj" << std::endl
                    << "\t@mkdir -p $(dir $@)" << std::endl
                    << "\tg++ -c -std=c++17 $< -o $@ -I./include" << std::endl
                    << "" << std::endl
                    << "" << std::endl;

   // the "legacy:" target
   MAKEFILE_CONTENT
                    << "legacy: $(SRC_FILES)" << std::endl
                    << "\t"
                    << "g++ -std=c++17 $(WINDOWS_SUBSYSTEM_FLAGS) $^ "
                           << main_program_filename
                           << " "
                           << "$(WINDOWS_APP_ICON_RESOURCE_OBJECT_FILE)"
                           << " "
                           << "-o"
                           << " "
                           << binary_name
                    << " -I./include $(ALLEGRO_LIBS)";
                    if (include_opengl) MAKEFILE_CONTENT << " $(OPENGL_LIB)";
                    if (include_yaml_cpp) MAKEFILE_CONTENT << " $(YAML_CPP_LIB)";
                    //if (include_windows_app_icon_resource_variable)
                    //{
                       //MAKEFILE_CONTENT << " $(WINDOWS_APP_ICON_RESOURCE_OBJECT_FILE)";
                    //}
                    MAKEFILE_CONTENT << std::endl;
                    MAKEFILE_CONTENT << std::endl;


                    //<< "list_objects:" << std::endl
                    //<< "\t@echo \"number of objects: $(NUM_OF_OBJECTS)\"" << std::endl
                    //<< "\t@for item in $(OBJECTS) ; do \\" << std::endl
                    //<< "\techo $$item ; \\" << std::endl
                    //<< "done" << std::endl;


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

std::string SourceReleaseBuilder::read_contents_of_file(std::string filePath)
{
   // TODO: Test this method
   std::ifstream file(filePath);
   std::string contents;

   if (file.is_open())
   {
      // Read the entire file into the string
      contents.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
      file.close();
   }
   else
   {
      // Handle the case where the file could not be opened
      std::cerr << "Unable to open file: " << filePath << std::endl;
   }

   return contents;
}

void SourceReleaseBuilder::copy_file(std::string source_filename, std::string destination_filename)
{
   std::ifstream src(source_filename, std::ios::binary);
   std::ofstream dst(destination_filename,   std::ios::binary);
   dst << src.rdbuf();
}

std::string SourceReleaseBuilder::get_release_info_header_file_contents()
{
   Blast::ReleaseInfoCppFileGenerator release_info_file_generator;
   release_info_file_generator.set_release_info(release_info);
   release_info_file_generator.initialize();
   return release_info_file_generator.header_file_content();
}

std::string SourceReleaseBuilder::get_release_info_source_file_contents()
{
   Blast::ReleaseInfoCppFileGenerator release_info_file_generator;
   release_info_file_generator.set_release_info(release_info);
   release_info_file_generator.initialize();
   return release_info_file_generator.source_file_content();
}

std::string SourceReleaseBuilder::get_build_info_header_file_contents()
{
   Blast::BuildInfoCppFileGenerator build_info_file_generator;
   build_info_file_generator.set_build_info(build_info);
   build_info_file_generator.initialize();
   return build_info_file_generator.header_file_content();
}

std::string SourceReleaseBuilder::get_build_info_source_file_contents()
{
   Blast::BuildInfoCppFileGenerator build_info_file_generator;
   build_info_file_generator.set_build_info(build_info);
   build_info_file_generator.initialize();
   return build_info_file_generator.source_file_content();
}

std::string SourceReleaseBuilder::get_project_appinfo_yaml_file_contents()
{
   std::string full_path_to_appinfo_yaml_file = source_project_directory + "/" + project_appinfo_yaml_filename;

   if (!std::filesystem::exists(full_path_to_appinfo_yaml_file))
   {
      Blast::Errors::throw_error(
         "Blast::Project::SourceReleaseBuilder::get_project_appinfo_yaml_file_contents",
         "The file \"" + full_path_to_appinfo_yaml_file + "\" does not exist."
      );
   }

   std::string contents = read_contents_of_file(full_path_to_appinfo_yaml_file);

   std::cout << "==========" << std::endl;
   std::cout << " path: " << full_path_to_appinfo_yaml_file << std::endl;
   std::cout << " contents: " << std::endl;
   std::cout << contents << std::endl;
   std::cout << "==========" << std::endl;

   return contents;

   //return read_contents_of_file(full_path_to_appinfo_yaml_file);
   //project_appinfo_yaml_filename
   // TODO: Replace this with an object so that the values can be symmetrically extracted
   //Blast::Project::SourceReleaseAppInfoFile app_info_file;
   //app_info_file.set_app_icon_filename("data/icons/golf-icon-01.png");
   //return app_info_file.get_contents();
}

std::string SourceReleaseBuilder::build_source_release_app_info_file_contents()
{
   YAML::Node node = YAML::Load(get_project_appinfo_yaml_file_contents());
   Blast::Project::SourceReleaseAppInfoFile result_app_info_file;

   std::string KEY = "app_icon_filename";
   bool key_exists = Blast::YAMLValidator::validate_presence_of_key(node, KEY, false);
   if (!key_exists)
   {
      Blast::Errors::throw_error(
         "Blast::Project::SourceReleaseBuilder::build_source_release_app_info_file_contents",
         "The key \"" + KEY + "\" does not exist in the file."
      );
   }
   else
   {
      // TODO: Replace this with an object so that the values can be symmetrically extracted
      //Blast::Project::SourceReleaseAppInfoFile result_app_info_file;
      std::string app_icon_filename = node[KEY].as<std::string>();
      
      result_app_info_file.set_app_icon_filename(app_icon_filename); //"data/icons/golf-icon-01.png");
   }

   return result_app_info_file.get_contents();
}

std::vector<std::pair<std::string, std::string>> SourceReleaseBuilder::list_symlinks()
{
   // TODO: This process iterates through every folder in the "Releases" folder, not sure this
   // does what it's supposed to
   std::string command = std::string("find ") + releases_base_folder;
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
   Blast::Project::ProjectSymlinkFixer symlink_fixer(releases_base_folder);
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

std::string SourceReleaseBuilder::get_generated_source_release_zip_filename()
{
   if (!(build_process_completed_successfully))
   {
      std::stringstream error_message;
      error_message << "[SourceReleaseBuilder::get_generated_source_release_zip_filename]: error: guard \"build_process_completed_successfully\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SourceReleaseBuilder::get_generated_source_release_zip_filename: error: guard \"build_process_completed_successfully\" not met");
   }
   return generated_release_folder_name + ".zip";
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

bool SourceReleaseBuilder::generate_source_release()
{
   // global info
   build_process_completed_successfully = false;
   generated_release_folder_name = "";


   // TODO: validate destination folder does not already exist



   // options:
   bool validate_bin_programs_data_folder_from_source_exists = true;
   bool validate_readme_exists_in_source_folder = true;
   bool validate_zip_command_exists = true;
   bool check_for_hard_coded_paths = true;
   bool copy_allegro_flare_source_and_header_files_from_source = true;
   bool copy_allegro_flare_include_lib_nlohmann_json_from_source = true;
   bool copy_allegro_flare_include_lib_ordered_map_from_source = true;
   Blast::TimeStamper time_stamper;

   std::string source_directory = get_source_project_directory();
   std::string time_of_source_release = time_stamper.generate_now_timestamp_utc();




   if (check_for_hard_coded_paths)
   {
      Blast::Project::HardCodedPathInfrencer hard_coded_path_infrencer;
      //hard_coded_path_infrencer.set_project_directory("/Users/markoates/Repos/Pipeline");
      hard_coded_path_infrencer.set_project_directory(source_project_directory);
      std::pair<bool, std::vector<std::string>> hard_coded_path_check_result =
         hard_coded_path_infrencer.check_for_hard_coded_paths();

      bool hard_coded_paths_detected = (!hard_coded_path_check_result.first);
      if (hard_coded_paths_detected)
      {
         std::stringstream message;
         message << "Hard-coded paths were detected. The command used to detect:" << std::endl
                 << "===============================" << std::endl
                 << hard_coded_path_infrencer.get_git_command() << std::endl
                 << "===============================" << std::endl
                 << "Here are the detected locations of the hard-coded paths:" << std::endl
                 << std::endl
                 << "===============================" << std::endl;
                 for (auto &result : hard_coded_path_check_result.second)
                 {
                    message << result << std::endl;
                 }
         message << "===============================" << std::endl
                 << std::endl
                 ;

         Blast::Errors::throw_error(
            "Blast::Project::SourceReleaseBuilder::generate_source_release",
            message.str()
         );
      }
   }



   // Increment the version.yml in the source repo location
   // TODO: Test this process
   // TODO: Offer a version alternative when no "version.yml" file is present... create new? etc...
   std::string expected_version_yml_filename = source_directory + "/version.yml";
   bool version_yaml_file_exists = Blast::FileExistenceChecker(expected_version_yml_filename).exists();
   Blast::VersionYAMLLoaderEmitter version_yaml_loader_emitter(expected_version_yml_filename);

   if (!version_yaml_file_exists)
   {
      // TODO: Add a configuration flag to make this throwing optional
      std::string message = "A \"version.yml\" file must be present but it not exist.";

      Blast::Errors::throw_error(
         "Blast::Project::SourceReleaseBuilder::generate_source_release",
         message
      );
   }
   else
   {
      // A "version.yml" file exists in this Repo. Increment the version and continue.
      std::cout << "[Blast::Project::SourceReleaseBuilder]: info: A \"version.yml\" file was found." << std::endl;

      version_yaml_loader_emitter.load();

      // TODO: Validate the current version is "wip" and can bump to a release number.

      std::cout << "[Blast::Project::SourceReleaseBuilder]: info: Current version (before release) is \""
                << version_yaml_loader_emitter.build_project_version_string() << "\". Incrementing..."
                << std::endl;

      version_yaml_loader_emitter.increment();
      version_yaml_loader_emitter.save();

      // TODO: Commit the version change file
      // TODO: ensure there are no dangling files in the repo before release

      std::cout << "[Blast::Project::SourceReleaseBuilder]: info: This release version is \""
                << version_yaml_loader_emitter.build_project_version_string() << "\"."
                << std::endl;
   }




   // TODO: Prompt the user if they would like to add "labels" or "metadata" to the version number



   // Now that the current version has been bumped to a release number, build the release info for this project
   Blast::ReleaseInfoBuilder release_info_builder(project_name);
   release_info = release_info_builder.build();
   if (version_yaml_file_exists)
   {
      // TODO: This value assignment should be handled in the Blast::ReleaseInfoBuilder instead, and not here
      release_info.set_version_number_major(version_yaml_loader_emitter.get_major());
      release_info.set_version_number_minor(version_yaml_loader_emitter.get_minor());
      release_info.set_version_number_patch(version_yaml_loader_emitter.get_patch());
      release_info.set_version_number_labels(version_yaml_loader_emitter.get_labels());
      release_info.set_version_number_metadata(version_yaml_loader_emitter.get_metadata());
   }


   release_info.set_time_of_source_release(time_of_source_release);

   // HERE


   std::string version_string = release_info.build_project_version_string();


   // !! WARNING: local variable name shadows class instance variable name:
   // !! WARNING: local variable name shadows class instance variable name:
   // !! WARNING: local variable name shadows class instance variable name:
   std::string generated_folder_name = get_project_name()
                                     + "-"
                                     + release_info.build_project_version_string()
                                     + "-SourceRelease";



   // TODO revert "version.yml" if there is a mistake


   std::string xxx = releases_base_folder + "/" + generated_folder_name;



   // TODO: Validate releases_folder_exists
   if (Blast::DirectoryExistenceChecker(xxx).exists())
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::SourceReleaseBuilder] error: The directory \""
                   << xxx
                   << "\" already exists.";
      throw std::runtime_error(error_message.str());
   }



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
      std::string expected_data_folder_location = source_directory + "/bin/data";
      Blast::DirectoryExistenceChecker checker(expected_data_folder_location);
      if (!checker.exists())
      {
         std::string message = "The expected bin/data folder does not exist. Expected at "
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


   if (validate_zip_command_exists)
   {
      // TODO: validate "zip" shell command exists
   }



   std::string destination_directory = xxx;



   std::stringstream copy_include_files_command;
   copy_include_files_command << "cp -R " << source_directory << "/include " << destination_directory << "/include";
   std::stringstream copy_src_files_command;
   copy_src_files_command << "cp -R " << source_directory << "/src " << destination_directory << "/src";
   std::stringstream copy_data_files_command;
   copy_data_files_command << "cp -R " << source_directory << "/bin/data " << destination_directory << "/data";
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

   std::cout << "Fixing symlinks from relative to absolute..." << std::flush;
   fix_symlink_targets_from_relative_to_absolute();
   std::cout << "done." << std::endl;

   std::cout << "Replacing sylminked files with original copies..." << std::flush;
   replace_symlinks_with_copies_of_linked_files();
   std::cout << "done." << std::endl;


   bool manually_copy_allegro_flare_headers_and_source_files = this->get_copy_allegro_flare_source();
   if (manually_copy_allegro_flare_headers_and_source_files)
   {
      /// Build commands

      // TODO: On this copy command, do not copy if any files will be overwritten
      // Do this with "-nR" instead of simply "-R". See:
      // https://chat.openai.com/c/a12a98e7-a3d5-47ab-8b8f-e2e6077ae106
      // headers
      std::string allegro_flare_include_directory = "/Users/markoates/Repos/allegro_flare/include/AllegroFlare/*";
      std::string allegro_flare_include_destination_directory = destination_directory + "/include/AllegroFlare";
      std::stringstream copy_allegro_flare_include_files_command;
      copy_allegro_flare_include_files_command << "cp -R "
         << allegro_flare_include_directory << " " << allegro_flare_include_destination_directory;

      // TODO: On this copy command, do not copy if any files will be overwritten
      // Do this with "-nR" instead of simply "-R". See:
      // https://chat.openai.com/c/a12a98e7-a3d5-47ab-8b8f-e2e6077ae106
      // src
      std::string allegro_flare_src_directory = "/Users/markoates/Repos/allegro_flare/src/AllegroFlare/*";
      std::string allegro_flare_src_destination_directory = destination_directory + "/src/AllegroFlare";
      std::stringstream copy_allegro_flare_src_files_command;
      copy_allegro_flare_src_files_command << "cp -R "
         << allegro_flare_src_directory << " " << allegro_flare_src_destination_directory;


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



   // In the SOURCE repo, re-increment the version number up to the next development version

   if (version_yaml_file_exists)
   {
      // A "version.yml" file exists in this Repo. Increment the version and continue.

      //Blast::VersionYAMLLoaderEmitter version_yaml_loader_emitter(expected_version_yml_filename);
      //version_yaml_loader_emitter.load();

      std::cout << "[Blast::Project::SourceReleaseBuilder]: info: Incrementing version of source repo to next "
                << "development version." << std::endl;

      version_yaml_loader_emitter.increment();
      version_yaml_loader_emitter.save();

      std::cout << "[Blast::Project::SourceReleaseBuilder]: info: Source repo is now at development version \""
                << version_yaml_loader_emitter.build_project_version_string() << "\"."
                << std::endl;
   }



   // Remove select, specific files via a black-list

   // TODO: Test this feature
   if (get_exclude_yaml_files_from_allegro_flare_source())
   {
      std::vector<std::string> blacklist_files = {
         destination_directory + "/include/AllegroFlare/DialogTree/YAMLLoader.hpp",
         destination_directory + "/src/AllegroFlare/DialogTree/YAMLLoader.cpp",

         destination_directory + "/include/AllegroFlare/AI/PromptTemplateYAMLLoader.hpp",
         destination_directory + "/src/AllegroFlare/AI/PromptTemplateYAMLLoader.cpp",

         destination_directory + "/include/AllegroFlare/YAMLValidator.hpp",
         destination_directory + "/src/AllegroFlare/YAMLValidator.cpp",
      };

      for (auto &blacklist_file : blacklist_files)
      {
         std::string item_to_remove = blacklist_file;
         recursively_remove_folder_with_prompt(item_to_remove);
      }
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


   if (get_remove_Testing_from_project_copy())
   {
      // TODO: Test this
      std::cout << "Looking in each top-level folder of \"include/\" and \"src/\" if they contain a \"Testing\" "
                << "folder." << std::endl;

      // 1) Get top-level folders within "include/" and "src/" folder
      std::vector<std::string> folders_in_include = get_top_level_folders_in_include(destination_directory);
      std::vector<std::string> folders_in_src = get_top_level_folders_in_src(destination_directory);

      // Ignore the "lib" folder if it exists in "include/" by removing it from the list
      // TODO: Test this case
      std::string lib_folder_to_look_for = "lib";
      if (
         std::find(folders_in_include.begin(), folders_in_include.end(), lib_folder_to_look_for)
         != folders_in_include.end())
      {
         std::cout << "Found a \"lib\" folder in \"include\". Ignoring it when looking for \"Testing\"."
                   << std::endl;
         std::string folder_to_remove = "lib";
         folders_in_include.erase(
            std::remove(folders_in_include.begin(), folders_in_include.end(), folder_to_remove),
            folders_in_include.end()
         );
      }

      // 2) Check they are identical lists (sanity check)
      std::sort(folders_in_include.begin(), folders_in_include.end());
      std::sort(folders_in_src.begin(), folders_in_src.end());

      std::vector<std::string> diff;
      std::set_difference(
         folders_in_include.begin(),
         folders_in_include.end(),
         folders_in_src.begin(),
         folders_in_src.end(),
         std::back_inserter(diff)
      );

      if (diff.empty())
      {
         // Cool, the two folder lists are identical
      }
      else
      {
         std::stringstream error_message;
         error_message << "[Project/ReleaseBuilder] error: When checking for \"Testing\" folders, expecting the "
                          "folders of \"include/\" and \"src/\" to have the same folder names but they contain "
                          "different elements.  The following elements are not in both: { ";
         for (auto &element : diff)
         {
            error_message << "\"" << element << "\", ";
         }
         error_message << "}.";
      
         throw std::runtime_error(error_message.str());
      }

      // 3) Collect each that have a Testing/ folder within them
      std::vector<std::string> possible_folder_names_to_check_for_existence;

      for (auto &folder : folders_in_include)
      {
         std::string include_folder_to_check = destination_directory + "/include/" + folder + "/Testing";
         std::string src_folder_to_check = destination_directory + "/src/" + folder + "/Testing";
         possible_folder_names_to_check_for_existence.push_back(include_folder_to_check);
         possible_folder_names_to_check_for_existence.push_back(src_folder_to_check);
      }

      std::vector<std::string> Testing_folders_to_remove;
      for (auto &possible_folder_name_to_check_for_existence : possible_folder_names_to_check_for_existence)
      {
         std::cout << "  - Checking in \"" << possible_folder_name_to_check_for_existence << "\" - ";
         if (Blast::DirectoryExistenceChecker(possible_folder_name_to_check_for_existence).exists())
         {
            Testing_folders_to_remove.push_back(possible_folder_name_to_check_for_existence);
            std::cout << " FOLDER EXISTS!" << std::endl;
         }
         else
         {
            std::cout << " folder does not exist" << std::endl;
         }
      }

      if (Testing_folders_to_remove.empty())
      {
         std::cout << "No extra \"Testing\" folders exist in these directories." << std::endl;
      }
      else
      {
         std::cout << "Some extra \"Testing\" folders were found. Removing..." << std::endl;

         for (auto &Testing_folder_to_remove : Testing_folders_to_remove)
         {
            // 4) Iterate over each one and remove it
            std::string folder_to_remove = Testing_folder_to_remove;
            recursively_remove_folder_with_prompt(folder_to_remove);
         }
      }
   }



   // Add version info source file(s)
   // Add the ReleeaseInfo.hpp header file
   std::string release_info_hpp_filename = destination_directory + "/include/ReleaseInfo.hpp";
   std::string release_info_header_file_contents = get_release_info_header_file_contents();
   write_file_contents(release_info_hpp_filename, release_info_header_file_contents);

   // Add the ReleeaseInfo.cpp source file
   std::string release_info_cpp_filename = destination_directory + "/src/ReleaseInfo.cpp";
   std::string release_info_source_file_contents = get_release_info_source_file_contents();
   write_file_contents(release_info_cpp_filename, release_info_source_file_contents);



   // Add the ReleeaseInfo.hpp header file
   std::string build_info_hpp_filename = destination_directory + "/include/BuildInfo.hpp";
   std::string build_info_header_file_contents = get_build_info_header_file_contents();
   write_file_contents(build_info_hpp_filename, build_info_header_file_contents);

   // Add the ReleeaseInfo.cpp source file
   std::string build_info_cpp_filename = destination_directory + "/src/BuildInfo.cpp";
   std::string build_info_source_file_contents = get_build_info_source_file_contents();
   write_file_contents(build_info_cpp_filename, build_info_source_file_contents);



   // Add the app info file for icons and titles
   // TODO: Just confirm there isn't already an "app.info" that might unintentionally get overwritten
   // TODO: Test 
   std::string app_info_file_filename = destination_directory
                                      + "/"
                                      + Blast::Project::SourceReleaseAppInfoFile::APP_INFO_FILENAME;
   std::string app_info_file_contents = build_source_release_app_info_file_contents();
   write_file_contents(app_info_file_filename, app_info_file_contents);



   // Zip up folder contents

   std::stringstream zip_release_folder_command;
   zip_release_folder_command << "(cd "
                              << releases_base_folder
                              << " && zip -r "
                              << generated_folder_name
                              << ".zip "
                              << generated_folder_name
                              << ")";
   std::cout << "Running zip command:" << std::endl;
   std::cout << "   " << zip_release_folder_command.str() << std::endl;
   Blast::ShellCommandExecutorWithCallback ordered_map_file_copy_executor(
         zip_release_folder_command.str(), ShellCommandExecutorWithCallback::simple_silent_callback
      );
   ordered_map_file_copy_executor.execute();



   // TODO: Upload the file to a google bucket

   // https://cloud.google.com/storage/docs/uploading-objects#storage-upload-object-code-sample




   // TODO: Write the info about the build to the "outgoing_build_file.txt"

   // /Users/markoates/Releases/outgoing_build_info.txt




   build_process_completed_successfully = true;
   generated_release_folder_name = generated_folder_name;


   return build_process_completed_successfully;
}

std::vector<std::string> SourceReleaseBuilder::get_top_level_folders_in_include(std::string directory)
{
   return get_top_level_folders(directory + "/include");
}

std::vector<std::string> SourceReleaseBuilder::get_top_level_folders_in_src(std::string directory)
{
   return get_top_level_folders(directory + "/src");
}

std::vector<std::string> SourceReleaseBuilder::get_top_level_folders(std::string directory)
{
   std::vector<std::string> result;

   for (const auto & entry : std::filesystem::directory_iterator(directory))
   {
      if (std::filesystem::is_directory(entry))
      {
         result.push_back(entry.path().filename().string());
      }
   }

   return result;
}


} // namespace Project
} // namespace Blast


