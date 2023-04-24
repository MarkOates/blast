

#include <Blast/Quintessence/YAMLParsers/FunctionArgumentParser.hpp>

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
   Blast::Cpp::FunctionArgument result;

   // YOUR CODE HERE

   return result;
}


} // namespace YAMLParsers
} // namespace Quintessence
} // namespace Blast


