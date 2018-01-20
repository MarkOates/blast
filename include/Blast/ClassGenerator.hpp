#pragma once


#include <Blast/ClassAttributeProperties.hpp>
#include <string>
#include <vector>


class ClassGenerator
{
private:
   std::string class_name;
   std::vector<ClassAttributeProperties> attribute_properties;

public:
   ClassGenerator(std::string class_name="ClassName", std::vector<ClassAttributeProperties> attribute_properties={});
   ~ClassGenerator();

   std::vector<ClassAttributeProperties> &get_class_attribute_properties_ref();

   std::vector<std::string> constructor_declaration_elements();
   std::vector<std::string> constructor_definition_elements();
   std::vector<std::string> initialization_list_elements();

   std::string class_property_list(int indent_level=0);
   std::string getter_function_declarations(int indent_level=0);
   std::string getter_function_definitions(int indent_level=0);
   std::string setter_function_declarations(int indent_level=0);
   std::string setter_function_definitions(int indent_level=0);
   std::string initialization_list(int indent_level=0);

   std::string constructor_declaration(int indent_level=0);
   std::string constructor_definition(int indent_level=0);
   std::string destructor_declaration(int indent_level=0);
   std::string destructor_definition(int indent_level=0);
};


