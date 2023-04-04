#pragma once


#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>


namespace Blast
{
   class YamlCppValidator
   {
   private:

   protected:


   public:
      YamlCppValidator();
      ~YamlCppValidator();

      static bool validate_presence_of_key(YAML::Node node={}, std::string key="[unset-key]", bool throw_on_error=true);
      static bool validate_node_type(YAML::Node node={}, std::string key="[unset-key]", YAML::NodeType::value expected_type=YAML::NodeType::Undefined, bool throw_on_error=true);
      static bool validate_node_has_unsigned_int_value(YAML::Node node={}, std::string key="[unset-key]");
      static bool validate_elements_are_unique(std::vector<std::string> elements={});
      static std::string yaml_node_type_as_string(YAML::NodeType::value node_type=YAML::NodeType::Undefined);
      static bool validate_unique_all_upper_identifiers(YAML::Node items={});
   };
}



