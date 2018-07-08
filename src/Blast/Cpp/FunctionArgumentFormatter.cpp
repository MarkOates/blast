

#include <Blast/Cpp/FunctionArgumentFormatter.hpp>

#include <sstream>


namespace Blast
{


namespace Cpp
{


FunctionArgumentFormatter::FunctionArgumentFormatter(Blast::Cpp::FunctionArgument function_argument)
   : function_argument(function_argument)
{
}


FunctionArgumentFormatter::~FunctionArgumentFormatter()
{
}


Blast::Cpp::FunctionArgument FunctionArgumentFormatter::get_function_argument()
{
   return function_argument;
}


std::string FunctionArgumentFormatter::get_as_function_definition()
{
   std::stringstream result;
   result << function_argument.get_type() << " " << function_argument.get_name();
   return result.str();
}


std::string FunctionArgumentFormatter::get_as_function_declaration()
{
   std::stringstream result;
   result << function_argument.get_type() << " " << function_argument.get_name();
   if (!function_argument.get_default_value().empty()) result << "=" << function_argument.get_default_value();
   return result.str();
}


} // namespace Cpp


} // namespace Blast


