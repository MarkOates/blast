

#include <Blast/Project/ComponentRelativeLister.hpp>
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
return {};

}
} // namespace Project
} // namespace Blast


