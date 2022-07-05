#pragma once


#include <string>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class SourceReleaseBuilder
      {
      private:
         std::string destination_directory;
         std::string project_name;
         std::string source_project_directory;
         std::string main_program_filename;
         bool link_with_opengl;

      public:
         SourceReleaseBuilder(std::string destination_directory="/Users/markoates/Desktop/Release/", std::string project_name="Flowers", std::string source_project_directory="/Users/markoates/Repos/Flowers", std::string main_program_filename="programs/main.cpp", bool link_with_opengl=true);
         ~SourceReleaseBuilder();

         void set_link_with_opengl(bool link_with_opengl);
         std::string get_project_name();
         std::string get_source_project_directory();
         std::string get_main_program_filename();
         bool get_link_with_opengl();
         void write_file_contents(std::string filename="", std::string file_contents="");
         std::string get_makefile_content();
         std::string get_pinfo_content();
         void copy_file(std::string source_filename="", std::string destination_filename="");
         std::vector<std::pair<std::string, std::string>> list_symlinks();
         void fix_symlink_targets_from_relative_to_absolute();
         void replace_symlinks_with_copies_of_linked_files();
         void copy_allegro_flare_source_and_header_files_from_source();
         std::string get_source_release_folder_name();
         std::string get_macos_release_folder_name();
         std::string get_win64_release_folder_name();
         void generate_macos_release();
         void generate_source_release();
      };
   }
}



