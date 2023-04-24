

#include <Blast/Cpp/ClassGenerator.hpp>

#include <Blast/Cpp/FunctionFormatter.hpp>
#include <Blast/Cpp/EnumClassFormatter.hpp>
#include <Blast/DependencySymbolAtomizer.hpp>
#include <Blast/DependencyHeadersSuggester.hpp>
#include <Blast/StringJoiner.hpp>
#include <set>
#include <unordered_set>
#include <sstream>
#include <iostream>
#include <algorithm> // for std::sort


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


static std::string __indent(int num_spaces, int indent_level, std::string non_split_line)
{
   std::stringstream result;
   std::vector<std::string> indented_results;

   std::stringstream indented_result;
   std::vector<std::string> tokens = split(non_split_line, '\n');
   for (auto &token : tokens)
   {
      indented_result << std::string(3*indent_level, ' ') << token << '\n';
   }
   indented_results.push_back(indented_result.str());

   return __join(indented_results, "\n");
}


namespace Blast
{


namespace Cpp
{


ClassGenerator::ClassGenerator(Class cpp_class)
   : cpp_class(cpp_class)
{
}


ClassGenerator::~ClassGenerator()
{
}


std::vector<std::string> ClassGenerator::constructor_declaration_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.is_constructor_parameter)
         elements.push_back(attribute_property.as_constructor_argument_in_declaration());
   return elements;
}


std::vector<std::string> ClassGenerator::constructor_definition_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.is_constructor_parameter)
         elements.push_back(attribute_property.as_constructor_argument_in_definition());
   return elements;
}


std::vector<std::string> ClassGenerator::initialization_list_elements()
{
   std::vector<std::string> elements;

   for (auto &parent_class_properties : cpp_class.get_parent_classes_properties())
      elements.push_back(parent_class_properties.as_argument_in_initialization_list());

   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (!attribute_property.is_static)
         elements.push_back(attribute_property.as_argument_in_initialization_list());

   return elements;
}


std::vector<std::string> ClassGenerator::class_declaration_opener_inheritence_elements()
{
   std::vector<std::string> elements;

   for (auto &parent_class_properties : cpp_class.get_parent_classes_properties())
      elements.push_back(parent_class_properties.as_class_inheritence_declaration());

   return elements;
}


std::vector<std::string> ClassGenerator::function_body_dependency_include_directive_elements()
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


std::vector<std::string> ClassGenerator::static_attribute_definition_elements()
{
   std::vector<std::string> elements;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
   {
      if (attribute_property.is_static && !attribute_property.is_constexpr)
      {
         elements.push_back(attribute_property.as_static_definition(cpp_class.get_class_name()));
      }
   }
   return elements;
}


std::vector<std::string> ClassGenerator::private_enum_class_declaration_elements(int indent_level)
{
   // TODO: test this function
   std::vector<std::string> result;
   for (auto &enum_class : cpp_class.get_enum_classes())
   {
      if (enum_class.is_private())
         result.push_back(EnumClassFormatter(enum_class).build_enum_definition());
   }
   return result;
}


std::vector<std::string> ClassGenerator::protected_enum_class_declaration_elements(int indent_level)
{
   // TODO: test this function
   std::vector<std::string> result;
   for (auto &enum_class : cpp_class.get_enum_classes())
   {
      if (enum_class.is_protected())
         result.push_back(EnumClassFormatter(enum_class).build_enum_definition());
   }
   return result;
}


std::vector<std::string> ClassGenerator::public_enum_class_declaration_elements(int indent_level)
{
   // TODO: test this function
   std::vector<std::string> result;
   for (auto &enum_class : cpp_class.get_enum_classes())
   {
      if (enum_class.is_public())
         result.push_back(EnumClassFormatter(enum_class).build_enum_definition());
   }
   return result;
}


std::vector<std::string> ClassGenerator::protected_function_declaration_elements(int indent_level)
{
   std::vector<std::string> protected_functions;
   for (auto &function : cpp_class.get_functions())
   {
      if (function.get_is_protected())
         protected_functions.push_back(FunctionFormatter(function).get_function_declaration());
   }
   // TODO: consider if "enum_classes" that have have "to_string" and "from_string" methods should have their
   // declarations included here. NOTE: I don't think they should. I think that should be assembled at
   // quintessence parsing time and added to the classes "functions" outside of here.
   return protected_functions;
}


