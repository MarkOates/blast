

#include <Blast/SymbolDependencies.hpp>

#include <sstream>


namespace Blast
{


SymbolDependencies::SymbolDependencies(std::string symbol, std::string include_header_file, std::string dependency_include_directory, std::string linked_library_name)
   : symbol(symbol)
   , include_header_file(include_header_file)
   , dependency_include_directory(dependency_include_directory)
   , linked_library_name(linked_library_name)
{
}


SymbolDependencies::~SymbolDependencies()
{
}


void SymbolDependencies::set_symbol(std::string symbol)
{
   this->symbol = symbol;
}


void SymbolDependencies::set_include_header_file(std::string include_header_file)
{
   this->include_header_file = include_header_file;
}


void SymbolDependencies::set_dependency_include_directory(std::string dependency_include_directory)
{
   this->dependency_include_directory = dependency_include_directory;
}


void SymbolDependencies::set_linked_library_name(std::string linked_library_name)
{
   this->linked_library_name = linked_library_name;
}


std::string SymbolDependencies::get_symbol()
{
   return symbol;
}


std::string SymbolDependencies::get_include_header_file()
{
   return include_header_file;
}


std::string SymbolDependencies::get_dependency_include_directory()
{
   return dependency_include_directory;
}


std::string SymbolDependencies::get_linked_library_name()
{
   return linked_library_name;
}


std::string SymbolDependencies::get_include_directive()
{
   std::stringstream result;
   result << "#include <" << get_include_header_file() << ">";
   return result.str();
}


bool SymbolDependencies::has_linked_library()
{
   return !linked_library_name.empty();
}


} // namespace Blast


