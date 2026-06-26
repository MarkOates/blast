#pragma once


#include <Blast/Cpp/Class.hpp>
#include <Blast/YAMLValidator.hpp>
#include <string>
#include <yaml-cpp/yaml.h>


namespace Blast
{
   namespace Quintessence
   {
      namespace YAMLParsers
      {
         class QuintessenceParser : public Blast::YAMLValidator
         {
         private:
            std::string quintessence_filename;
            YAML::Node node;

         protected:


         public:
            QuintessenceParser(std::string quintessence_filename="", YAML::Node node={});
            ~QuintessenceParser();

            void set_quintessence_filename(std::string quintessence_filename);
            void set_node(YAML::Node node);
            std::string get_quintessence_filename() const;
            YAML::Node get_node() const;
            Blast::Cpp::Class parse();
         };
      }
   }
}
