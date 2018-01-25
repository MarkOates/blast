

#include <Blast/ClassGenerator.hpp>

#include <iostream>


int main(int argc, char **argv)
{
   CppClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_argument, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, false, true, false },
      { "std::string", "name", "\"[unnamed]\"", false, false, true, true },
      { "std::string", "type", "\"[untyped]\"", false, true, true, true },
   });

   class_generator.constructor_declaration_elements();
   class_generator.constructor_definition_elements();
   std::cout << class_generator.generate_header_file_contnet();

   return 0;
}


