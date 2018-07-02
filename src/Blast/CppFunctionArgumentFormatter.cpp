

#include <Blast/CppFunctionArgumentFormatter.hpp>

#include <sstream>


namespace Blast
{


CppFunctionArgumentFormatter::CppFunctionArgumentFormatter(Blast::CppFunctionArgument function_argument)
   : function_argument(function_argument)
{
}


CppFunctionArgumentFormatter::~CppFunctionArgumentFormatter()
{
}


Blast::CppFunctionArgument CppFunctionArgumentFormatter::get_function_argument()
{
   return function_argument;
}


std::string CppFunctionArgumentFormatter::get_as_function_definition()
{
   std::stringstream result;
   result << function_argument.get_type() << " " << function_argument.get_name();
   return result.str();
}


std::string CppFunctionArgumentFormatter::get_as_function_declaration()
{
   std::stringstream result;
   result << function_argument.get_type() << " " << function_argument.get_name();
   if (!function_argument.get_default_value().empty()) result << "=" << function_argument.get_default_value();
   return result.str();
}


} // namespace Blast


