

#include <Blast/Project/ComponentListerNew.hpp>



namespace Blast
{
namespace Project
{


ComponentListerNew::ComponentListerNew(std::string project_root_directory)
   : project_root_directory(project_root_directory)
{
}


ComponentListerNew::~ComponentListerNew()
{
}


std::string ComponentListerNew::get_component_fragment_folder_name(Blast::Project::component_fragment_t component_fragment)
{
return "";

}

std::string ComponentListerNew::get_component_fragment_extension(Blast::Project::component_fragment_t component_fragment)
{
return "";

}

std::vector<std::string> ComponentListerNew::get_components_of_fragment_type(std::string project_root_directory, Blast::Project::component_fragment_t component_fragment)
{
return {};

}

std::vector<std::string> ComponentListerNew::components()
{
return {};

}
} // namespace Project
} // namespace Blast


