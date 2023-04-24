#pragma once


#include <Blast/Cpp/FunctionArgument.hpp>
#include <Blast/YAMLValidator.hpp>
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
         };
      }
   }
}



