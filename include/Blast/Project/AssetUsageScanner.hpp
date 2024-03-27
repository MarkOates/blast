#pragma once


#include <string>
#include <utility>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class AssetUsageScanner
      {
      private:
         std::string project_directory;
         static std::vector<std::string> remove_empty(std::vector<std::string> strVector={});

      protected:


      public:
         AssetUsageScanner(std::string project_directory="/Users/markoates/Repos/SomePlatformer");
         ~AssetUsageScanner();

         void set_project_directory(std::string project_directory);
         std::string get_project_directory() const;
         std::string get_git_command();
         std::pair<bool, std::vector<std::string>> check_for_prefixed_assets();
         static std::vector<std::string> trim_each(std::vector<std::string> tokens={});
      };
   }
}



