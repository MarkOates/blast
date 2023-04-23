#pragma once


#include <Blast/Cpp/EnumClass.hpp>
#include <Blast/YAMLValidator.hpp>
#include <yaml-cpp/yaml.h>


namespace Blast
{
   namespace Quinetessence
   {
      namespace YAMLParsing
      {
         class EnumClassParser : public Blast::YAMLValidator
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
         };
      }
   }
}



