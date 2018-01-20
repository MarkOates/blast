

#include <Blast/ClassGenerator.hpp>

#include <sstream>
#include <iostream>


static std::string __join(std::vector<std::string> elements)
{
   if (elements.empty()) return "";

   std::stringstream result;
   for (int i=0; i<(int)(elements.size())-1; i++) result << elements[i] << ", ";
   result << elements.back();
   return result.str();
}


static void __replace(std::string &str, const std::string &find_str, const std::string &replace_str)
{
  std::string::size_type pos = 0u;

  while((pos = str.find(find_str, pos)) != std::string::npos)
  {
     str.replace(pos, find_str.length(), replace_str);
     pos += replace_str.length();
  }
}


ClassGenerator::ClassGenerator(std::string class_name, std::vector<ClassAttributeProperties> attribute_properties)
   : class_name(class_name)
   , attribute_properties(attribute_properties)
{
}


ClassGenerator::~ClassGenerator()
{
}


std::vector<std::string> ClassGenerator::constructor_declaration_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : attribute_properties)
      if (attribute_property.is_constructor_parameter) elements.push_back(attribute_property.as_constructor_argument_in_declaration());
   return elements;
}


std::vector<std::string> ClassGenerator::constructor_definition_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : attribute_properties)
      if (attribute_property.is_constructor_parameter) elements.push_back(attribute_property.as_constructor_argument_in_definition());
   return elements;
}


std::vector<std::string> ClassGenerator::initialization_list_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : attribute_properties)
      elements.push_back(attribute_property.as_argument_in_initialization_list());
   return elements;
}


std::string ClassGenerator::class_property_list()
{
   std::stringstream result;
   for (auto &attribute_property : attribute_properties)
      result << "   " << attribute_property.as_class_property() << ";\n";
   return result.str();
}


std::string ClassGenerator::initialization_list()
{
   std::stringstream result;
   std::vector<std::string> elements = initialization_list_elements();

   if (elements.empty()) return "";

   result << "   : " << elements.front() << "\n";
   for (int i=1; i<elements.size(); i++) result << "   , " << elements[i] << "\n";
   return result.str();
}


std::string ClassGenerator::constructor_declaration()
{
   std::stringstream result;
   result << class_name << "(" << __join(constructor_declaration_elements()) << ");";
   return result.str();
}


std::string ClassGenerator::constructor_definition()
{
   std::stringstream result;
   result << class_name << "::" << class_name << "(" << __join(constructor_definition_elements()) << ")\n"
      << initialization_list()
      << "{\n}\n";
   return result.str();
}


std::string ClassGenerator::destructor_declaration()
{
   std::stringstream result;
   result << "~" << class_name << "();";
   return result.str();
}


std::string ClassGenerator::destructor_definition()
{
   std::stringstream result;
   result << class_name << "::~" << class_name << "()\n{\n}\n";
   return result.str();
}


