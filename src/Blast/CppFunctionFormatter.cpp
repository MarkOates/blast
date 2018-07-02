

#include <Blast/CppFunctionFormatter.hpp>

#include <sstream>


namespace Blast
{


CppFunctionFormatter::CppFunctionFormatter(Blast::CppFunction function, std::string class_name)
    : function(function)
    , class_name(class_name)
{}


CppFunctionFormatter::~CppFunctionFormatter()
{
}


std::string CppFunctionFormatter::get_function_declaration()
{
   std::stringstream result;

   if (function.get_is_static()) result << "static ";
   result << function.get_type() << " ";
   if (!class_name.empty()) result << class_name << "::";
   result << function.get_name() << "(...)";
   if (function.get_is_const()) result << " const";
   if (function.get_is_override()) result << " override";
   result << ';' << std::endl;

   return result.str();
}


std::string CppFunctionFormatter::get_function_definition()
{
   std::stringstream result;

   result << function.get_type() << " ";
   if (!class_name.empty()) result << class_name << "::";
   result << function.get_name() << "(...)";
   if (function.get_is_const()) result << " const";
   if (function.get_is_override()) result << " override";
   result << std::endl;
   result << '{' << std::endl;
   result << function.get_body() << std::endl;
   result << '}' << std::endl;

   return result.str();
}


} // namespace Blast


