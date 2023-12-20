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

      protected:


      public:
         HardCodedPathInfrencer();
         ~HardCodedPathInfrencer();

         std::string get_git_command();
         std::pair<bool, std::vector<std::string>> check_for_hard_coded_paths();
      };
   }
}



