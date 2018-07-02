

#include <Blast/CppClass.hpp>


namespace Blast
{


CppClass::CppClass(std::string class_name, std::vector<std::string> namespaces, std::vector<Blast::ParentClassProperties> parent_classes_properties, std::vector<Blast::ClassAttributeProperties> attribute_properties, std::vector<Blast::CppFunction> functions, std::vector<Blast::SymbolDependencies> symbol_dependencies, std::vector<Blast::SymbolDependencies> function_body_symbol_dependencies)
   : class_name(class_name)
   , namespaces(namespaces)
   , parent_classes_properties(parent_classes_properties)
   , attribute_properties(attribute_properties)
   , functions(functions)
   , symbol_dependencies(symbol_dependencies)
   , function_body_symbol_dependencies(function_body_symbol_dependencies)
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


std::vector<Blast::CppFunction> CppClass::get_functions()
{
   return functions;
}


std::vector<Blast::SymbolDependencies> CppClass::get_symbol_dependencies()
{
   return symbol_dependencies;
}


std::vector<Blast::SymbolDependencies> CppClass::get_function_body_symbol_dependencies()
{
   return function_body_symbol_dependencies;
}


} // namespace Blast


