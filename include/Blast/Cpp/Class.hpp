#pragma once


#include <Blast/Cpp/ClassAttributeProperties.hpp>
#include <Blast/Cpp/Function.hpp>
#include <Blast/Cpp/ParentClassProperties.hpp>
#include <Blast/Cpp/SymbolDependencies.hpp>
#include <string>
#include <vector>


namespace Blast
{
   namespace Cpp
   {
      class Class
      {
      private:
         std::string class_name;
         std::vector<std::string> namespaces;
         std::vector<Blast::Cpp::ParentClassProperties> parent_classes_properties;
         std::vector<Blast::Cpp::ClassAttributeProperties> attribute_properties;
         std::vector<Blast::Cpp::Function> functions;
         std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies;
         std::vector<Blast::Cpp::SymbolDependencies> function_body_symbol_dependencies;

      public:
         Class(std::string class_name="UnnamedClass", std::vector<std::string> namespaces={}, std::vector<Blast::Cpp::ParentClassProperties> parent_classes_properties={}, std::vector<Blast::Cpp::ClassAttributeProperties> attribute_properties={}, std::vector<Blast::Cpp::Function> functions={}, std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies={}, std::vector<Blast::Cpp::SymbolDependencies> function_body_symbol_dependencies={});
         ~Class();


         std::string get_class_name();
         std::vector<std::string> get_namespaces();
         std::vector<Blast::Cpp::ParentClassProperties> get_parent_classes_properties();
         std::vector<Blast::Cpp::ClassAttributeProperties> get_attribute_properties();
         std::vector<Blast::Cpp::Function> get_functions();
         std::vector<Blast::Cpp::SymbolDependencies> get_symbol_dependencies();
         std::vector<Blast::Cpp::SymbolDependencies> get_function_body_symbol_dependencies();
      };
   }
}



