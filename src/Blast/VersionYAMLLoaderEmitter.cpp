

#include <Blast/VersionYAMLLoaderEmitter.hpp>

#include <Blast/Errors.hpp>
#include <Blast/StringJoiner.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Blast
{


VersionYAMLLoaderEmitter::VersionYAMLLoaderEmitter(std::string yaml_filename)
   : yaml_filename(yaml_filename)
   , major(0)
   , minor(0)
   , patch(0)
   , labels({})
   , metadata({})
   , loaded(false)
{
}


VersionYAMLLoaderEmitter::~VersionYAMLLoaderEmitter()
{
}


std::string VersionYAMLLoaderEmitter::get_yaml_filename() const
{
   return yaml_filename;
}


std::string VersionYAMLLoaderEmitter::load()
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[VersionYAMLLoaderEmitter::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionYAMLLoaderEmitter::load: error: guard \"(!loaded)\" not met");
   }
   YAML::Node root = YAML::LoadFile(yaml_filename);

   validate_or_throw(root, "version");
   validate_or_throw_v(root, { "version", "major" });
   validate_or_throw_v(root, { "version", "minor" });
   validate_or_throw_v(root, { "version", "patch" });

   major = root["version"]["major"].as<int>();
   minor = root["version"]["minor"].as<int>();
   patch = root["version"]["patch"].as<int>();

   loaded = true;

   return "Hello World!";
}

int VersionYAMLLoaderEmitter::get_major()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[VersionYAMLLoaderEmitter::get_major]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionYAMLLoaderEmitter::get_major: error: guard \"loaded\" not met");
   }
   return major;
}

int VersionYAMLLoaderEmitter::get_minor()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[VersionYAMLLoaderEmitter::get_minor]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionYAMLLoaderEmitter::get_minor: error: guard \"loaded\" not met");
   }
   return minor;
}

int VersionYAMLLoaderEmitter::get_patch()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[VersionYAMLLoaderEmitter::get_patch]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionYAMLLoaderEmitter::get_patch: error: guard \"loaded\" not met");
   }
   return patch;
}

std::vector<std::string> VersionYAMLLoaderEmitter::get_labels()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[VersionYAMLLoaderEmitter::get_labels]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionYAMLLoaderEmitter::get_labels: error: guard \"loaded\" not met");
   }
   return labels;
}

std::vector<std::string> VersionYAMLLoaderEmitter::get_metadata()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[VersionYAMLLoaderEmitter::get_metadata]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionYAMLLoaderEmitter::get_metadata: error: guard \"loaded\" not met");
   }
   return metadata;
}

void VersionYAMLLoaderEmitter::validate_or_throw(YAML::Node node, std::string key)
{
   if (!node[key])
   {
      std::stringstream error_message;
      error_message << "Missing key in node. Expecting \"" << key << "\".";
      Blast::Errors::throw_error("Blast::VersionYAMLLoaderEmitter", error_message.str());
   }
   return;
}

void VersionYAMLLoaderEmitter::validate_or_throw_v(YAML::Node initial_node, std::vector<std::string> nested_keys)
{
   YAML::Node node = YAML::Clone(initial_node);

   std::vector<std::string> accumulated_keys;
   for (auto &nested_key : nested_keys)
   {
      accumulated_keys.push_back(nested_key);

      if (!node[nested_key])
      {
         // Wrap the accumulated keys in nice brackets and quotes
         for (auto &accumulated_key : accumulated_keys) accumulated_key = "[\"" + accumulated_key + "\"]";

         // Build and throw our error message
         std::stringstream error_message;
         error_message << "Missing key in node. Expecting node"
                       << Blast::StringJoiner(accumulated_keys, "").join()
                       << ".";
         Blast::Errors::throw_error("Blast::VersionYAMLLoaderEmitter", error_message.str());
      }

      node = node[nested_key];
   }
   return;
}


} // namespace Blast


