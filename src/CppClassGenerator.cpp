

#include <Blast/CppClassGenerator.hpp>

#include <set>
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


CppClassGenerator::CppClassGenerator(std::string class_name, std::vector<std::string> namespaces, std::vector<Blast::ParentClassProperties> parent_classes_properties, std::vector<ClassAttributeProperties> attribute_properties, std::vector<Blast::SymbolDependencies> symbol_dependencies)
   : class_name(class_name)
   , namespaces(namespaces)
   , parent_classes_properties(parent_classes_properties)
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
   for (auto &parent_class_properties : parent_classes_properties)
      elements.push_back(parent_class_properties.as_argument_in_initialization_list());
   for (auto &attribute_property : attribute_properties)
      if (!attribute_property.is_static) elements.push_back(attribute_property.as_argument_in_initialization_list());
   return elements;
}


std::vector<std::string> CppClassGenerator::class_declaration_opener_inheritence_elements()
{
   std::vector<std::string> elements;
   for (auto &parent_class_properties : parent_classes_properties)
      elements.push_back(parent_class_properties.as_class_inheritence_declaration());
   return elements;
}


std::vector<std::string> CppClassGenerator::static_attribute_definition_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : attribute_properties)
      if (attribute_property.is_static) elements.push_back(attribute_property.as_static_definition(class_name));
   return elements;
}


void CppClassGenerator::set_class_name(std::string class_name)
{
   this->class_name = class_name;
}


bool CppClassGenerator::has_parent_classes()
{
   return !parent_classes_properties.empty();
}


bool CppClassGenerator::has_namespaces()
{
   return !namespaces.empty();
}


std::string CppClassGenerator::private_scope_specifier(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "private:\n";
   return result.str();
}


std::string CppClassGenerator::public_scope_specifier(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "public:\n";
   return result.str();
}


std::string CppClassGenerator::protected_scope_specifier(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "protected:\n";
   return result.str();
}


std::string CppClassGenerator::get_class_name()
{
   return class_name;
}


std::string CppClassGenerator::namespaces_scope_opener(bool indented)
{
   std::stringstream result;
   int indentation_level = 0;
   for (auto &n : namespaces)
   {
      if (indented) result << std::string(3*indentation_level, ' ');
      result << "namespace " << n << "\n";
      if (indented) result << std::string(3*indentation_level, ' ');
      result << "{\n";
      if (indented) indentation_level++;
   }
   return result.str();
}


std::string CppClassGenerator::namespaces_scope_closer(bool indented, bool include_comment)
{
   std::stringstream result;
   for (int i=namespaces.size()-1; i>=0; i--)
   {
      std::string &n = namespaces[i];
      if (indented) result << std::string(3*i, ' ');
      result << "}";
      if (include_comment) result << " // namespace " << n;
      result << "\n";
   }
   return result.str();
}


std::string CppClassGenerator::class_declaration_inheritence_list()
{
   std::stringstream result;
   if (!has_parent_classes()) return "";

   result << " : ";
   for (int i=0; i<parent_classes_properties.size()-1; i++)
      result << parent_classes_properties[i].as_class_inheritence_declaration() << ", ";
   result << parent_classes_properties.back().as_class_inheritence_declaration();

   return result.str();
}


std::string CppClassGenerator::class_declaration_opener(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "class " << class_name << class_declaration_inheritence_list() << "\n" << std::string(3*indent_level, ' ') << "{\n";
   return result.str();
}


std::string CppClassGenerator::class_declaration_closer(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "};\n";
   return result.str();
}


std::string CppClassGenerator::header_filename()
{
   std::stringstream result;
   result << class_name << ".hpp";
   return result.str();
}


std::string CppClassGenerator::source_filename()
{
   std::stringstream result;
   result << class_name << ".cpp";
   return result.str();
}


std::string CppClassGenerator::header_include_directive(std::string project_name_camelcase)
{
   std::stringstream result;
   result << "#include <" << project_name_camelcase << "/" << header_filename() << ">\n";
   return result.str();
}


