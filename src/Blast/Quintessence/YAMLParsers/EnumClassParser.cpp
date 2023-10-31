

#include <Blast/Quintessence/YAMLParsers/EnumClassParser.hpp>

#include <stdexcept>


namespace Blast
{
namespace Quintessence
{
namespace YAMLParsers
{


EnumClassParser::EnumClassParser(YAML::Node node)
   : Blast::YAMLValidator()
   , node(node)
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
   bool scope_node_is_present = (bool)node["scope"];
   if (scope_node_is_present) validate_node_type(node, "scope", YAML::NodeType::Scalar);
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
         error_message << "[Blast::Quintessence::YAMLParsers::EnumClassParser::parse]: error: "
                       << "An enum property \"start_from\" must be a valid number.";
                       // TODO: look into the Mark() function in YAML, which shoutd(?) provide data about the line
                       // number of the node
         throw std::runtime_error(error_message.str());
      }
   }

   // Extract the "start_from" value
   int start_from_value = 0;
   if (start_from_node_is_present)
   {
      std::string start_from_as_string = node["start_from"].as<std::string>();
      if (start_from_as_string.size() >= 3 && start_from_as_string.substr(0, 2) == "0x")
      {
         // The number is being represented as a hexidecimal. Parse the hex string into its integer value.
         std::string hexstr = start_from_as_string.substr(2);
         std::istringstream(hexstr) >> std::hex >> start_from_value;
      }
      else
      {
         start_from_value = node["start_from"].as<int>();
      }
   }

   // Extract the "bitwise" value (equivelent to "enumerators_are_bitwise" on the EnumClass)
   bool enumerators_are_bitwise_node_is_present = (bool)node["bitwise"];
   bool enumerators_are_bitwise_value = false;
   if (enumerators_are_bitwise_node_is_present)
   {
      // Validate node type
      validate_node_type(node, "bitwise", YAML::NodeType::Scalar);

      // Validate node value as "true" or "false"
      std::string val = node["bitwise"].as<std::string>();
      if (!(val == "true" || val == "false"))
      {
         // TODO: Test this error
         std::stringstream error_message;
         error_message << "[Blast::Quintessence::YAMLParsers::EnumClassParser::parse]: error: "
                       << "An enum property \"bitwise\" can only be \"true\" or \"false\".";
         throw std::runtime_error(error_message.str());
      }

      if (val == "true") enumerators_are_bitwise_value = true;

      // If enumerators_are_bitwise is true, then confirm start_from is a power of two. Note this error is also
      // handled at the EnumClass level, but is nice to have it here at this level to be consistent, and
      // Blast::Cpp::EnumClass is already a core dependency of this class
      if (enumerators_are_bitwise_value == true)
      {
         if (!Blast::Cpp::EnumClass::is_power_of_two(start_from_value))
         {
            // TODO: Test this error
            std::stringstream error_message;
            error_message << "[Blast::Quintessence::YAMLParsers::EnumClassParser::parse]: error: "
                          << "\"bitwise\" is set to true, thus \"start_from\" must be a valid bitfield number (e.g. "
                          << "a power of two, an int that represents values such as 0x04, 0x80, 0x1000, etc.), but "
                          << "is not.";
            throw std::runtime_error(error_message.str());
         }
      }
   }

   result.set_enumerators_are_bitwise(enumerators_are_bitwise_value);


   validate_presence_of_key(node, "enumerators");
   validate_node_type(node, "enumerators", YAML::NodeType::Sequence);

   // Extract the "class" and/or "name" value, along with the "is_class" property
   if (name_node_is_present && class_node_is_present)
   {
      std::stringstream error_message;
      error_message << "[Blast::Quintessence::YAMLParsers::EnumClassParser::parse]: error: "
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

   // Set the "start_from" value
   if (start_from_node_is_present) result.set_start_from(start_from_value);

   // Extract the "scope" value
   if (scope_node_is_present) result.set_scope(node["scope"].as<std::string>());

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


} // namespace YAMLParsers
} // namespace Quintessence
} // namespace Blast


