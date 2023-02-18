#pragma once


#include <Blast/Cpp/EnumClass.hpp>
#include <string>
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
            static bool validate_presence_of_key(YAML::Node node={}, std::string key="[unset-key]", bool throw_on_error=false);
            static bool validate_node_type(YAML::Node node={}, std::string key="[unset-key]", YAML::NodeType::value expected_type=YAML::NodeType::Undefined, bool throw_on_error=false);
            static std::string yaml_node_type_as_string(YAML::NodeType::value node_type=YAML::NodeType::Undefined);
         };
      }
   }
}



