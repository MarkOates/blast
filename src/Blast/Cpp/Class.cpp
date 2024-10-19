

#include <Blast/Cpp/Class.hpp>


namespace Blast
{
namespace Cpp
{


Class::Class(
      std::string class_name,
      std::vector<std::string> namespaces,
      std::vector<Blast::Cpp::ParentClassProperties> parent_classes_properties,
      std::vector<Blast::Cpp::ClassAttributes> attribute_properties,
      std::vector<Blast::Cpp::EnumClass> enum_classes,
      Blast::Cpp::Function destructor,
      std::vector<Blast::Cpp::Function> functions,
      std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies,
      std::vector<Blast::Cpp::SymbolDependencies> function_body_symbol_dependencies
   )
   : class_name(class_name)
   , namespaces(namespaces)
   , parent_classes_properties(parent_classes_properties)
   , attribute_properties(attribute_properties)
   , enum_classes(enum_classes)
   , destructor(destructor)
   , functions(functions)
   , symbol_dependencies(symbol_dependencies)
   , function_body_symbol_dependencies(function_body_symbol_dependencies)
{
}


Class::~Class()
{
}


bool Class::infer_has_destructor()
{
   return destructor.get_name() == "unnamed_function"; // TODO: Consider if this is good enough, it's a bit fragile
}


bool Class::infer_has_virtual_functions()
{
   for (auto &function : get_functions()) if (function.get_is_virtual() || function.get_is_pure_virtual()) return true;
   return false;
}


bool Class::infer_has_constexpr_properties()
{
   for (auto &attribute_property: get_attribute_properties())
   {
      if (attribute_property.is_constexpr) return true;
   }
   return false;
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


std::vector<Blast::Cpp::ClassAttributes> Class::get_attribute_properties()
{
   return attribute_properties;
}


std::vector<Blast::Cpp::EnumClass> Class::get_enum_classes()
{
   return enum_classes;
}


Blast::Cpp::Function Class::get_destructor()
{
   return destructor;
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


