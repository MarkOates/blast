#pragma once


#include <string>
#include <utility>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class SourceReleaseBuilder
      {
      private:
         std::string releases_base_folder;
         std::string project_name;
         std::string source_project_directory;
         std::string main_program_filename;
         bool link_with_opengl;
         bool build_process_completed_successfully;
         std::string generated_release_folder_name;
         bool copy_allegro_flare_source;
         bool copy_nlohmann_json_from_allegro_flare_source;
         bool copy_ordered_map_from_allegro_flare_source;
         bool remove_AllegroFlare_Network_from_allegro_flare_copy;
         bool remove_AllegroFlare_Network2_from_allegro_flare_copy;
         bool remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy;
         bool remove_AllegroFlare_Testing_from_allegro_flare_copy;
         bool prompt_before_deleting_unneeded_folders;

      protected:


      public:
         SourceReleaseBuilder(std::string releases_base_folder="/Users/markoates/Releases/", std::string project_name="Flowers", std::string source_project_directory="/Users/markoates/Repos/Flowers", std::string main_program_filename="programs/main.cpp", bool link_with_opengl=true, bool copy_allegro_flare_source=true, bool copy_nlohmann_json_from_allegro_flare_source=true, bool copy_ordered_map_from_allegro_flare_source=true, bool remove_AllegroFlare_Network_from_allegro_flare_copy=true, bool remove_AllegroFlare_Network2_from_allegro_flare_copy=true, bool remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy=true, bool remove_AllegroFlare_Testing_from_allegro_flare_copy=true, bool prompt_before_deleting_unneeded_folders=true);
         ~SourceReleaseBuilder();

         void set_link_with_opengl(bool link_with_opengl);
         void set_copy_allegro_flare_source(bool copy_allegro_flare_source);
         void set_copy_nlohmann_json_from_allegro_flare_source(bool copy_nlohmann_json_from_allegro_flare_source);
         void set_copy_ordered_map_from_allegro_flare_source(bool copy_ordered_map_from_allegro_flare_source);
         void set_remove_AllegroFlare_Network_from_allegro_flare_copy(bool remove_AllegroFlare_Network_from_allegro_flare_copy);
         void set_remove_AllegroFlare_Network2_from_allegro_flare_copy(bool remove_AllegroFlare_Network2_from_allegro_flare_copy);
         void set_remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy(bool remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy);
         void set_remove_AllegroFlare_Testing_from_allegro_flare_copy(bool remove_AllegroFlare_Testing_from_allegro_flare_copy);
         void set_prompt_before_deleting_unneeded_folders(bool prompt_before_deleting_unneeded_folders);
         std::string get_project_name() const;
         std::string get_source_project_directory() const;
         std::string get_main_program_filename() const;
         bool get_link_with_opengl() const;
         bool get_build_process_completed_successfully() const;
         std::string get_generated_release_folder_name() const;
         bool get_copy_allegro_flare_source() const;
         bool get_copy_nlohmann_json_from_allegro_flare_source() const;
         bool get_copy_ordered_map_from_allegro_flare_source() const;
         bool get_remove_AllegroFlare_Network_from_allegro_flare_copy() const;
         bool get_remove_AllegroFlare_Network2_from_allegro_flare_copy() const;
         bool get_remove_AllegroFlare_Integrations_Network_from_allegro_flare_copy() const;
         bool get_remove_AllegroFlare_Testing_from_allegro_flare_copy() const;
         bool get_prompt_before_deleting_unneeded_folders() const;
         void write_file_contents(std::string filename="", std::string file_contents="");
         std::string get_makefile_content();
         std::string get_pinfo_content();
         void copy_file(std::string source_filename="", std::string destination_filename="");
         std::vector<std::pair<std::string, std::string>> list_symlinks();
         void fix_symlink_targets_from_relative_to_absolute();
         void replace_symlinks_with_copies_of_linked_files();
         std::string get_source_release_folder_name();
         std::string get_macos_release_folder_name();
         std::string get_win64_release_folder_name();
         void generate_macos_release();
         void recursively_remove_folder_with_prompt(std::string folder_to_remove="/Users/markoates/Desktop/releases");
         bool generate_source_release();
      };
   }
}



