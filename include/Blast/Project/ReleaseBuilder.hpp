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
         std::string base_directory;

      public:
         ReleaseBuilder(std::string base_directory="/Users/markoates/Desktop/Release");
         ~ReleaseBuilder();


      void copy_file(std::string source_filename="", std::string destination_filename="");
      std::vector<std::pair<std::string, std::string>> list_symlinks();
      void replace_symlinks_with_copies_of_linked_files();
      };
   }
}



