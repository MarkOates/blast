

#include <Blast/CppClassGenerator.hpp>

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


CppClassGenerator::CppClassGenerator(std::string class_name, std::vector<ClassAttributeProperties> attribute_properties)
   : class_name(class_name)
   , attribute_properties(attribute_properties)
{
}


CppClassGenerator::~CppClassGenerator()
{
}


std::vector<ClassAttributeProperties> &CppClassGenerator::get_class_attribute_properties_ref()
{
   return attribute_properties;
}


std::vector<std::string> CppClassGenerator::constructor_declaration_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : attribute_properties)
      if (attribute_property.is_constructor_parameter) elements.push_back(attribute_property.as_constructor_argument_in_declaration());
   return elements;
}


std::vector<std::string> CppClassGenerator::constructor_definition_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : attribute_properties)
      if (attribute_property.is_constructor_parameter) elements.push_back(attribute_property.as_constructor_argument_in_definition());
   return elements;
}


std::vector<std::string> CppClassGenerator::initialization_list_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : attribute_properties)
      elements.push_back(attribute_property.as_argument_in_initialization_list());
   return elements;
}


std::string CppClassGenerator::header_filename()
{
   std::stringstream result;
   result << class_name << ".hpp";
   return result.str();
}


std::string CppClassGenerator::header_include_directive()
{
   std::stringstream result;
   result << "#include <Blast/" << header_filename() << ">\n";
   return result.str();
}


std::string CppClassGenerator::class_property_list(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : attribute_properties)
      result << std::string(3*indent_level, ' ') << attribute_property.as_class_property() << ";\n";
   return result.str();
}


std::string CppClassGenerator::getter_function_declarations(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : attribute_properties)
      if (attribute_property.has_getter) result << std::string(3*indent_level, ' ') << attribute_property.getter_function_declaration() << "\n";
   return result.str();
}


std::string CppClassGenerator::getter_function_definitions(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : attribute_properties)
      if (attribute_property.has_getter) result << std::string(3*indent_level, ' ') << attribute_property.getter_function_definition(class_name) << "\n\n";
   return result.str();
}


std::string CppClassGenerator::setter_function_declarations(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : attribute_properties)
      if (attribute_property.has_setter) result << std::string(3*indent_level, ' ') << attribute_property.setter_function_declaration() << "\n";
   return result.str();
}


std::string CppClassGenerator::setter_function_definitions(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : attribute_properties)
      if (attribute_property.has_setter) result << std::string(3*indent_level, ' ') << attribute_property.setter_function_definition(class_name) << "\n\n";
   return result.str();
}


std::string CppClassGenerator::initialization_list(int indent_level)
{
   std::stringstream result;
   std::vector<std::string> elements = initialization_list_elements();

   if (elements.empty()) return "";

   result << std::string(3*indent_level, ' ') << ": " << elements.front() << "\n";
   for (int i=1; i<elements.size(); i++) result << std::string(3*indent_level, ' ') << ", " << elements[i] << "\n";
   return result.str();
}


std::string CppClassGenerator::constructor_declaration(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << class_name << "(" << __join(constructor_declaration_elements()) << ");\n";
   return result.str();
}


std::string CppClassGenerator::constructor_definition(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << class_name << "::" << class_name << "(" << __join(constructor_definition_elements()) << ")\n"
      << initialization_list(indent_level+1)
      << std::string(3*indent_level, ' ') << "{\n" << std::string(3*indent_level, ' ') << "}\n";
   return result.str();
}


std::string CppClassGenerator::destructor_declaration(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "~" << class_name << "();\n";
   return result.str();
}


std::string CppClassGenerator::destructor_definition(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << class_name << "::~" << class_name << "()\n" << std::string(3*indent_level, ' ') << "{\n" << std::string(3*indent_level, ' ') << "}\n";
   return result.str();
}


std::string CppClassGenerator::generate_source_file_content()
{
   throw std::runtime_error("Not implemented");
   std::stringstream content;
   return content.str();
}


std::string CppClassGenerator::generate_header_file_content()
{
   throw std::runtime_error("Not implemented");
   std::stringstream content;
   return content.str();
}


std::string CppClassGenerator::generate_test_file_content()
{
   throw std::runtime_error("Not implemented");
   std::stringstream content;
   return content.str();
}


std::string CppClassGenerator::generate_example_file_content()
{
   throw std::runtime_error("Not implemented");
   std::stringstream content;
   return content.str();
}