std::string CppClassGenerator::dependency_include_directives()
{
   std::stringstream result;

   std::set<std::string> symbol_dependency_header_directives;
   std::set<std::string> undefined_symbols;

   std::set<std::string> present_symbols;
   for (auto &attribute_property : attribute_properties) present_symbols.insert(attribute_property.datatype);
   for (auto &parent_class_properties : parent_classes_properties) present_symbols.insert(parent_class_properties.get_class_name());

   for (auto &present_symbol : present_symbols)
   {
      bool found = false;
      for (auto &individual_symbol_dependencies : symbol_dependencies)
      {
         if (individual_symbol_dependencies.is_symbol(present_symbol))
         {
            found = true;
            if (individual_symbol_dependencies.requires_header_files())
            {
               std::vector<std::string> include_directives = individual_symbol_dependencies.get_include_directives();
               std::copy(include_directives.begin(), include_directives.end(), std::inserter(symbol_dependency_header_directives, symbol_dependency_header_directives.end()));
            }
            break;
         }
      }

      if (!found) undefined_symbols.insert(present_symbol);
   }

   if (!undefined_symbols.empty())
   {
      std::stringstream error_message;
      error_message << "Undefined symbol for datatypes [ ";
      for (auto &undefined_symbol : undefined_symbols) error_message << "\"" << undefined_symbol << "\", ";
      error_message << " ]";
      throw std::runtime_error(error_message.str());
   }

   for (auto &symbol_dependency_header_directive : symbol_dependency_header_directives)
      result << symbol_dependency_header_directive << "\n";

   return result.str();
}


std::string CppClassGenerator::class_property_list(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : attribute_properties)
      result << std::string(3*indent_level, ' ') << attribute_property.as_class_property() << ";\n";
   return result.str();
}


std::string CppClassGenerator::static_attribute_definitions(int indent_level)
{
   std::stringstream result;
   for (auto &static_attribute_definition : static_attribute_definition_elements())
      result << std::string(3*indent_level, ' ') << static_attribute_definition << "\n\n\n";
   return result.str();
}


std::string CppClassGenerator::getter_function_declarations(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : attribute_properties)
      if (attribute_property.has_getter)
      {
         result << std::string(3*indent_level, ' ');
         result << attribute_property.getter_function_declaration() << "\n";
      }
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


std::string CppClassGenerator::generate_source_file_content(std::string project_name_camelcase)
{
   std::string source_file_template = R"END(

CLASS_HEADER_INCLUDE_DIRECTIVE


NAMESPACES_OPENER

CONSTRUCTOR


DESTRUCTOR


SETTER_FUNCTIONS
GETTER_FUNCTIONS
NAMESPACES_CLOSER

)END";

   std::string result = source_file_template;

   __replace(result, "NAMESPACES_OPENER", namespaces_scope_opener(false));
   __replace(result, "NAMESPACES_CLOSER", namespaces_scope_closer(false));
   __replace(result, "CLASS_HEADER_INCLUDE_DIRECTIVE\n", header_include_directive(project_name_camelcase));
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


DEPENDENCY_INCLUDE_DIRECTIVES

NAMESPACES_OPENER
CLASS_DECLARATION_OPENER
PRIVATE_SCOPE_SPECIFIER
PROPERTIES

PUBLIC_SCOPE_SPECIFIER
CONSTRUCTOR
DESTRUCTOR

SETTER_FUNCTIONS

GETTER_FUNCTIONS
CLASS_DECLARATION_CLOSER
NAMESPACES_CLOSER


)END";

   std::string result = header_file_template;

   int required_namespace_indentation_levels = namespaces.size();

   __replace(result, "NAMESPACES_OPENER\n", namespaces_scope_opener(true));
   __replace(result, "NAMESPACES_CLOSER", namespaces_scope_closer(true, false));
   __replace(result, "DEPENDENCY_INCLUDE_DIRECTIVES", dependency_include_directives());
   __replace(result, "CLASS_NAME", class_name);
   __replace(result, "CONSTRUCTOR\n", constructor_declaration(required_namespace_indentation_levels + 1));
   __replace(result, "DESTRUCTOR\n", destructor_declaration(required_namespace_indentation_levels + 1));
   __replace(result, "PROPERTIES\n", class_property_list(required_namespace_indentation_levels + 1));
   __replace(result, "SETTER_FUNCTIONS\n", setter_function_declarations(required_namespace_indentation_levels + 1));
   __replace(result, "GETTER_FUNCTIONS\n", getter_function_declarations(required_namespace_indentation_levels + 1));
   __replace(result, "CLASS_DECLARATION_OPENER\n", class_declaration_opener(required_namespace_indentation_levels));
   __replace(result, "CLASS_DECLARATION_CLOSER\n", class_declaration_closer(required_namespace_indentation_levels));
   __replace(result, "PRIVATE_SCOPE_SPECIFIER\n", private_scope_specifier(required_namespace_indentation_levels));
   __replace(result, "PUBLIC_SCOPE_SPECIFIER\n", public_scope_specifier(required_namespace_indentation_levels));

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


std::string CppClassGenerator::project_source_filepath()
{
   std::stringstream result;
   result << "src/" << source_filename();
   return result.str();
}


std::string CppClassGenerator::project_header_filepath(std::string project_name_camelcase)
{
   std::stringstream result;
   result << "include/" << project_name_camelcase << "/" << header_filename();
   return result.str();
}


} // namespace Blast


