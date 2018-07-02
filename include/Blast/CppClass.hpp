#pragma once


#include <Blast/ClassAttributeProperties.hpp>
#include <Blast/CppFunction.hpp>
#include <Blast/ParentClassProperties.hpp>
#include <Blast/SymbolDependencies.hpp>
#include <string>
#include <vector>


namespace Blast
{
   class CppClass
   {
   private:
      std::string class_name;
      std::vector<std::string> namespaces;
      std::vector<Blast::ParentClassProperties> parent_classes_properties;
      std::vector<Blast::ClassAttributeProperties> attribute_properties;
      std::vector<Blast::CppFunction> functions;
      std::vector<Blast::SymbolDependencies> symbol_dependencies;

   public:
      CppClass(std::string class_name="UnnamedClass", std::vector<std::string> namespaces={}, std::vector<Blast::ParentClassProperties> parent_classes_properties={}, std::vector<Blast::ClassAttributeProperties> attribute_properties={}, std::vector<Blast::CppFunction> functions={}, std::vector<Blast::SymbolDependencies> symbol_dependencies={});
      ~CppClass();


      std::string get_class_name();
      std::vector<std::string> get_namespaces();
      std::vector<Blast::ParentClassProperties> get_parent_classes_properties();
      std::vector<Blast::ClassAttributeProperties> get_attribute_properties();
      std::vector<Blast::CppFunction> get_functions();
      std::vector<Blast::SymbolDependencies> get_symbol_dependencies();
   };
}



