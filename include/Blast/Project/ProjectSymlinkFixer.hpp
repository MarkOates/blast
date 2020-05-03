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
      std::string run();
      };
   }
}



