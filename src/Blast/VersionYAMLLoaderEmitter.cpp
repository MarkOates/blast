

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


void VersionYAMLLoaderEmitter::load()
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

   // Assign the version numbers
   major = root["version"]["major"].as<int>();
   minor = root["version"]["minor"].as<int>();
   patch = root["version"]["patch"].as<int>();

   // Collect, validate, and assign the labels
   YAML::Node labels_node = root["version"]["labels"];
   std::set<std::string> labels_vec;
   for (auto it=labels_node.begin(); it!=labels_node.end(); it++)
   {
      labels_vec.insert(it->as<std::string>());
   }
   validate_labels_format(labels_vec);
   labels = labels_vec;

   // Collect, validate, and assign the metadata
   YAML::Node metadata_node = root["version"]["metadata"];
   std::set<std::string> metadata_vec;
   for (auto it=metadata_node.begin(); it!=metadata_node.end(); it++)
   {
      metadata_vec.insert(it->as<std::string>());
   }
   validate_labels_format(metadata_vec);
   metadata = metadata_vec;

   loaded = true;
   return;
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

   labels.clear();

   // If the patch version is even, add the "wip" label
   bool incremented_patch_version_is_even = (patch % 2 == 0);
   bool include_wip_label = incremented_patch_version_is_even;
   if (include_wip_label) labels.insert(INTERNAL_DEVELOPMENT_VERSION_LABEL);

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

bool VersionYAMLLoaderEmitter::validate_labels_format(std::set<std::string> labels)
{
   std::vector<std::string> invalid_labels;

   // Accumulate invalid labels
   for (auto &label : labels)
   {
      if (!is_valid_label(label)) invalid_labels.push_back(label);
   }

   // Throw error if there are invalid labels
   if (!invalid_labels.empty())
   {
      // Build and throw our error message
      std::stringstream error_message;
      error_message << "The following labels are invalid: ";
      for (auto &invalid_label : invalid_labels)
      {
         error_message << "\"" << invalid_label << "\", ";
      }
      Blast::Errors::throw_error("Blast::VersionYAMLLoaderEmitter", error_message.str());
   }
   return true;
}

void VersionYAMLLoaderEmitter::add_label(std::string label)
{
   if (!(is_valid_label(label)))
   {
      std::stringstream error_message;
      error_message << "[VersionYAMLLoaderEmitter::add_label]: error: guard \"is_valid_label(label)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionYAMLLoaderEmitter::add_label: error: guard \"is_valid_label(label)\" not met");
   }
   labels.insert(label);
   return;
}

void VersionYAMLLoaderEmitter::add_metadata(std::string metadata_element)
{
   if (!(is_valid_label(metadata_element)))
   {
      std::stringstream error_message;
      error_message << "[VersionYAMLLoaderEmitter::add_metadata]: error: guard \"is_valid_label(metadata_element)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionYAMLLoaderEmitter::add_metadata: error: guard \"is_valid_label(metadata_element)\" not met");
   }
   metadata.insert(metadata_element);
   return;
}

bool VersionYAMLLoaderEmitter::is_valid_label(std::string label)
{
   if (label.empty()) return false;

   // Check if first character is a letter
   if (!isalpha(label[0])) return false;

   for (char c : label)
   {
      // check if the character is not alphanumeric or underscore
      if (!isalnum(c) && c != '_') return false;

         // check if the character is uppercase
      if (isupper(c)) return false;
   }

   return true;
}


} // namespace Blast


