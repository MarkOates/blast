#pragma once


#include <Blast/ClassAttributeProperties.hpp>
#include <Blast/SymbolDependencies.hpp>
#include <string>
#include <vector>


namespace Blast
{
   class CppClassGenerator
   {
   private:
      std::string class_name;
      std::vector<std::string> namespaces;
      std::vector<Blast::ClassAttributeProperties> attribute_properties;
      std::vector<Blast::SymbolDependencies> symbol_dependencies;

   public:
      CppClassGenerator(std::string class_name="UnnamedClass", std::vector<std::string> namespaces={}, std::vector<ClassAttributeProperties> attribute_properties={}, std::vector<Blast::SymbolDependencies> symbol_dependencies={});
      ~CppClassGenerator();

      std::vector<ClassAttributeProperties> &get_class_attribute_properties_ref();
      std::vector<SymbolDependencies> &get_symbol_dependencies_ref();

      std::vector<std::string> constructor_declaration_elements();
      std::vector<std::string> constructor_definition_elements();
      std::vector<std::string> initialization_list_elements();

      void set_class_name(std::string class_name);

      std::string get_class_name();

      bool has_namespaces();

      std::string header_filename();
      std::string source_filename();
      std::string header_include_directive(std::string project_name_camelcase);
      std::string dependency_include_directives();
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

      std::string generate_source_file_content(std::string project_name_camelcase);
      std::string generate_header_file_content();
      std::string generate_test_file_content();
      std::string generate_example_file_content();

      std::string project_source_filepath();
      std::string project_header_filepath(std::string project_name_camelcase);
   };
}


