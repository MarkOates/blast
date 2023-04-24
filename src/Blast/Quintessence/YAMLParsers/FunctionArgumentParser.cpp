

#include <Blast/Quintessence/YAMLParsers/FunctionArgumentParser.hpp>

#include <sstream>
#include <stdexcept>


namespace Blast
{
namespace Quintessence
{
namespace YAMLParsers
{


FunctionArgumentParser::FunctionArgumentParser(YAML::Node node)
   : Blast::YAMLValidator()
   , node(node)
{
}


FunctionArgumentParser::~FunctionArgumentParser()
{
}


void FunctionArgumentParser::set_node(YAML::Node node)
{
   this->node = node;
}


YAML::Node FunctionArgumentParser::get_node() const
{
   return node;
}


Blast::Cpp::FunctionArgument FunctionArgumentParser::parse()
{
   std::string this_func_name = "Blast::Quintessence::YAMLParsers::FunctionArgumentParser::parse";

   const std::string TYPE = "type";
   const std::string NAME = "name";
   const std::string DEFAULT_ARGUMENT = "default_argument";

   validate(node.IsMap(), this_func_name, "Unexpected sequence element in \"parameters\", expected to be of a YAML Map.");

   YAML::Node type_node = node.operator[](TYPE);
   YAML::Node name_node = node.operator[](NAME);
   YAML::Node default_argument_node = node.operator[](DEFAULT_ARGUMENT);

   validate(type_node.IsScalar(), this_func_name, "Unexpected type_node, expected to be of YAML type Scalar.");
   validate(name_node.IsScalar(), this_func_name, "Unexpected name_node, expected to be of YAML type Scalar.");
   validate(default_argument_node.IsScalar(), this_func_name, "Unexpected default_argument_node, expected to be of YAML type Scalar.");

   std::vector<std::string> default_value_dependency_symbols;
   // TODO:
   //std::vector<std::string> default_value_dependency_symbols = extract_default_argument_dependency_symbols(node);

   return Blast::Cpp::FunctionArgument(
         type_node.as<std::string>(),
         name_node.as<std::string>(),
         default_argument_node.as<std::string>(),
         default_value_dependency_symbols
   );
}

std::vector<std::string> FunctionArgumentParser::extract_default_argument_dependency_symbols(YAML::Node node)
{
   std::vector<std::string> result;
   // TODO: This function
   //const std::string DEPENDENCY_SYMBOLS = "default_argument_dependency_symbols";
   //std::vector<std::string> result;
   //YAML::Node dependency_symbols = fetch_node(source, DEPENDENCY_SYMBOLS, YAML::NodeType::Sequence, YAML::Load("[]"));
   //result = extract_sequence_as_string_array(dependency_symbols);
   return result;
}

void FunctionArgumentParser::explode(std::string location, std::string error_message)
{
   std::stringstream ss;
   ss << "[" << location << "] " << error_message;
   throw std::runtime_error(ss.str());
}

void FunctionArgumentParser::validate(bool value, std::string location, std::string error_message)
{
   if (!value) explode(location, error_message);
}


} // namespace YAMLParsers
} // namespace Quintessence
} // namespace Blast


