

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
   return {};
}


} // namespace YAMLParsing
} // namespace Quinetessence
} // namespace Blast


