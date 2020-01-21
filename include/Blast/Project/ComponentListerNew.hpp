#pragma once


#include <Blast/Project/ComponentFragmentTypeEnum.hpp>
#include <string>
#include <vector>


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


      std::string get_component_fragment_folder_name(Blast::Project::component_fragment_t component_fragment=COMPONENT_FRAGMENT_TYPE_UNDEFINED);
      std::string get_component_fragment_extension(Blast::Project::component_fragment_t component_fragment=COMPONENT_FRAGMENT_TYPE_UNDEFINED);
      std::vector<std::string> components();
      };
   }
}



