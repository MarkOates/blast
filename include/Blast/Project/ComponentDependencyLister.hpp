#pragma once


#include <Blast/Project/Component.hpp>
#include <string>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class ComponentDependencyLister
      {
      private:
         Blast::Project::Component* component;

      public:
         ComponentDependencyLister(Blast::Project::Component* component=nullptr);
         ~ComponentDependencyLister();

         std::vector<std::string> list_component_dependency_names();
      };
   }
}



