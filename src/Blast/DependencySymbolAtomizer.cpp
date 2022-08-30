

#include <Blast/DependencySymbolAtomizer.hpp>



namespace Blast
{


DependencySymbolAtomizer::DependencySymbolAtomizer(std::string dependency_symbol)
   : dependency_symbol(dependency_symbol)
{
}


DependencySymbolAtomizer::~DependencySymbolAtomizer()
{
}


void DependencySymbolAtomizer::set_dependency_symbol(std::string dependency_symbol)
{
   this->dependency_symbol = dependency_symbol;
}


std::string DependencySymbolAtomizer::get_dependency_symbol() const
{
   return dependency_symbol;
}


std::vector<std::string> DependencySymbolAtomizer::atomize()
{
   std::vector<std::string> result;

   return { "vector", "string" };

   return result;
}
} // namespace Blast


