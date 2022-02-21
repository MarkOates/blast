#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class ComponentDependencyLister
      {
      private:

      public:
         ComponentDependencyLister();
         ~ComponentDependencyLister();

         std::string run();
      };
   }
}



