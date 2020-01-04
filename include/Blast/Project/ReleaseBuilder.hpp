#pragma once


#include <string>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class ReleaseBuilder
      {
      private:
         std::string project_repo_name;
         std::string project_repo_base_path;

      public:
         ReleaseBuilder(std::string project_repo_name="", std::string project_repo_base_path="/Users/markoates/Repos/");
         ~ReleaseBuilder();


         std::string get_project_repo_base_path();
      std::vector<std::string> get_source_file_listings();
      std::vector<std::string> build_repo_base_path_directory_components();
      std::vector<std::string> build_include_folder_directory_components();
      std::vector<std::string> build_src_folder_directory_components();
      std::vector<std::string> build_data_folder_directory_components();
      void duplicate_source_files();
      void create_folders();
      };
   }
}



