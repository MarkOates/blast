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
         ReleaseBuilder(std::string base_directory="");
         ~ReleaseBuilder();


      std::vector<std::pair<std::string, std::string>> list_symlinks();
      };
   }
}



