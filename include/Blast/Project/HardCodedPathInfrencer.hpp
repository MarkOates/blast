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
         static std::vector<std::string> remove_empty(std::vector<std::string> strVector={});

      protected:


      public:
         HardCodedPathInfrencer(std::string project_directory="/Users/markoates/Repos/Pipeline");
         ~HardCodedPathInfrencer();

         void set_project_directory(std::string project_directory);
         std::string get_project_directory() const;
         std::string get_git_command();
         std::pair<bool, std::vector<std::string>> check_for_hard_coded_paths();
         static std::vector<std::string> trim_each(std::vector<std::string> tokens={});
      };
   }
}