std::vector<std::string> ClassGenerator::private_function_declaration_elements(int indent_level)
{
   std::vector<std::string> private_functions;
   for (auto &function : cpp_class.get_functions())
   {
      if (function.get_is_private())
         private_functions.push_back(FunctionFormatter(function).get_function_declaration());
   }
   return private_functions;
}


std::vector<std::string> ClassGenerator::public_function_declaration_elements(int indent_level)
{
   std::vector<std::string> public_functions;
   for (auto &function : cpp_class.get_functions())
   {
      if (!function.get_is_private() && !function.get_is_protected())
         public_functions.push_back(FunctionFormatter(function).get_function_declaration());
   }
   return public_functions;
}


std::vector<std::string> ClassGenerator::function_definition_elements(int indent_level)
{
   std::vector<std::string> result;
   for (auto &function : cpp_class.get_functions())
      result.push_back(FunctionFormatter(function, cpp_class.get_class_name()).get_function_definition());
   return result;
}


std::string ClassGenerator::private_scope_specifier(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "private:\n";
   return result.str();
}


std::string ClassGenerator::public_scope_specifier(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "public:\n";
   return result.str();
}


std::string ClassGenerator::protected_scope_specifier(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "protected:\n";
   return result.str();
}


std::string ClassGenerator::namespaces_scope_opener(bool indented)
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


std::string ClassGenerator::namespaces_scope_closer(bool indented, bool include_comment)
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


std::string ClassGenerator::class_declaration_inheritence_list()
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


std::string ClassGenerator::class_declaration_opener(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ')
          << "class "
          << cpp_class.get_class_name()
          << class_declaration_inheritence_list()
          << "\n" << std::string(3*indent_level, ' ')
          << "{\n";
   return result.str();
}


std::string ClassGenerator::function_body_dependency_include_directives(int indent_level)
{
   std::stringstream result;
   std::vector<std::string> elements = function_body_dependency_include_directive_elements();

   std::sort(elements.begin(), elements.end());
   auto last = std::unique(elements.begin(), elements.end());
   elements.erase(last, elements.end());

   return __join(elements, "\n");
   return "";
}


std::string ClassGenerator::class_declaration_closer(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << "};\n";
   return result.str();
}


std::string ClassGenerator::header_filename()
{
   std::stringstream result;
   result << cpp_class.get_class_name() << ".hpp";
   return result.str();
}


std::string ClassGenerator::source_filename()
{
   std::stringstream result;
   result << cpp_class.get_class_name() << ".cpp";
   return result.str();
}



std::string ClassGenerator::get_class_name_with_namespaces()
{
   std::stringstream result;
   std::vector<std::string> tokens;

   for (unsigned i=0; i<cpp_class.get_namespaces().size(); i++) tokens.push_back(cpp_class.get_namespaces()[i]);
   tokens.push_back(cpp_class.get_class_name());

   result << Blast::StringJoiner(tokens, "::").join();

   return result.str();
}



std::string ClassGenerator::header_include_directive()
{
   std::stringstream result;
   std::vector<std::string> tokens;

   for (unsigned i=0; i<cpp_class.get_namespaces().size(); i++) tokens.push_back(cpp_class.get_namespaces()[i]);
   tokens.push_back(header_filename());

   result << "#include <" << Blast::StringJoiner(tokens, "/").join() << ">";

   return result.str();
}


