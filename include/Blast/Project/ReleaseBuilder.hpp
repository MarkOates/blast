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
         std::string destination_directory;
         std::string source_project_directory;

      public:
         ReleaseBuilder(std::string destination_directory="/Users/markoates/Desktop/Flower.app");
         ~ReleaseBuilder();


         std::string get_source_project_directory();
      void write_file_contents(std::string filename="", std::string file_contents="");
      std::string get_makefile_content();
      void copy_file(std::string source_filename="", std::string destination_filename="");
      std::vector<std::pair<std::string, std::string>> list_symlinks();
      void replace_symlinks_with_copies_of_linked_files();
      void generate_macos_release();
      void generate_source_release();
      };
   }
}



