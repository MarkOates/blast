#pragma once


#include <string>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class ComponentLister
      {
      private:
         std::string project_root_directory;

      public:
         ComponentLister(std::string project_root_directory="");
         ~ComponentLister();


      std::vector<std::string> components();
      };
   }
}



