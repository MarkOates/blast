

#include <Blast/SymbolDependencies.hpp>

#include <sstream>


namespace Blast
{


SymbolDependencies::SymbolDependencies(std::string symbol, std::vector<std::string> include_header_files, std::string dependency_include_directory, std::string linked_library_name)
   : symbol(symbol)
   , include_header_files(include_header_files)
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


void SymbolDependencies::set_include_header_files(std::vector<std::string> include_header_files)
{
   this->include_header_files = include_header_files;
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


std::vector<std::string> SymbolDependencies::get_include_header_files()
{
   return include_header_files;
}


std::string SymbolDependencies::get_dependency_include_directory()
{
   return dependency_include_directory;
}


std::string SymbolDependencies::get_linked_library_name()
{
   return linked_library_name;
}


bool SymbolDependencies::is_symbol(std::string symbol)
{
   return this->symbol == symbol;
}


std::vector<std::string> SymbolDependencies::get_include_directives()
{
   std::vector<std::string> result;

   for (auto &include_header_file : include_header_files)
   {
      std::stringstream directive_str;
      directive_str << "#include <" << include_header_file << ">";
      result.push_back(directive_str.str());
   }

   return result;
}


bool SymbolDependencies::requires_header_files()
{
   return !include_header_files.empty();
}


bool SymbolDependencies::has_linked_library()
{
   return !linked_library_name.empty();
}


} // namespace Blast


