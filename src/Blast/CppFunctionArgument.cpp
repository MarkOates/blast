

#include <Blast/CppFunctionArgument.hpp>


namespace Blast
{


CppFunctionArgument::CppFunctionArgument(std::string type, std::string name, std::string default_value)
   : type(type)
   , name(name)
   , default_value(default_value)
{
}


CppFunctionArgument::~CppFunctionArgument()
{
}


std::string CppFunctionArgument::get_type()
{
   return type;
}


std::string CppFunctionArgument::get_name()
{
   return name;
}


std::string CppFunctionArgument::get_default_value()
{
   return default_value;
}


} // namespace Blast


