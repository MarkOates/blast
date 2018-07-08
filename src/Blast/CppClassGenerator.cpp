

#include <Blast/CppClassGenerator.hpp>

#include <Blast/CppFunctionFormatter.hpp>
#include <set>
#include <sstream>
#include <iostream>


template<typename Out>
void split(const std::string &s, char delim, Out result) {
   std::stringstream ss(s);
   std::string item;
   while (std::getline(ss, item, delim)) {
      *(result++) = item;
   }
}


std::vector<std::string> split(const std::string &s, char delim = ' ') {
   std::vector<std::string> elems;
   split(s, delim, std::back_inserter(elems));
   return elems;
}


static std::string __join(std::vector<std::string> elements, std::string delim=", ")
{
   if (elements.empty()) return "";

   std::stringstream result;
   for (int i=0; i<(int)(elements.size())-1; i++) result << elements[i] << delim;
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


CppClassGenerator::CppClassGenerator(CppClass cpp_class)
   : cpp_class(cpp_class)
{
}


CppClassGenerator::~CppClassGenerator()
{
}


std::vector<std::string> CppClassGenerator::constructor_declaration_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.is_constructor_parameter) elements.push_back(attribute_property.as_constructor_argument_in_declaration());
   return elements;
}


std::vector<std::string> CppClassGenerator::constructor_definition_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.is_constructor_parameter) elements.push_back(attribute_property.as_constructor_argument_in_definition());
   return elements;
}


std::vector<std::string> CppClassGenerator::initialization_list_elements()
{
   std::vector<std::string> elements;
   for (auto &parent_class_properties : cpp_class.get_parent_classes_properties())
      elements.push_back(parent_class_properties.as_argument_in_initialization_list());
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (!attribute_property.is_static) elements.push_back(attribute_property.as_argument_in_initialization_list());
   return elements;
}


std::vector<std::string> CppClassGenerator::class_declaration_opener_inheritence_elements()
{
   std::vector<std::string> elements;
   for (auto &parent_class_properties : cpp_class.get_parent_classes_properties())
      elements.push_back(parent_class_properties.as_class_inheritence_declaration());
   return elements;
}


std::vector<std::string> CppClassGenerator::function_body_dependency_include_directive_elements()
{
   std::vector<std::string> elements;
   
   for (auto &function_body_symbol_dependency : cpp_class.get_function_body_symbol_dependencies())
   {
      for (auto &include_header_file : function_body_symbol_dependency.get_include_directives())
      {
         elements.push_back(include_header_file);
      }
   }

   return elements;
}


std::vector<std::string> CppClassGenerator::static_attribute_definition_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.is_static) elements.push_back(attribute_property.as_static_definition(cpp_class.get_class_name()));
   return elements;
}


std::vector<std::string> CppClassGenerator::function_declaration_elements(int indent_level)
{
   std::vector<std::string> result;
   for (auto &function : cpp_class.get_functions())
      result.push_back(CppFunctionFormatter(function).get_function_declaration());
   return result;
}


