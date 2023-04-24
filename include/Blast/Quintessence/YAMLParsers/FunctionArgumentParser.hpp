#pragma once


#include <Blast/Cpp/FunctionArgument.hpp>
#include <Blast/YAMLValidator.hpp>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>


namespace Blast
{
   namespace Quintessence
   {
      namespace YAMLParsers
      {
         class FunctionArgumentParser : public Blast::YAMLValidator
         {
         private:
            YAML::Node node;

         protected:


         public:
            FunctionArgumentParser(YAML::Node node={});
            ~FunctionArgumentParser();

            void set_node(YAML::Node node);
            YAML::Node get_node() const;
            Blast::Cpp::FunctionArgument parse();
            std::vector<std::string> extract_default_argument_dependency_symbols(YAML::Node source={});
            YAML::Node fetch_node(YAML::Node* node=nullptr, std::string key="[unset-key]", YAML::NodeType::value expected_type=YAML::NodeType::Undefined, YAML::Node default_value={});
            void explode(std::string location="[unset-location]", std::string error_message="[unset-error_message]");
            void validate(bool value=false, std::string location="[unset-location]", std::string error_message="[unset-error_message]");
         };
      }
   }
}



