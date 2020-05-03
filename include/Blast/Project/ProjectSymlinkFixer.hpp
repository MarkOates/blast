#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class ProjectSymlinkFixer
      {
      private:

      public:
         ProjectSymlinkFixer();
         ~ProjectSymlinkFixer();


      bool starts_with(std::string source="", std::string string_to_find="");
      int line_count(std::string filename="");
      std::string read_file_firstline(std::string filename="");
      bool likely_an_intended_symlink(std::string filename="", std::string string_to_find="");
      std::string read_symlink(std::string filename="");
      std::string run();
      };
   }
}



