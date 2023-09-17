#pragma once


#include <string>
#include <vector>


namespace Blast
{
   namespace Cpp
   {
      class ClassAttributes
      {
      public:
         std::string datatype;
         std::string variable_name;
         std::string initialization_value;
         bool is_static;
         bool is_constructor_parameter;
         bool has_getter;
         bool has_explicit_getter;
         bool has_getter_ref;
         bool has_setter;
         bool is_constexpr;
         bool is_exposed;

         ClassAttributes(
            std::string datatype,
            std::string variable_name,
            std::string initialization_value,
            bool is_static,
            bool is_constructor_parameter,
            bool has_getter,
            bool has_expicit_getter,
            bool has_getter_ref,
            bool has_setter,
            bool is_constexpr,
            bool is_exposed
         );
         ~ClassAttributes();

         bool infer_getter_with_const();
         std::string as_constructor_argument_in_declaration();
         std::string as_constructor_argument_in_definition();
         std::string as_argument_in_initialization_list();
         std::string as_class_property();
         std::string as_static_definition(std::string class_name);
         std::string getter_function_symbol();
         std::string getter_function_declaration();
         std::string getter_function_definition(std::string class_name);
         std::string getter_ref_function_symbol();
         std::string getter_ref_function_declaration();
         std::string getter_ref_function_definition(std::string class_name);
         std::string setter_function_symbol();
         std::string setter_function_declaration();
         std::string setter_function_definition(std::string class_name);
      };
   }
}


