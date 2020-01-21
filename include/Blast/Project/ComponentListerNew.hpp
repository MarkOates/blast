#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class ComponentListerNew
      {
      private:
         std::string project_root_directory;

      public:
         ComponentListerNew(std::string project_root_directory="");
         ~ComponentListerNew();


      std::string run();
      };
   }
}



