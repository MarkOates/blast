

#include <Blast/Cpp/Class.hpp>


namespace Blast
{


namespace Cpp
{


Class::Class(std::string class_name, std::vector<std::string> namespaces, std::vector<Blast::Cpp::ParentClassProperties> parent_classes_properties, std::vector<Blast::Cpp::ClassAttributeProperties> attribute_properties, std::vector<Blast::Cpp::Function> functions, std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies, std::vector<Blast::Cpp::SymbolDependencies> function_body_symbol_dependencies)
   : class_name(class_name)
   , namespaces(namespaces)
   , parent_classes_properties(parent_classes_properties)
   , attribute_properties(attribute_properties)
   , functions(functions)
   , symbol_dependencies(symbol_dependencies)
   , function_body_symbol_dependencies(function_body_symbol_dependencies)
{
}


Class::~Class()
{
}


std::string Class::get_class_name()
{
   return class_name;
}


std::vector<std::string> Class::get_namespaces()
{
   return namespaces;
}


std::vector<Blast::Cpp::ParentClassProperties> Class::get_parent_classes_properties()
{
   return parent_classes_properties;
}


std::vector<Blast::Cpp::ClassAttributeProperties> Class::get_attribute_properties()
{
   return attribute_properties;
}


std::vector<Blast::Cpp::Function> Class::get_functions()
{
   return functions;
}


std::vector<Blast::Cpp::SymbolDependencies> Class::get_symbol_dependencies()
{
   return symbol_dependencies;
}


std::vector<Blast::Cpp::SymbolDependencies> Class::get_function_body_symbol_dependencies()
{
   return function_body_symbol_dependencies;
}


} // namespace Cpp


} // namespace Blast
