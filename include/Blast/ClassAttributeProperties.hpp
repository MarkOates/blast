#pragma once


#include <string>
#include <vector>


class ClassAttributeProperties
{
public:
   std::string datatype;
   std::string variable_name;
   std::string initialization_value;
   bool is_static;
   bool is_constructor_parameter;
   bool has_getter;
   bool has_setter;

   ClassAttributeProperties(std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter);
   ~ClassAttributeProperties();

   std::string as_constructor_argument_in_declaration();
   std::string as_constructor_argument_in_definition();
   std::string as_argument_in_initialization_list();
   std::string as_class_property();
   std::string getter_function_declaration();
   std::string getter_function_definition(std::string class_name);
   std::string setter_function_declaration();
   std::string setter_function_definition(std::string class_name);
};


