

#include <Blast/Project/ComponentRelativeLister.hpp>
#include <Blast/Project/ComponentLister.hpp>
#include <sstream>


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
if (!component)
{
   std::stringstream error_message;
   error_message << "[Blast::Project::ComponentRelativeLister error] "
                 << "cannot list_component_relative_names with a nullptr component";
   throw std::runtime_error(error_message.str());
}

if (!component->exists())
{
   std::stringstream error_message;
   error_message << "[Blast::Project::ComponentRelativeLister error] "
                 << "cannot list_component_relative_names; The component \""
                 << component->get_name() << "\" does not exist";
   throw std::runtime_error(error_message.str());
}

Blast::Project::ComponentLister component_lister(component->get_project_root());

std::vector<std::string> entire_project_tree_component_names = component_lister.components();

return entire_project_tree_component_names;

}
} // namespace Project
} // namespace Blast


