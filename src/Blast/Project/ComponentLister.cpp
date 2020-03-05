

#include <Blast/Project/ComponentLister.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <sstream>
#include <Blast/StringSplitter.hpp>
#include <iostream>
#include <Blast/Project/Component.hpp>
#include <ctime>
#include <algorithm>
#include <Blast/Project/ComponentBasenameExtractor.hpp>
#include <algorithm>
#include <algorithm>


namespace Blast
{
namespace Project
{


ComponentLister::ComponentLister(std::string project_root_directory)
   : project_root_directory(project_root_directory)
{
}


ComponentLister::~ComponentLister()
{
}


std::string ComponentLister::get_component_fragment_folder_name(Blast::Project::component_fragment_t component_fragment)
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

std::string ComponentLister::get_component_fragment_extension(Blast::Project::component_fragment_t component_fragment)
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

std::vector<std::string> ComponentLister::get_components_of_fragment_type(std::string project_root_directory, Blast::Project::component_fragment_t component_fragment)
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

std::vector<std::string> ComponentLister::components_sorted_by_most_recent()
{
std::vector<std::string> result = {};
std::vector<std::string> unsorted_components = components();
std::vector<std::pair<std::time_t, std::string>> intermediate_list_for_sorting = {};

for (auto &component_name : unsorted_components)
{
   Blast::Project::Component component(component_name, project_root_directory);
   std::time_t component_last_write_time = component.last_write_time();
   intermediate_list_for_sorting.push_back({ component_last_write_time, component_name });
}

std::sort(intermediate_list_for_sorting.begin(), intermediate_list_for_sorting.end());

for (auto &component : intermediate_list_for_sorting)
{
   std::cout << component.second << " << " << component.first << std::endl;
   result.push_back(component.second);
}

return result;

}

std::vector<std::string> ComponentLister::components()
{
std::vector<std::string> result = {};

//std::cerr << "WARNING: This function does NOT vaildate the passed project_root_directory "
   //<< "and injects it directly into a shell command.  This needs to be fixed."
   //<< std::endl;

std::vector<component_fragment_t> fragments_to_look_for = {
   COMPONENT_FRAGMENT_TYPE_HEADER,
   COMPONENT_FRAGMENT_TYPE_SOURCE,
   COMPONENT_FRAGMENT_TYPE_EXAMPLE,
   COMPONENT_FRAGMENT_TYPE_TEST,
   COMPONENT_FRAGMENT_TYPE_QUINTESSENCE,
};

for (auto &fragment_to_look_for : fragments_to_look_for)
{
   std::vector<std::string> fragment_component_names= get_components_of_fragment_type(project_root_directory, fragment_to_look_for);

   for (auto &item : fragment_component_names)
   {
      Blast::Project::ComponentBasenameExtractor extractor(item);
      result.push_back(extractor.identify_component_basename());
   }
}

std::sort(result.begin(), result.end());
std::vector<std::string>::iterator it = std::unique(result.begin(), result.end());
result.resize(std::distance(result.begin(), it));

return result;

}
} // namespace Project
} // namespace Blast


