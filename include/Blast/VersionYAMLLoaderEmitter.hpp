#pragma once


#include <Blast/YamlCppValidator.hpp>
#include <set>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>


namespace Blast
{
   class VersionYAMLLoaderEmitter : protected Blast::YamlCppValidator
   {
   private:
      std::string yaml_filename;
      YAML::Node root;
      int major;
      int minor;
      int patch;
      std::set<std::string> labels;
      std::set<std::string> metadata;
      bool loaded;

   protected:


   public:
      VersionYAMLLoaderEmitter(std::string yaml_filename="[unset-yaml_filename]");
      ~VersionYAMLLoaderEmitter();

      std::string get_yaml_filename() const;
      std::string load();
      void save();
      int get_major();
      int get_minor();
      int get_patch();
      std::set<std::string> get_labels();
      std::set<std::string> get_metadata();
      void increment();
      void validate_or_throw(YAML::Node node={}, std::string key="[unset-key]");
      void validate_or_throw_v(YAML::Node initial_node={}, std::vector<std::string> nested_keys={}, YAML::NodeType::value type=YAML::NodeType::Undefined);
   };
}