std::vector<std::string> CppClassGenerator::function_definition_elements(int indent_level)
{
   std::vector<std::string> result;
   for (auto &function : cpp_class.get_functions())
      result.push_back(CppFunctionFormatter(function, cpp_class.get_class_name()).get_function_definition());
   return result;
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


std::string CppClassGenerator::namespaces_scope_opener(bool indented)
{
   std::stringstream result;
   int indentation_level = 0;
   for (auto &n : cpp_class.get_namespaces())
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
   std::vector<std::string> namespaces = cpp_class.get_namespaces();
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
   // ineffecient use of recalling this value, TODO optimize

   std::stringstream result;
   if (cpp_class.get_parent_classes_properties().empty()) return "";

   result << " : ";
   for (int i=0; i<cpp_class.get_parent_classes_properties().size()-1; i++)
      result << cpp_class.get_parent_classes_properties()[i].as_class_inheritence_declaration() << ", ";
   result << cpp_class.get_parent_classes_properties().back().as_class_inheritence_declaration();

   return result.str();
}


std::string CppClassGenerator::class_declaration_opener(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "class " << cpp_class.get_class_name() << class_declaration_inheritence_list() << "\n" << std::string(3*indent_level, ' ') << "{\n";
   return result.str();
}


std::string CppClassGenerator::function_body_dependency_include_directives(int indent_level)
{
   std::stringstream result;
   return __join(function_body_dependency_include_directive_elements(), "\n");
   return "";
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
   result << cpp_class.get_class_name() << ".hpp";
   return result.str();
}


std::string CppClassGenerator::source_filename()
{
   std::stringstream result;
   result << cpp_class.get_class_name() << ".cpp";
   return result.str();
}


std::string CppClassGenerator::header_include_directive()
{
   std::stringstream result;
   result << "#include <";
   for (unsigned i=0; i<cpp_class.get_namespaces().size(); i++)
   {
      result << cpp_class.get_namespaces()[i];
      if (i != (cpp_class.get_namespaces().size()-1)) result << "/";
   }
   result << "/" << header_filename() << ">\n";

   return result.str();
}


std::string CppClassGenerator::dependency_include_directives()
{
   std::stringstream result;

   std::set<std::string> symbol_dependency_header_directives;
   std::set<std::string> undefined_symbols;

   std::set<std::string> present_symbols;
   for (auto &attribute_property : cpp_class.get_attribute_properties()) present_symbols.insert(attribute_property.datatype);
   for (auto &parent_class_properties : cpp_class.get_parent_classes_properties()) present_symbols.insert(parent_class_properties.get_class_name());
   for (auto &function : cpp_class.get_functions())
   {
      present_symbols.insert(function.get_type());
      for (auto &parameter : function.get_signature()) present_symbols.insert(parameter.get_type());
   }

   for (auto &present_symbol : present_symbols)
   {
      bool found = false;
      for (auto &individual_symbol_dependencies : cpp_class.get_symbol_dependencies())
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
   for (auto &attribute_property : cpp_class.get_attribute_properties())
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
   for (auto &attribute_property : cpp_class.get_attribute_properties())
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
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.has_getter) result << std::string(3*indent_level, ' ') << attribute_property.getter_function_definition(cpp_class.get_class_name()) << "\n\n";
   return result.str();
}


std::string CppClassGenerator::getter_ref_function_declarations(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.has_getter_ref)
      {
         result << std::string(3*indent_level, ' ');
         result << attribute_property.getter_ref_function_declaration() << "\n";
      }
   return result.str();
}


std::string CppClassGenerator::getter_ref_function_definitions(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.has_getter_ref) result << std::string(3*indent_level, ' ') << attribute_property.getter_ref_function_definition(cpp_class.get_class_name()) << "\n\n";
   return result.str();
}


std::string CppClassGenerator::setter_function_declarations(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.has_setter) result << std::string(3*indent_level, ' ') << attribute_property.setter_function_declaration() << "\n";
   return result.str();
}


std::string CppClassGenerator::setter_function_definitions(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.has_setter) result << std::string(3*indent_level, ' ') << attribute_property.setter_function_definition(cpp_class.get_class_name()) << "\n\n";
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


std::string CppClassGenerator::function_declarations(int indent_level)
{
   std::stringstream result;
   for (auto &function_declaration_element : function_declaration_elements())
      result << std::string(3*indent_level, ' ') << function_declaration_element;
   return result.str();
}


std::string CppClassGenerator::function_definitions(int indent_level)
{
   std::stringstream result;
   std::vector<std::string> indented_results;

   for (auto &function_definition_element : function_definition_elements())
   {
      std::stringstream indented_result;
      std::vector<std::string> tokens = split(function_definition_element, '\n');
      for (auto &token : tokens)
      {
         indented_result << std::string(3*indent_level, ' ') << token << std::endl;
      }
      indented_results.push_back(indented_result.str());
   }

   return __join(indented_results, "\n");
}


std::string CppClassGenerator::constructor_declaration(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << cpp_class.get_class_name() << "(" << __join(constructor_declaration_elements()) << ");\n";
   return result.str();
}


std::string CppClassGenerator::constructor_definition(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << cpp_class.get_class_name() << "::" << cpp_class.get_class_name() << "(" << __join(constructor_definition_elements()) << ")\n"
      << initialization_list(indent_level+1)
      << std::string(3*indent_level, ' ') << "{\n" << std::string(3*indent_level, ' ') << "}\n";
   return result.str();
}


std::string CppClassGenerator::destructor_declaration(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "~" << cpp_class.get_class_name() << "();\n";
   return result.str();
}


