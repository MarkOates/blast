

#include <Blast/Project/ComponentListerNew.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <sstream>
#include <Blast/StringSplitter.hpp>


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
switch (component_fragment)
{
case COMPONENT_FRAGMENT_TYPE_HEADER:
   return "include";
   break;
case COMPONENT_FRAGMENT_TYPE_SOURCE:
   return "src";
   break;
case COMPONENT_FRAGMENT_TYPE_EXAMPLE:
   return "examples";
   break;
case COMPONENT_FRAGMENT_TYPE_TEST:
   return "tests";
   break;
case COMPONENT_FRAGMENT_TYPE_QUINTESSENCE:
   return "quintessence";
   break;
default:
   throw std::runtime_error("get_component_fragment_folder_name error: unaccounted for component_fragment_t");
   break;
}

}

std::string ComponentListerNew::get_component_fragment_extension(Blast::Project::component_fragment_t component_fragment)
{
switch (component_fragment)
{
case COMPONENT_FRAGMENT_TYPE_HEADER:
   return ".hpp";
   break;
case COMPONENT_FRAGMENT_TYPE_SOURCE:
   return ".cpp";
   break;
case COMPONENT_FRAGMENT_TYPE_EXAMPLE:
   return "Example.cpp";
   break;
case COMPONENT_FRAGMENT_TYPE_TEST:
   return "Test.cpp";
   break;
case COMPONENT_FRAGMENT_TYPE_QUINTESSENCE:
   return ".q.yml";
   break;
default:
   throw std::runtime_error("get_component_fragment_folder_name error: unaccounted for component_fragment_t");
   break;
}

}

std::vector<std::string> ComponentListerNew::get_components_of_fragment_type(std::string project_root_directory, Blast::Project::component_fragment_t component_fragment)
{
//component_fragment

std::stringstream find_command;
std::string fragment_folder_name = get_component_fragment_folder_name(component_fragment);
std::string fragment_extension = get_component_fragment_extension(component_fragment);
find_command << "cd " << project_root_directory << " && find " << fragment_folder_name << " -type f -name \"*" << fragment_extension << "\"";
Blast::ShellCommandExecutorWithCallback executor(find_command.str(), Blast::ShellCommandExecutorWithCallback::simple_silent_callback);
std::string executor_response = executor.execute();
StringSplitter splitter(executor_response, '\n');
std::vector<std::string> component_names_with_fragment = splitter.split();

return component_names_with_fragment;

}

std::vector<std::string> ComponentListerNew::components()
{
return {};

}
} // namespace Project
} // namespace Blast


