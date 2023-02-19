#pragma once


#include <Blast/Cpp/EnumClass.hpp>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>


namespace Blast
{
   namespace Quinetessence
   {
      namespace YAMLParsing
      {
         class EnumClassParser
         {
         private:
            YAML::Node node;

         protected:


         public:
            EnumClassParser(YAML::Node node={});
            ~EnumClassParser();

            void set_node(YAML::Node node);
            YAML::Node get_node() const;
            Blast::Cpp::EnumClass parse();
            static bool validate_presence_of_key(YAML::Node node={}, std::string key="[unset-key]", bool throw_on_error=true);
            static bool validate_node_type(YAML::Node node={}, std::string key="[unset-key]", YAML::NodeType::value expected_type=YAML::NodeType::Undefined, bool throw_on_error=true);
            static bool validate_elements_are_unique(std::vector<std::string> elements={});
            static std::string yaml_node_type_as_string(YAML::NodeType::value node_type=YAML::NodeType::Undefined);
            static bool validate_unique_all_upper_identifiers(YAML::Node items={});
         };
      }
   }
}



