#pragma once


#include <string>


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


      std::pair<std::string, std::string> list_symlinks();
      };
   }
}



