#pragma once


#include <Blast/Project/ComponentFragmentTypeEnum.hpp>
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

         std::string get_component_fragment_folder_name(Blast::Project::component_fragment_t component_fragment=COMPONENT_FRAGMENT_TYPE_UNDEFINED);
         std::string get_component_fragment_extension(Blast::Project::component_fragment_t component_fragment=COMPONENT_FRAGMENT_TYPE_UNDEFINED);
         std::vector<std::string> get_components_of_fragment_type(std::string project_root_directory="", Blast::Project::component_fragment_t component_fragment=COMPONENT_FRAGMENT_TYPE_UNDEFINED);
         std::vector<std::string> components_sorted_by_most_recent();
         std::vector<std::string> components();
      };
   }
}



