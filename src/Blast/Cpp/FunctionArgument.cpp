

#include <Blast/Cpp/FunctionArgument.hpp>


namespace Blast
{


namespace Cpp
{


FunctionArgument::FunctionArgument(std::string type, std::string name, std::string default_value, std::vector<std::string> default_value_dependency_symbols)
   : type(type)
   , name(name)
   , default_value(default_value)
   , default_value_dependency_symbols(default_value_dependency_symbols)
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


std::vector<std::string> FunctionArgument::get_default_value_dependency_symbols()
{
   return default_value_dependency_symbols;
}



} // namespace Cpp


} // namespace Blast


