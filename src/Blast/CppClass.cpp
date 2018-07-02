

#include <Blast/CppClass.hpp>


namespace Blast
{


CppClass::CppClass(std::string class_name, std::vector<std::string> namespaces, std::vector<Blast::ParentClassProperties> parent_classes_properties, std::vector<Blast::ClassAttributeProperties> attribute_properties, std::vector<Blast::SymbolDependencies> symbol_dependencies)
   : class_name(class_name)
   , namespaces(namespaces)
   , parent_classes_properties(parent_classes_properties)
   , attribute_properties(attribute_properties)
   , symbol_dependencies(symbol_dependencies)
{
}


CppClass::~CppClass()
{
}


std::string CppClass::get_class_name()
{
   return class_name;
}


std::vector<std::string> CppClass::get_namespaces()
{
   return namespaces;
}


std::vector<Blast::ParentClassProperties> CppClass::get_parent_classes_properties()
{
   return parent_classes_properties;
}


std::vector<Blast::ClassAttributeProperties> CppClass::get_attribute_properties()
{
   return attribute_properties;
}


std::vector<Blast::ClassAttributeProperties> &CppClass::get_attribute_properties_ref()
{
   return attribute_properties;
}


std::vector<Blast::SymbolDependencies> CppClass::get_symbol_dependencies()
{
   return symbol_dependencies;
}


}