std::string CppClassGenerator::destructor_definition(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << cpp_class.get_class_name() << "::~" << cpp_class.get_class_name() << "()\n" << std::string(3*indent_level, ' ') << "{\n" << std::string(3*indent_level, ' ') << "}\n";
   return result.str();
}


std::string CppClassGenerator::generate_source_file_content()
{
   std::string source_file_template = R"END(

CLASS_HEADER_INCLUDE_DIRECTIVE

FUNCTION_BODY_DEPENDENCY_INCLUDE_DIRECTIVES



NAMESPACES_OPENER

STATIC_ATTRIBUTE_DEFINITIONS
CONSTRUCTOR


DESTRUCTOR


SETTER_FUNCTIONS
GETTER_FUNCTIONS
GETTER_REF_FUNCTIONS
FUNCTION_DEFINITIONS
NAMESPACES_CLOSER

)END";

   std::string result = source_file_template;

   __replace(result, "STATIC_ATTRIBUTE_DEFINITIONS\n", static_attribute_definitions(false));
   __replace(result, "NAMESPACES_OPENER", namespaces_scope_opener(false));
   __replace(result, "NAMESPACES_CLOSER", namespaces_scope_closer(false));
   __replace(result, "CLASS_HEADER_INCLUDE_DIRECTIVE\n", header_include_directive());
   __replace(result, "FUNCTION_BODY_DEPENDENCY_INCLUDE_DIRECTIVES\n", function_body_dependency_include_directives());
   __replace(result, "HEADER_FILENAME", header_filename());
   __replace(result, "CONSTRUCTOR\n", constructor_definition(0));
   __replace(result, "DESTRUCTOR\n", destructor_definition(0));
   __replace(result, "SETTER_FUNCTIONS\n", setter_function_definitions(0));
   __replace(result, "GETTER_FUNCTIONS\n", getter_function_definitions(0));
   __replace(result, "FUNCTION_DEFINITIONS\n", function_definitions(0));
   __replace(result, "GETTER_REF_FUNCTIONS\n", getter_ref_function_definitions(0));

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
GETTER_REF_FUNCTIONS
FUNCTION_DECLARATIONS
CLASS_DECLARATION_CLOSER
NAMESPACES_CLOSER


)END";

   std::string result = header_file_template;

   int required_namespace_indentation_levels = cpp_class.get_namespaces().size();

   __replace(result, "NAMESPACES_OPENER\n", namespaces_scope_opener(true));
   __replace(result, "NAMESPACES_CLOSER", namespaces_scope_closer(true, false));
   __replace(result, "DEPENDENCY_INCLUDE_DIRECTIVES", dependency_include_directives());
   __replace(result, "CLASS_NAME", cpp_class.get_class_name());
   __replace(result, "CONSTRUCTOR\n", constructor_declaration(required_namespace_indentation_levels + 1));
   __replace(result, "DESTRUCTOR\n", destructor_declaration(required_namespace_indentation_levels + 1));
   __replace(result, "PROPERTIES\n", class_property_list(required_namespace_indentation_levels + 1));
   __replace(result, "SETTER_FUNCTIONS\n", setter_function_declarations(required_namespace_indentation_levels + 1));
   __replace(result, "GETTER_FUNCTIONS\n", getter_function_declarations(required_namespace_indentation_levels + 1));
   __replace(result, "GETTER_REF_FUNCTIONS\n", getter_ref_function_declarations(required_namespace_indentation_levels + 1));
   __replace(result, "CLASS_DECLARATION_OPENER\n", class_declaration_opener(required_namespace_indentation_levels));
   __replace(result, "CLASS_DECLARATION_CLOSER\n", class_declaration_closer(required_namespace_indentation_levels));
   __replace(result, "PRIVATE_SCOPE_SPECIFIER\n", private_scope_specifier(required_namespace_indentation_levels));
   __replace(result, "FUNCTION_DECLARATIONS\n", function_declarations(required_namespace_indentation_levels));
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
   result << "src";
   for (unsigned i=0; i<cpp_class.get_namespaces().size(); i++) result << "/" << cpp_class.get_namespaces()[i];
   result << "/" << source_filename();
   return result.str();
}


std::string CppClassGenerator::project_header_filepath()
{
   std::stringstream result;
   result << "include";
   for (unsigned i=0; i<cpp_class.get_namespaces().size(); i++) result << "/" << cpp_class.get_namespaces()[i];
   result << "/" << header_filename();
   return result.str();
}


} // namespace Blast


