

#include <Blast/Cpp/FunctionArgument.hpp>


namespace Blast
{


namespace Cpp
{


FunctionArgument::FunctionArgument(std::string type, std::string name, std::string default_value)
   : type(type)
   , name(name)
   , default_value(default_value)
{
}


FunctionArgument::~FunctionArgument()
{
}


std::string FunctionArgument::get_type()
{
   return type;
}


std::string FunctionArgument::get_name()
{
   return name;
}


std::string FunctionArgument::get_default_value()
{
   return default_value;
}


} // namespace Cpp


} // namespace Blast


