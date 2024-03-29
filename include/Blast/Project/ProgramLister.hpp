#pragma once


#include <string>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class ProgramLister
      {
      private:
         std::string project_root;

      protected:


      public:
         ProgramLister(std::string project_root="");
         ~ProgramLister();

         std::string get_project_root() const;
         std::string build_program_lister_shell_command();
         std::vector<std::string> program_filenames();
      };
   }
}



