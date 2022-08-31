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
         std::string get_component_quintessence_full_filename();

      protected:


      public:
         ComponentDependencyLister(Blast::Project::Component* component=nullptr);
         ~ComponentDependencyLister();

         std::vector<std::string> list_component_dependency_names();
      };
   }
}



