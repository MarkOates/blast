

#include <Blast/Quinetessence/YAMLParsing/EnumClassParser.hpp>

#include <Blast/Errors.hpp>
#include <algorithm>
#include <stdexcept>
#include <unordered_set>


namespace Blast
{
namespace Quinetessence
{
namespace YAMLParsing
{


EnumClassParser::EnumClassParser(YAML::Node node)
   : node(node)
{
}


EnumClassParser::~EnumClassParser()
{
}


void EnumClassParser::set_node(YAML::Node node)
{
   this->node = node;
}


YAML::Node EnumClassParser::get_node() const
{
   return node;
}


Blast::Cpp::EnumClass EnumClassParser::parse()
{
   Blast::Cpp::EnumClass result;

   // This is the schema:

   //- name: State
     //scope: protected
     //include_undef_item: true (default)
     //to_string_func: true (default)
     //from_string_func: true (default)
     //to_int_func: false (default)
     //from_int_func: false (default)
     //items:
       //- RUNNING
       //- HIDING

   // Validate presence and type
   bool class_node_is_present = (bool)node["class"];
   if (class_node_is_present) validate_node_type(node, "class", YAML::NodeType::Scalar);
   bool name_node_is_present = (bool)node["name"];
   if (name_node_is_present) validate_node_type(node, "name", YAML::NodeType::Scalar);
   bool type_node_is_present = (bool)node["type"];
   if (type_node_is_present) validate_node_type(node, "type", YAML::NodeType::Scalar);
   bool start_from_node_is_present = (bool)node["start_from"];
   if (start_from_node_is_present) validate_node_type(node, "start_from", YAML::NodeType::Scalar);
   if (start_from_node_is_present)
   {
      if (!validate_node_has_unsigned_int_value(node, "start_from"))
      {
         std::stringstream error_message;
         error_message << "[Blast::Quinetessence::YAMLParsing::EnumClassParser::parse]: error: "
                       << "An enum property \"start_from\" must be a valid number.";
                       // TODO: look into the Mark() function in YAML, which shoutd(?) provide data about the line
                       // number of the node
         throw std::runtime_error(error_message.str());
      }
   }

   validate_presence_of_key(node, "enumerators");
   validate_node_type(node, "enumerators", YAML::NodeType::Sequence);

   // Extract the "class" and/or "name" value, along with the "is_class" property
   if (name_node_is_present && class_node_is_present)
   {
      std::stringstream error_message;
      error_message << "[Blast::Quinetessence::YAMLParsing::EnumClassParser::parse]: error: "
                    << "An enum cannot have both the \"name\" and \"class\" present. It must be one or neither.";
                    // TODO: look into the Mark() function in YAML, which should(?) provide data about the line
                    // number of the node
      throw std::runtime_error(error_message.str());
   }
   else if (class_node_is_present)
   {
      result.set_name(node["class"].as<std::string>());
      result.set_is_class(true);
   }
   else if (name_node_is_present)
   {
      result.set_name(node["name"].as<std::string>());
   }

   // Extract the "type" value
   if (type_node_is_present) result.set_type(node["type"].as<std::string>());

   // Extract the "start_from" value
   if (start_from_node_is_present) result.set_start_from(node["start_from"].as<int>());

   // Extract the "enumerators" elements
   std::vector<std::string> enum_enumerators;
   YAML::Node enumerators_node = node["enumerators"];
   validate_unique_all_upper_identifiers(enumerators_node);
   for (std::size_t i=0; i<enumerators_node.size(); i++)
   {
      // TODO: validate elements are all std::string and are of valid format (all caps, underscores, unique)
      std::string enum_item = enumerators_node[i].as<std::string>();
      enum_enumerators.push_back(enum_item);
   }

   // Set the "enumerators" values
   result.set_enumerators(enum_enumerators);

   return result;
}

bool EnumClassParser::validate_presence_of_key(YAML::Node node, std::string key, bool throw_on_error)
{
   // TODO: test this function
   if (node[key]) return true;

   if (throw_on_error)
   {
      std::stringstream error_message;
      error_message << "[Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_presence_of_key]: error: "
                    << "expecting to find node \"" << key << "\" but it is not present.";
      throw std::runtime_error(error_message.str());
   }
   return false;
}

bool EnumClassParser::validate_node_type(YAML::Node node, std::string key, YAML::NodeType::value expected_type, bool throw_on_error)
{
   if (node[key].Type() == expected_type) return true;

   // TODO: test these validators
   if (throw_on_error)
   {
      std::string name_of_type = yaml_node_type_as_string(expected_type);
      std::stringstream error_message;
      error_message << "[Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_node_type]: error: "
                    << "expecting to find node \"" << key << "\" as a \"" << name_of_type << "\", "
                    << "but it is a \"" << node[key] << "\".";
      throw std::runtime_error(error_message.str());
   }
   return false;
}

bool EnumClassParser::validate_node_has_unsigned_int_value(YAML::Node node, std::string key)
{
   if (!node[key].IsScalar()) return false;

   std::string str = node[key].as<std::string>();

   if (str.empty())
   {
      // An empty string is not a valid numerical string.
      return false;
   }
   else if (str[0] == '0')
   {
      // A numerical string cannot start with 0 unless it is only 0.
      if (str.length() == 1) return true;
      return false;
   }
   for (const char c : str) {
      if (!isdigit(c)) {
        // If any character is not a digit, then the string is not a valid numerical string.
        return false;
      }
   }

   return true;
}

bool EnumClassParser::validate_elements_are_unique(std::vector<std::string> elements)
{
   // TODO: test this function
   std::unordered_set<std::string> unique_set;
   for (const auto& element : elements)
   {
      if (!unique_set.insert(element).second)
      {
          return false;
      }
   }
   return true;
}

std::string EnumClassParser::yaml_node_type_as_string(YAML::NodeType::value node_type)
{
   // TODO: test this function
   switch(node_type)
   {
      case YAML::NodeType::Null: return "Null"; break;
      case YAML::NodeType::Scalar: return "Scalar"; break;
      case YAML::NodeType::Sequence: return "Sequence"; break;
      case YAML::NodeType::Map: return "Map"; break;
      case YAML::NodeType::Undefined: return "Undefined"; break;
      default: {
         std::stringstream error_message;
         error_message << "[Blast::Quinetessence::YAMLParsing::EnumClassParser::yaml_node_type_as_string]: error: "
                       << "Unhandled case for type \"" << node_type << "\"";
         throw std::runtime_error(error_message.str());
      } break;
   }
   return "";
}

bool EnumClassParser::validate_unique_all_upper_identifiers(YAML::Node items)
{
   // TODO: add exception messages to areas with return false
   if (!items.IsSequence())
   {
      std::string node_type_as_string = yaml_node_type_as_string(items["items"].Type());
      std::stringstream error_message;
      error_message
        << "Expecting node \"items\" to be a \"Sequence\" but it was a \""
        << node_type_as_string
        << "\".";

      Blast::Errors::throw_error(
        "Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_unique_all_upper_identifiers",
        error_message.str()
      );

      return false;
   }

   // Check that each string in the list meets the requirements
   for (const auto& item : items) {
      if (!item.IsScalar()) {
         return false;
      }

      const std::string& str = item.as<std::string>();
      if (str.empty() || !std::isupper(str[0])) {
         return false;
      }

      for (char c : str) {
         if (!std::isalnum(c) && c != '_') {
           return false;
         }
      }

      if (std::any_of(str.begin() + 1, str.end(), [](char c) { return std::isdigit(c); })) {
         return false;
      }
    }

    // All checks passed
    return true;
}


} // namespace YAMLParsing
} // namespace Quinetessence
} // namespace Blast


