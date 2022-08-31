

#include <Blast/Project/ComponentDependencyLister.hpp>

#include <Blast/Project/ComponentLister.hpp>
#include <Blast/ProjectComponentFileTypes.hpp>
#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <yaml-cpp/yaml.h>


namespace Blast
{
namespace Project
{


ComponentDependencyLister::ComponentDependencyLister(Blast::Project::Component* component)
   : component(component)
{
}


ComponentDependencyLister::~ComponentDependencyLister()
{
}


std::vector<std::string> ComponentDependencyLister::list_component_dependency_names()
{
   if (!(component))
   {
      std::stringstream error_message;
      error_message << "ComponentDependencyLister" << "::" << "list_component_dependency_names" << ": error: " << "guard \"component\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::vector<std::string> results;

   // TODO: move this to guard
   if (!component->exists())
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::ComponentDependencyLister error] "
                    << "cannot list_component_dependency_names; The component \""
                    << component->get_name() << "\" does not exist";
      throw std::runtime_error(error_message.str());
   }

   if (!component->has_quintessence())
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::ComponentDependencyLister error] "
                    << "cannot list_component_dependency_names; The component \""
                    << component->get_name() << "\" must have a quintessence (until further support is added).";
      std::cout << error_message.str() << std::endl; //throw std::runtime_error(error_message.str());
      results.push_back("[only-supported-for-quintessence]");
      return results;
   }

   std::string quintessence_full_filename = get_component_quintessence_full_filename();
   YAML::Node loaded_file = YAML::LoadFile(quintessence_full_filename);
   YAML::Node dependencies = loaded_file["dependencies"];

   for(unsigned i=0; i<dependencies.size(); i++)
   {
      std::string scalar;
      const YAML::Node& node = dependencies[i]; //["symbol"] >> scalar;
      scalar = node["symbol"].as<std::string>();
      results.push_back(scalar);
   }

   return results;
}

std::string ComponentDependencyLister::get_component_quintessence_full_filename()
{
   if (!(component))
   {
      std::stringstream error_message;
      error_message << "ComponentDependencyLister" << "::" << "get_component_quintessence_full_filename" << ": error: " << "guard \"component\" not met";
      throw std::runtime_error(error_message.str());
   }
   std::string project_root = component->get_project_root();
   std::string component_name = component->get_name();
   Blast::ProjectComponentFileTypes::project_file_type_t type = Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE;
   std::string filename = Blast::ProjectComponentFilenameGenerator(component_name, type).generate_filename();
   std::string full_filename = project_root + filename;
   return full_filename;
}


} // namespace Project
} // namespace Blast


