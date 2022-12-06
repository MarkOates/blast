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
         bool debug_output;
         bool starts_with(std::string source="", std::string string_to_find="");

      protected:


      public:
         ProjectSymlinkFixer(std::string project_folder=".", bool debug_output=false);
         ~ProjectSymlinkFixer();

         void set_debug_output(bool debug_output);
         std::string get_project_folder() const;
         bool get_debug_output() const;
         int has_one_line(std::string filename="");
         std::string read_file_firstline(std::string filename="");
         bool likely_an_intended_symlink(std::string filename="", std::string string_to_find="");
         std::string read_symlink(std::string filename="");
         void run();
      };
   }
}



