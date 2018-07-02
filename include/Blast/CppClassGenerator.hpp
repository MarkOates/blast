#pragma once


#include <Blast/CppClass.hpp>
#include <string>
#include <vector>


namespace Blast
{
   class CppClassGenerator
   {
   private:
      CppClass cpp_class;

   public:
      CppClassGenerator(CppClass cpp_class={});
      ~CppClassGenerator();

      std::vector<std::string> constructor_declaration_elements();
      std::vector<std::string> constructor_definition_elements();
      std::vector<std::string> initialization_list_elements();
      std::vector<std::string> class_declaration_opener_inheritence_elements();
      std::vector<std::string> static_attribute_definition_elements();
      std::vector<std::string> function_declaration_elements(int indent_level=0);
      std::vector<std::string> function_definition_elements(int indent_level=0);

      std::string private_scope_specifier(int indent_level=0);
      std::string public_scope_specifier(int indent_level=0);
      std::string protected_scope_specifier(int indent_level=0);
      std::string namespaces_scope_opener(bool indented);
      std::string namespaces_scope_closer(bool indented, bool include_comment=true);
      std::string class_declaration_inheritence_list();
      std::string class_declaration_opener(int indent_level=0);
      std::string class_declaration_closer(int indent_level=0);
      std::string header_filename();
      std::string source_filename();
      std::string header_include_directive();
      std::string dependency_include_directives();
      std::string class_property_list(int indent_level=0);
      std::string static_attribute_definitions(int indent_level=0);
      std::string getter_function_declarations(int indent_level=0);
      std::string getter_function_definitions(int indent_level=0);
      std::string getter_ref_function_declarations(int indent_level=0);
      std::string getter_ref_function_definitions(int indent_level=0);
      std::string setter_function_declarations(int indent_level=0);
      std::string setter_function_definitions(int indent_level=0);
      std::string initialization_list(int indent_level=0);

      std::string function_declarations(int indent_level=0);
      std::string function_definitions(int indent_level=0);

      std::string constructor_declaration(int indent_level=0);
      std::string constructor_definition(int indent_level=0);
      std::string destructor_declaration(int indent_level=0);
      std::string destructor_definition(int indent_level=0);

      std::string generate_source_file_content();
      std::string generate_header_file_content();
      std::string generate_test_file_content();
      std::string generate_example_file_content();

      std::string project_source_filepath();
      std::string project_header_filepath();
   };
}


