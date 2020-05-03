#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class ProjectSymlinkFixer
      {
      private:
         std::string project_folder;

      public:
         ProjectSymlinkFixer(std::string project_folder=".");
         ~ProjectSymlinkFixer();


         std::string get_project_folder();
      bool starts_with(std::string source="", std::string string_to_find="");
      int has_one_line(std::string filename="");
      int line_count(std::string filename="");
      std::string read_file_firstline(std::string filename="");
      bool likely_an_intended_symlink(std::string filename="", std::string string_to_find="");
      std::string read_symlink(std::string filename="");
      void run();
      };
   }
}



