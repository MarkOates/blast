

#include <Blast/CppFunctionFormatter.hpp>

#include <Blast/CppFunctionArgumentFormatter.hpp>
#include <Blast/StringJoiner.hpp>
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

   // format the args
   std::vector<std::string> function_arg_elements;
   for (auto &parameter : function.get_signature())
   {
      Blast::CppFunctionArgumentFormatter formatter(parameter);
      function_arg_elements.push_back(formatter.get_as_function_declaration());
   }

   // format the function
   if (function.get_is_static()) result << "static ";
   result << function.get_type() << " ";
   if (!class_name.empty()) result << class_name << "::";
   result << function.get_name() << "(" << Blast::StringJoiner(function_arg_elements, ", ").join() << ")";
   if (function.get_is_const()) result << " const";
   if (function.get_is_override()) result << " override";
   result << ';' << std::endl;

   return result.str();
}


std::string CppFunctionFormatter::get_function_definition()
{
   std::stringstream result;

   // format the args
   std::vector<std::string> function_arg_elements;
   for (auto &parameter : function.get_signature())
   {
      Blast::CppFunctionArgumentFormatter formatter(parameter);
      function_arg_elements.push_back(formatter.get_as_function_definition());
   }

   // format the function
   result << function.get_type() << " ";
   if (!class_name.empty()) result << class_name << "::";
   result << function.get_name() << "(" << Blast::StringJoiner(function_arg_elements, ", ").join() << ")";
   if (function.get_is_const()) result << " const";
   if (function.get_is_override()) result << " override";
   result << std::endl;
   result << '{' << std::endl;
   result << function.get_body() << std::endl;
   result << '}' << std::endl;

   return result.str();
}


} // namespace Blast


