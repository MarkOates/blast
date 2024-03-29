#pragma once


#include <Blast/BuildInfo.hpp>
#include <Blast/ReleaseInfo.hpp>
#include <string>
#include <utility>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class SourceReleaseBuilder
      {
      public:
         static constexpr const char* APP_INFO_FILENAME = (char*)"app.info";

      private:
         std::string releases_base_folder;
         std::string project_name;
         std::string source_project_directory;
         std::string main_program_filename;
         std::string project_appinfo_yaml_filename;
         bool link_with_opengl;
         bool link_with_yaml_cpp;
         bool build_process_completed_successfully;
         std::string generated_release_folder_name;
         Blast::ReleaseInfo release_info;
         Blast::BuildInfo build_info;
         bool copy_allegro_flare_source;
         bool exclude_yaml_files_from_allegro_flare_source;
         bool copy_nlohmann_json_from_allegro_flare_source;
         bool copy_ordered_map_from_allegro_flare_source;
         bool remove_AllegroFlare_Network_from_allegro_flare_copy;
         bool remove_AllegroFlare_Network2_from_allegro_flare_copy;
         bool remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy;
         bool remove_AllegroFlare_Testing_from_allegro_flare_copy;
         bool remove_Testing_from_project_copy;
         bool prompt_before_deleting_unneeded_folders;

      protected:


      public:
         SourceReleaseBuilder(std::string releases_base_folder="/Users/markoates/Releases/", std::string project_name="Flowers", std::string source_project_directory="/Users/markoates/Repos/Flowers", std::string main_program_filename="programs/main.cpp", std::string project_appinfo_yaml_filename="appinfo.yml", bool link_with_opengl=true, bool link_with_yaml_cpp=false, bool copy_allegro_flare_source=true, bool exclude_yaml_files_from_allegro_flare_source=true, bool copy_nlohmann_json_from_allegro_flare_source=true, bool copy_ordered_map_from_allegro_flare_source=true, bool remove_AllegroFlare_Network_from_allegro_flare_copy=true, bool remove_AllegroFlare_Network2_from_allegro_flare_copy=true, bool remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy=true, bool remove_AllegroFlare_Testing_from_allegro_flare_copy=true, bool remove_Testing_from_project_copy=true, bool prompt_before_deleting_unneeded_folders=true);
         ~SourceReleaseBuilder();

         void set_link_with_opengl(bool link_with_opengl);
         void set_link_with_yaml_cpp(bool link_with_yaml_cpp);
         void set_copy_allegro_flare_source(bool copy_allegro_flare_source);
         void set_exclude_yaml_files_from_allegro_flare_source(bool exclude_yaml_files_from_allegro_flare_source);
         void set_copy_nlohmann_json_from_allegro_flare_source(bool copy_nlohmann_json_from_allegro_flare_source);
         void set_copy_ordered_map_from_allegro_flare_source(bool copy_ordered_map_from_allegro_flare_source);
         void set_remove_AllegroFlare_Network_from_allegro_flare_copy(bool remove_AllegroFlare_Network_from_allegro_flare_copy);
         void set_remove_AllegroFlare_Network2_from_allegro_flare_copy(bool remove_AllegroFlare_Network2_from_allegro_flare_copy);
         void set_remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy(bool remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy);
         void set_remove_AllegroFlare_Testing_from_allegro_flare_copy(bool remove_AllegroFlare_Testing_from_allegro_flare_copy);
         void set_remove_Testing_from_project_copy(bool remove_Testing_from_project_copy);
         void set_prompt_before_deleting_unneeded_folders(bool prompt_before_deleting_unneeded_folders);
         std::string get_project_name() const;
         std::string get_source_project_directory() const;
         std::string get_main_program_filename() const;
         std::string get_project_appinfo_yaml_filename() const;
         bool get_link_with_opengl() const;
         bool get_link_with_yaml_cpp() const;
         bool get_build_process_completed_successfully() const;
         std::string get_generated_release_folder_name() const;
         Blast::ReleaseInfo get_release_info() const;
         Blast::BuildInfo get_build_info() const;
         bool get_copy_allegro_flare_source() const;
         bool get_exclude_yaml_files_from_allegro_flare_source() const;
         bool get_copy_nlohmann_json_from_allegro_flare_source() const;
         bool get_copy_ordered_map_from_allegro_flare_source() const;
         bool get_remove_AllegroFlare_Network_from_allegro_flare_copy() const;
         bool get_remove_AllegroFlare_Network2_from_allegro_flare_copy() const;
         bool get_remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy() const;
         bool get_remove_AllegroFlare_Testing_from_allegro_flare_copy() const;
         bool get_remove_Testing_from_project_copy() const;
         bool get_prompt_before_deleting_unneeded_folders() const;
         void write_file_contents(std::string filename="", std::string file_contents="");
         std::string get_released_version_string();
         std::string get_makefile_content();
         std::string get_pinfo_content();
         std::string read_contents_of_file(std::string filePath="[unset-filePath]");
         void copy_file(std::string source_filename="", std::string destination_filename="");
         std::string get_release_info_header_file_contents();
         std::string get_release_info_source_file_contents();
         std::string get_build_info_header_file_contents();
         std::string get_build_info_source_file_contents();
         std::string get_project_appinfo_yaml_file_contents();
         std::string build_source_release_app_info_file_contents();
         std::vector<std::pair<std::string, std::string>> list_symlinks();
         void fix_symlink_targets_from_relative_to_absolute(std::string folder="[unset-folder]");
         void replace_symlinks_with_copies_of_linked_files();
         std::string get_generated_source_release_zip_filename();
         void generate_macos_release();
         void recursively_remove_folder_with_prompt(std::string folder_to_remove="/Users/markoates/Desktop/releases");
         bool generate_source_release();
         static std::vector<std::string> get_top_level_folders_in_include(std::string directory="[unset-directory]");
         static std::vector<std::string> get_top_level_folders_in_src(std::string directory="[unset-directory]");
         static std::vector<std::string> get_top_level_folders(std::string directory="[unset-directory]");
      };
   }
}