std::string ClassGenerator::dependency_include_directives()
{
   // result data
   std::stringstream result;
   std::set<std::string> symbol_dependency_header_directives;
   std::set<std::string> undefined_symbols;


   // gather all the symbols into a single list
   std::set<std::string> present_symbols;

   // gather symbols of the class's attributes
   for (auto &attribute_property : cpp_class.get_attribute_properties())
   {
      present_symbols.insert(attribute_property.datatype);
   }
   // gather symbols of the parent classes
   for (auto &parent_class_properties : cpp_class.get_parent_classes_properties())
   {
      present_symbols.insert(parent_class_properties.get_class_name());
   }
   // gather symbols from function signatures
   for (auto &function : cpp_class.get_functions())
   {
      // include the type of the function
      present_symbols.insert(function.get_type());

      // include the type(s) for each of the parameters in the function
      for (auto &parameter : function.get_signature()) present_symbols.insert(parameter.get_type());

      // TODO: include the type(s) used in the default arguments
      // HERE:
   }


   // atomize the dependencies
   std::set<std::string> atomized_symbols;
   for (auto &present_symbol : present_symbols)
   {
      std::vector<std::string> symbol_atoms = Blast::DependencySymbolAtomizer(present_symbol).atomize();
      for (auto &symbol_atom : symbol_atoms) atomized_symbols.insert(symbol_atom);
   }


   // look for undefined symbols
   for (auto &present_symbol : atomized_symbols)
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
      error_message << "When consolidating dependencies for:" << std::endl
                    << std::endl
                    << "  " << get_class_name_with_namespaces() << std::endl
                    << std::endl
                    << "There are undefined symbols for datatypes [ ";
      for (auto &undefined_symbol : undefined_symbols) error_message << "\"" << undefined_symbol << "\", ";
      error_message << " ]";

      // append more readable error:
      error_message << std::endl;
      error_message << std::endl;

      error_message << cpp_class.get_class_name() << " appears to be missing the following dependencies:" << std::endl;
      error_message << std::endl;
      for (auto &undefined_symbol : undefined_symbols) error_message << "  - " << undefined_symbol << std::endl;

      error_message << std::endl;
      Blast::DependencyHeadersSuggester dependency_headers_suggester;
      for (auto &undefined_symbol : undefined_symbols)
      {
         std::string dependency = undefined_symbol;
         std::string headers = dependency_headers_suggester.find_suggested_headers_csv(dependency);

         //std::string symbol = undefined_symbol;
         //std::string header = undefined_symbol;
         //__replace(header, "::", "/");
         //header += ".hpp";

         //if (symbol == "ALLEGRO_BITMAP") header = "allegro5/allegro.h";
         //if (symbol == "ALLEGRO_FONT") header = "allegro5/allegro_font.h";
         //if (symbol == "ALLEGRO_DISPLAY") header = "allegro5/allegro.h";

         error_message << "  - symbol: " << undefined_symbol << std::endl;
         error_message << "    headers: [ " << headers << " ]" << std::endl;
      }

      error_message << std::endl;
      error_message << std::endl;

      throw std::runtime_error(error_message.str());
   }

   for (auto &symbol_dependency_header_directive : symbol_dependency_header_directives)
      result << symbol_dependency_header_directive << "\n";

   return result.str();
}


std::string ClassGenerator::class_property_list(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
   {
      if (attribute_property.is_constexpr) continue;
      result << std::string(3*indent_level, ' ') << attribute_property.as_class_property() << ";\n";
   }
   return result.str();
}


std::string ClassGenerator::constexpr_property_list(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
   {
      if (!attribute_property.is_constexpr) continue;
      result << std::string(3*indent_level, ' ') << attribute_property.as_class_property() << ";\n";
   };
   return result.str();
}


std::string ClassGenerator::static_attribute_definitions(int indent_level)
{
   std::stringstream result;
   for (auto &static_attribute_definition : static_attribute_definition_elements())
      result << std::string(3*indent_level, ' ') << static_attribute_definition << "\n\n\n";
   return result.str();
}


std::string ClassGenerator::getter_function_declarations(int indent_level)
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


std::string ClassGenerator::getter_function_definitions(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.has_getter) result << std::string(3*indent_level, ' ') << attribute_property.getter_function_definition(cpp_class.get_class_name()) << "\n\n";
   return result.str();
}


std::string ClassGenerator::getter_ref_function_declarations(int indent_level)
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


std::string ClassGenerator::getter_ref_function_definitions(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.has_getter_ref) result << std::string(3*indent_level, ' ') << attribute_property.getter_ref_function_definition(cpp_class.get_class_name()) << "\n\n";
   return result.str();
}


std::string ClassGenerator::setter_function_declarations(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.has_setter) result << std::string(3*indent_level, ' ') << attribute_property.setter_function_declaration() << "\n";
   return result.str();
}


std::string ClassGenerator::setter_function_definitions(int indent_level)
{
   std::stringstream result;
   for (auto &attribute_property : cpp_class.get_attribute_properties())
      if (attribute_property.has_setter) result << std::string(3*indent_level, ' ') << attribute_property.setter_function_definition(cpp_class.get_class_name()) << "\n\n";
   return result.str();
}


std::string ClassGenerator::initialization_list(int indent_level)
{
   std::stringstream result;
   std::vector<std::string> elements = initialization_list_elements();

   if (elements.empty()) return "";

   result << std::string(3*indent_level, ' ') << ": " << elements.front() << "\n";
   for (int i=1; i<elements.size(); i++) result << std::string(3*indent_level, ' ') << ", " << elements[i] << "\n";
   return result.str();
}


