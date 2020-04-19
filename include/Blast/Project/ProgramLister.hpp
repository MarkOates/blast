#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class ProgramLister
      {
      private:
         std::string project_root;

      public:
         ProgramLister(std::string project_root="");
         ~ProgramLister();


         std::string get_project_root();
      std::string run();
      };
   }
}



