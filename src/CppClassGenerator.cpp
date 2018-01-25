

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


namespace Blast
{


CppClassGenerator::CppClassGenerator(std::string class_name, std::vector<ClassAttributeProperties> attribute_properties, std::vector<Blast::SymbolDependencies> symbol_dependencies)
   : class_name(class_name)
   , attribute_properties(attribute_properties)
   , symbol_dependencies(symbol_dependencies)
{
}


CppClassGenerator::~CppClassGenerator()
{
}


std::vector<ClassAttributeProperties> &CppClassGenerator::get_class_attribute_properties_ref()
{
   return attribute_properties;
}


std::vector<SymbolDependencies> &CppClassGenerator::get_symbol_dependencies_ref()
{
   return symbol_dependencies;
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



void CppClassGenerator::set_class_name(std::string class_name)
{
   this->class_name = class_name;
}


std::string CppClassGenerator::get_class_name()
{
   return class_name;
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
   std::string source_file_template = R"END(

#include <Blast/HEADER_FILENAME>


CONSTRUCTOR


DESTRUCTOR


SETTER_FUNCTIONS
GETTER_FUNCTIONS
)END";

   std::string result = source_file_template;

   __replace(result, "HEADER_FILENAME", header_filename());
   __replace(result, "CONSTRUCTOR\n", constructor_definition(0));
   __replace(result, "DESTRUCTOR\n", destructor_definition(0));
   __replace(result, "SETTER_FUNCTIONS\n", setter_function_definitions(0));
   __replace(result, "GETTER_FUNCTIONS\n", getter_function_definitions(0));

   return result;
}


std::string CppClassGenerator::generate_header_file_content()
{
   std::string header_file_template = R"END(#pragma once


class CLASS_NAME
{
private:
PROPERTIES

public:
CONSTRUCTOR
DESTRUCTOR

SETTER_FUNCTIONS

GETTER_FUNCTIONS
};


)END";

   std::string result = header_file_template;

   __replace(result, "CLASS_NAME", class_name);
   __replace(result, "CONSTRUCTOR\n", constructor_declaration(1));
   __replace(result, "DESTRUCTOR\n", destructor_declaration(1));
   __replace(result, "PROPERTIES\n", class_property_list(1));
   __replace(result, "SETTER_FUNCTIONS\n", setter_function_declarations(1));
   __replace(result, "GETTER_FUNCTIONS\n", getter_function_declarations(1));

   return result;
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


} // namespace Blast


