#pragma once


#include <string>
#include <utility>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class HardCodedPathInfrencer
      {
      private:
         std::string project_directory;

      protected:


      public:
         HardCodedPathInfrencer(std::string project_directory="/Users/markoates/Repos/Pipeline");
         ~HardCodedPathInfrencer();

         void set_project_directory(std::string project_directory);
         std::string get_project_directory() const;
         std::string get_git_command();
         std::pair<bool, std::vector<std::string>> check_for_hard_coded_paths();
      };
   }
}