std::string ClassGenerator::private_function_declarations(int indent_level)
{
   std::stringstream result;
   for (auto &private_function_declaration_element : private_function_declaration_elements())
      result << std::string(3*indent_level, ' ') << private_function_declaration_element;
   return result.str();
}


std::string ClassGenerator::protected_function_declarations(int indent_level)
{
   std::stringstream result;
   for (auto &protected_function_declaration_element : protected_function_declaration_elements())
      result << std::string(3*indent_level, ' ') << protected_function_declaration_element;
   return result.str();
}


std::string ClassGenerator::public_function_declarations(int indent_level)
{
   std::stringstream result;
   for (auto &public_function_declaration_element : public_function_declaration_elements())
      result << std::string(3*indent_level, ' ') << public_function_declaration_element;
   return result.str();
}


std::string ClassGenerator::private_enum_class_declarations(int indent_level)
{
   // TODO: add tests for these, including indentation
   std::stringstream result;
   for (auto &private_enum_class_declaration_element : private_enum_class_declaration_elements())
   {
      //result << std::string(3*indent_level, ' ') << private_enum_class_declaration_element;
      result << __indent(3, indent_level, private_enum_class_declaration_element);
   }
   return result.str();
}


std::string ClassGenerator::protected_enum_class_declarations(int indent_level)
{
   // TODO: add tests for these, including indentation
   std::stringstream result;
   for (auto &protected_enum_class_declaration_element : protected_enum_class_declaration_elements())
   {
      //result << std::string(3*indent_level, ' ') << protected_enum_class_declaration_element;
      result << __indent(3, indent_level, protected_enum_class_declaration_element);
   }
   return result.str();
}


std::string ClassGenerator::public_enum_class_declarations(int indent_level)
{
   // TODO: add tests for these, including indentation
   std::stringstream result;
   for (auto &public_enum_class_declaration_element : public_enum_class_declaration_elements())
   {
      //result << std::string(3*indent_level, ' ') << public_enum_class_declaration_element;
      result << __indent(3, indent_level, public_enum_class_declaration_element);
   }
   return result.str();
}


std::string ClassGenerator::function_definitions(int indent_level)
{
   std::stringstream result;
   std::vector<std::string> indented_results;

   for (auto &function_definition_element : function_definition_elements())
   {
      std::stringstream indented_result;
      std::vector<std::string> tokens = split(function_definition_element, '\n');
      for (auto &token : tokens)
      {
         indented_result << std::string(3*indent_level, ' ') << token << '\n';
      }
      indented_results.push_back(indented_result.str());
   }

   return __join(indented_results, "\n");
}


std::string ClassGenerator::constructor_declaration(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << cpp_class.get_class_name() << "(" << __join(constructor_declaration_elements()) << ");\n";
   return result.str();
}


std::string ClassGenerator::constructor_definition(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << cpp_class.get_class_name() << "::" << cpp_class.get_class_name() << "(" << __join(constructor_definition_elements()) << ")\n"
      << initialization_list(indent_level+1)
      << std::string(3*indent_level, ' ') << "{\n" << std::string(3*indent_level, ' ') << "}\n";
   return result.str();
}


std::string ClassGenerator::destructor_declaration(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ');
      if (cpp_class.infer_has_virtual_functions()) result << "virtual ";
      result << "~" << cpp_class.get_class_name() << "();\n";
   return result.str();
}


std::string ClassGenerator::destructor_definition(int indent_level)
{
   std::stringstream result;
   result << std::string(3*indent_level, ' ') << cpp_class.get_class_name() << "::~" << cpp_class.get_class_name() << "()\n" << std::string(3*indent_level, ' ') << "{\n" << std::string(3*indent_level, ' ') << "}\n";
   return result.str();
}


bool ClassGenerator::public_enums_are_present()
{
   // TODO: test this function
   for (auto &enum_class : cpp_class.get_enum_classes())
   {
      if (enum_class.is_public()) return true;
   }
   return false;
}


bool ClassGenerator::private_enums_are_present()
{
   // TODO: test this function
   for (auto &enum_class : cpp_class.get_enum_classes())
   {
      if (enum_class.is_private()) return true;
   }
   return false;
}


bool ClassGenerator::protected_enums_are_present()
{
   // TODO: test this function
   for (auto &enum_class : cpp_class.get_enum_classes())
   {
      if (enum_class.is_protected()) return true;
   }
   return false;
}


std::string ClassGenerator::generate_source_file_content()
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


