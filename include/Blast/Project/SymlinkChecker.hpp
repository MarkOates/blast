#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class SymlinkChecker
      {
      private:
         std::string filename;

      public:
         SymlinkChecker(std::string filename="");
         ~SymlinkChecker();


      std::string read_symlink_target();
      };
   }
}



