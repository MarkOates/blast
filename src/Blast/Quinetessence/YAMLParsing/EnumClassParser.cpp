

#include <Blast/Quinetessence/YAMLParsing/EnumClassParser.hpp>




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
     //include_undef_item: true (default)
     //to_string_func: true (default)
     //from_string_func: true (default)
     //to_int_func: false (default)
     //from_int_func: false (default)
     //items:
       //- RUNNING
       //- HIDING

   // Validate presence and type
   validate_presence_of_key(node, "name");
   validate_node_type(node, "name", YAML::NodeType::Scalar);
   validate_presence_of_key(node, "items");
   validate_node_type(node, "items", YAML::NodeType::Sequence);

   // Extract the "name" value
   result.set_enum_name(node["name"].as<std::string>());

   // Extract the "items" elements
   std::vector<std::string> enum_items;
   YAML::Node items_node = node["items"];
   for (std::size_t i=0; i<items_node.size(); i++)
   {
      // TODO: validate elements are all std::string and are of valid format (all caps, underscores, unique)
      std::string enum_item = items_node[i].as<std::string>();
      enum_items.push_back(enum_item);
   }

   // Set the "items" values
   result.set_elements(enum_items);

   return result;
}

bool EnumClassParser::validate_presence_of_key(YAML::Node node, std::string key, bool throw_on_error)
{
   // TODO: test this function
   if (node["name"]) return true;

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
   if (node["name"].Type() == expected_type) return true;

   // TODO: test this validators
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


} // namespace YAMLParsing
} // namespace Quinetessence
} // namespace Blast


