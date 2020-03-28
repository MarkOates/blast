

#include <Blast/Project/ComponentRelativeLister.hpp>



namespace Blast
{
namespace Project
{


ComponentRelativeLister::ComponentRelativeLister(Blast::Project::Component* component)
   : component(component)
{
}


ComponentRelativeLister::~ComponentRelativeLister()
{
}


std::vector<std::string> ComponentRelativeLister::list_component_relative_names()
{
return {};

}
} // namespace Project
} // namespace Blast


