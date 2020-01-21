

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

std::vector<std::string> ComponentListerNew::components()
{
return {};

}
} // namespace Project
} // namespace Blast


