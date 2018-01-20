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

   std::vector<std::string> constructor_declaration_elements();
   std::vector<std::string> constructor_definition_elements();
   std::vector<std::string> initialization_list_elements();

   std::string initialization_list();
   std::string constructor_declaration();
   std::string constructor_definition();
   std::string destructor_declaration();
   std::string destructor_definition();
};


