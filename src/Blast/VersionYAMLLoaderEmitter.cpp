

#include <Blast/VersionYAMLLoaderEmitter.hpp>

#include <Blast/Errors.hpp>
#include <Blast/StringJoiner.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Blast
{


VersionYAMLLoaderEmitter::VersionYAMLLoaderEmitter(std::string yaml_filename)
   : Blast::YamlCppValidator()
   , yaml_filename(yaml_filename)
   , root()
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
   root = YAML::LoadFile(yaml_filename);

   validate_or_throw(root, "version");
   validate_or_throw_v(root, { "version", "major" });
   validate_or_throw_v(root, { "version", "minor" });
   validate_or_throw_v(root, { "version", "patch" });
   validate_or_throw_v(root, { "version", "labels" });
   validate_or_throw_v(root, { "version", "metadata" });

   major = root["version"]["major"].as<int>();
   minor = root["version"]["minor"].as<int>();
   patch = root["version"]["patch"].as<int>();

   loaded = true;

   return "Hello World!";
}

void VersionYAMLLoaderEmitter::save()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[VersionYAMLLoaderEmitter::save]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionYAMLLoaderEmitter::save: error: guard \"loaded\" not met");
   }
   std::ofstream fout(yaml_filename);
   YAML::Emitter emitter(fout);
   emitter << root;
   fout.close();
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

std::set<std::string> VersionYAMLLoaderEmitter::get_labels()
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

std::set<std::string> VersionYAMLLoaderEmitter::get_metadata()
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

void VersionYAMLLoaderEmitter::increment()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[VersionYAMLLoaderEmitter::increment]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionYAMLLoaderEmitter::increment: error: guard \"loaded\" not met");
   }
   static const std::string INTERNAL_DEVELOPMENT_VERSION_LABEL = "wip";

   // Increment the patch version
   patch++;

   // Update the YAML::Node "patch"
   root["version"]["patch"] = patch;

   // If the patch version is even, add the "wip" label
   bool incremented_patch_version_is_even = (patch % 2 == 0);
   bool include_wip_label = incremented_patch_version_is_even;
   if (include_wip_label) labels.insert(INTERNAL_DEVELOPMENT_VERSION_LABEL);
   else
   {
      // If the patch version is odd, remove the "wip" label if it's present
      auto it = labels.find(INTERNAL_DEVELOPMENT_VERSION_LABEL);
      if (it != labels.end()) labels.erase(INTERNAL_DEVELOPMENT_VERSION_LABEL);
   }

   // Update the YAML::Node "labels"
   std::vector<std::string> labels_as_vector(labels.begin(), labels.end());
   root["version"]["labels"] = labels_as_vector;

   return;
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

void VersionYAMLLoaderEmitter::validate_or_throw_v(YAML::Node initial_node, std::vector<std::string> nested_keys, YAML::NodeType::value type)
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

   if (node.Type())

   return;
}


} // namespace Blast


