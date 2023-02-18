

#include <Blast/Cpp/EnumClass.hpp>




namespace Blast
{
namespace Cpp
{


EnumClass::EnumClass(std::string enum_name, std::set<std::string> elements)
   : enum_name(enum_name)
   , elements(elements)
{
}


EnumClass::~EnumClass()
{
}


void EnumClass::set_enum_name(std::string enum_name)
{
   this->enum_name = enum_name;
}


void EnumClass::set_elements(std::set<std::string> elements)
{
   this->elements = elements;
}


std::string EnumClass::get_enum_name() const
{
   return enum_name;
}


std::set<std::string> EnumClass::get_elements() const
{
   return elements;
}




} // namespace Cpp
} // namespace Blast