std::string ClassGenerator::generate_header_file_content()
{
   std::string header_file_template = R"END(#pragma once


DEPENDENCY_INCLUDE_DIRECTIVES

NAMESPACES_OPENER
CLASS_DECLARATION_OPENER
CONSTEXPR_SECTION
FORWARD_DECLARED_ENUMS_PUBLIC_SCOPE_SPECIFIER
FORWARD_DECLARED_PUBLIC_ENUM_DECLARATIONS
FORWARD_DECLARED_ENUMS_PROTECTED_SCOPE_SPECIFIER
FORWARD_DECLARED_PROTECTED_ENUM_DECLARATIONS
PRIVATE_SCOPE_SPECIFIER
PRIVATE_ENUM_CLASS_DECLARATIONS
PROPERTIES
PRIVATE_FUNCTION_DECLARATIONS

PROTECTED_SECTION
PROTECTED_ENUM_CLASS_DECLARATIONS

PUBLIC_SCOPE_SPECIFIER
PUBLIC_ENUM_CLASS_DECLARATIONS
CONSTRUCTOR
DESTRUCTOR

SETTER_FUNCTIONS
GETTER_FUNCTIONS
GETTER_REF_FUNCTIONS
PUBLIC_FUNCTION_DECLARATIONS
CLASS_DECLARATION_CLOSER
NAMESPACES_CLOSER


)END";

   std::string result = header_file_template;

   int required_namespace_indentation_levels = cpp_class.get_namespaces().size();


   // NOTE: Order of replacing is important in this function.  Some replaced symbols have similar
   // symbos that cointain it as a substring, e.g. "FORWARD_DECLARED_ENUMS_PUBLIC_SCOPE_SPECIFIER" contains
   // "PUBLIC_SCOPE_SPECIFIER" so the former needs to be replaced in the template first.


   // Forward-declared enums
   // TODO: consider writing proper forward-declared enums here (rather than fully declaring them in this part, the
   // forward-delared section of class).

   // TODO: Test this replace
   __replace(
         result,
         "FORWARD_DECLARED_ENUMS_PUBLIC_SCOPE_SPECIFIER\n",
         public_enums_are_present() ? __indent(3, required_namespace_indentation_levels, "public:") + "\n" : "" );
   // TODO: Update this to be a forward-declaration rather than a full declaration (Add full declarations below)
   __replace(
         result,
         "FORWARD_DECLARED_PUBLIC_ENUM_DECLARATIONS\n",
         public_enum_class_declarations(required_namespace_indentation_levels + 1)
      );
   // TODO: Test this replace
   __replace(
         result,
         "FORWARD_DECLARED_ENUMS_PROTECTED_SCOPE_SPECIFIER\n",
         protected_enums_are_present() ? __indent(3, required_namespace_indentation_levels, "protected:") + "\n" : "" );
   // TODO: Update this to be a forward-declaration rather than a full declaration (Add full declarations below)
   __replace(
         result,
         "FORWARD_DECLARED_PROTECTED_ENUM_DECLARATIONS\n",
         protected_enum_class_declarations(required_namespace_indentation_levels + 1)
      );


   // replace/expand CONSTEXPR_SECTION if constexpr properties are present
   
   if (cpp_class.infer_has_constexpr_properties())
   {
      std::string replace_string = "PUBLIC_SCOPE_SPECIFIER\nCONSTEXPR_PROPERTIES\n\n";
      __replace(result, "CONSTEXPR_SECTION\n", replace_string);
      //__replace(result, "CONSTEXPR_PROPERTIES\n", constexpr_property_list(required_namespace_indentation_levels + 1));
   }
   else
   {
      __replace(result, "CONSTEXPR_SECTION\n", "");
   }


   // TODO
    bool has_elements_in_a_protected_section = true; //cpp_class.WHATEVER();
   if (has_elements_in_a_protected_section)
   {
      std::string replace_string = "PROTECTED_SCOPE_SPECIFIER\nPROTECTED_FUNCTION_DECLARATIONS\n\n";
      __replace(result, "PROTECTED_SECTION\n", replace_string);
      //__replace(result, "CONSTEXPR_PROPERTIES\n", constexpr_property_list(required_namespace_indentation_levels + 1));
   }
   else
   {
      __replace(result, "PROTECTED_SECTION\n", "");
   }

   // replace the variables (including ones that may have been added to the template in pre-processing)
   __replace(result, "NAMESPACES_OPENER\n", namespaces_scope_opener(true));
   __replace(result, "NAMESPACES_CLOSER", namespaces_scope_closer(true, false));
   __replace(result, "DEPENDENCY_INCLUDE_DIRECTIVES", dependency_include_directives());
   __replace(result, "CLASS_NAME", cpp_class.get_class_name());
   __replace(result, "CONSTRUCTOR\n", constructor_declaration(required_namespace_indentation_levels + 1));
   __replace(result, "DESTRUCTOR\n", destructor_declaration(required_namespace_indentation_levels + 1));
   __replace(result, "CONSTEXPR_PROPERTIES\n", constexpr_property_list(required_namespace_indentation_levels + 1));
   __replace(result, "PROPERTIES\n", class_property_list(required_namespace_indentation_levels + 1));
   __replace(result, "SETTER_FUNCTIONS\n", setter_function_declarations(required_namespace_indentation_levels + 1));
   __replace(result, "GETTER_FUNCTIONS\n", getter_function_declarations(required_namespace_indentation_levels + 1));
   __replace(result, "GETTER_REF_FUNCTIONS\n", getter_ref_function_declarations(required_namespace_indentation_levels + 1));
   __replace(result, "CLASS_DECLARATION_OPENER\n", class_declaration_opener(required_namespace_indentation_levels));
   __replace(result, "CLASS_DECLARATION_CLOSER\n", class_declaration_closer(required_namespace_indentation_levels));

   __replace(result, "PRIVATE_SCOPE_SPECIFIER\n", private_scope_specifier(required_namespace_indentation_levels));
   __replace(result, "PUBLIC_SCOPE_SPECIFIER\n", public_scope_specifier(required_namespace_indentation_levels));
   __replace(result, "PROTECTED_SCOPE_SPECIFIER\n", protected_scope_specifier(required_namespace_indentation_levels));

   __replace(result, "PUBLIC_FUNCTION_DECLARATIONS\n", public_function_declarations(required_namespace_indentation_levels + 1));
   __replace(result, "PRIVATE_FUNCTION_DECLARATIONS\n", private_function_declarations(required_namespace_indentation_levels + 1));
   __replace(result, "PROTECTED_FUNCTION_DECLARATIONS\n", protected_function_declarations(required_namespace_indentation_levels + 1));



   // Enums
   
   __replace(
         result,
         "PUBLIC_ENUM_CLASS_DECLARATIONS\n",
         // TODO: Update this to be the full declaration (once forward-declarations above are not full declarations)
         ""
         //public_enum_class_declarations(required_namespace_indentation_levels + 1)
      );
   __replace(
         result,
         "PRIVATE_ENUM_CLASS_DECLARATIONS\n",
         private_enum_class_declarations(required_namespace_indentation_levels + 1)
      );
   __replace(
         result,
         "PROTECTED_ENUM_CLASS_DECLARATIONS\n",
         // TODO: Update this to be the full declaration (once forward-declarations above are not full declarations)
         ""
         //protected_enum_class_declarations(required_namespace_indentation_levels + 1)
      );


   return result;
}


