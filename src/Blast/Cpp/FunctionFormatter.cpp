

#include <Blast/Cpp/FunctionFormatter.hpp>

#include <Blast/Cpp/FunctionArgumentFormatter.hpp>
#include <Blast/StringJoiner.hpp>
#include <sstream>


namespace Blast
{


namespace Cpp
{


FunctionFormatter::FunctionFormatter(Blast::Cpp::Function function, std::string class_name)
    : function(function)
    , class_name(class_name)
{}


FunctionFormatter::~FunctionFormatter()
{
}


std::string FunctionFormatter::get_function_declaration()
{
   std::stringstream result;

   // format the args
   std::vector<std::string> function_arg_elements;
   for (auto &parameter : function.get_signature())
   {
      Blast::Cpp::FunctionArgumentFormatter formatter(parameter);
      function_arg_elements.push_back(formatter.get_as_function_declaration());
   }

   // format the function
   if (function.get_is_static()) result << "static ";
   if (function.get_is_virtual() || function.get_is_pure_virtual()) result << "virtual ";
   result << function.get_type() << " ";
   if (!class_name.empty()) result << class_name << "::";
   result << function.get_name() << "(" << Blast::StringJoiner(function_arg_elements, ", ").join() << ")";
   if (function.get_is_pure_virtual()) result << " = 0";
   if (function.get_is_const()) result << " const";
   if (function.get_is_override()) result << " override";
   result << ';' << std::endl;

   return result.str();
}


std::string FunctionFormatter::get_function_definition()
{
   std::stringstream result;

   if (function.get_is_pure_virtual()) return "";

   // format the args
   std::vector<std::string> function_arg_elements;
   for (auto &parameter : function.get_signature())
   {
      Blast::Cpp::FunctionArgumentFormatter formatter(parameter);
      function_arg_elements.push_back(formatter.get_as_function_definition());
   }

   // format the function
   result << function.get_type() << " ";
   if (!class_name.empty()) result << class_name << "::";
   result << function.get_name() << "(" << Blast::StringJoiner(function_arg_elements, ", ").join() << ")";
   if (function.get_is_const()) result << " const";
   result << std::endl;
   result << '{' << std::endl;
   result << function.get_body() << std::endl;
   result << '}' << std::endl;

   return result.str();
}


} // namespace Cpp


} // namespace Blast