std::string ClassGenerator::generate_test_file_content()
{
   throw std::runtime_error("Not implemented");
   std::stringstream content;
   return content.str();
}


std::string ClassGenerator::generate_example_file_content()
{
   throw std::runtime_error("Not implemented");
   std::stringstream content;
   return content.str();
}


std::string ClassGenerator::project_source_filepath()
{
   std::stringstream result;
   result << "src";
   for (unsigned i=0; i<cpp_class.get_namespaces().size(); i++) result << "/" << cpp_class.get_namespaces()[i];
   result << "/" << source_filename();
   return result.str();
}


std::string ClassGenerator::project_header_filepath()
{
   std::stringstream result;
   result << "include";
   for (unsigned i=0; i<cpp_class.get_namespaces().size(); i++) result << "/" << cpp_class.get_namespaces()[i];
   result << "/" << header_filename();
   return result.str();
}



std::vector<std::string> ClassGenerator::consolidate_default_value_dependency_symbols(
      std::vector<Blast::Cpp::FunctionArgument> function_arguments
   )
{
   std::set<std::string> result_set;

   // Consolidate the values
   for (auto &function_argument : function_arguments)
   {
      for (auto &default_value_dependency_symbol : function_argument.get_default_value_dependency_symbols())
      {
         result_set.insert(default_value_dependency_symbol);
      }
   }

   // Convert the set to a vector
   std::vector<std::string> result_vector;
   std::copy(result_set.begin(), result_set.end(), std::back_inserter(result_vector));

   // Return the result
   return result_vector;
}




} // namespace Cpp


} // namespace Blast


