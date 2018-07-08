

#include <Blast/Cpp/SymbolDependencies.hpp>

#include <sstream>


namespace Blast
{


namespace Cpp
{


SymbolDependencies::SymbolDependencies(std::string symbol, std::vector<std::string> include_header_files, std::vector<std::string> dependency_include_directories, std::vector<std::string> linked_library_names)
   : symbol(symbol)
   , include_header_files(include_header_files)
   , dependency_include_directories(dependency_include_directories)
   , linked_library_names(linked_library_names)
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


void SymbolDependencies::set_dependency_include_directories(std::vector<std::string> dependency_include_directories)
{
   this->dependency_include_directories = dependency_include_directories;
}


void SymbolDependencies::set_linked_library_names(std::vector<std::string> linked_library_names)
{
   this->linked_library_names = linked_library_names;
}


std::string SymbolDependencies::get_symbol()
{
   return symbol;
}


std::vector<std::string> SymbolDependencies::get_include_header_files()
{
   return include_header_files;
}


std::vector<std::string> SymbolDependencies::get_dependency_include_directories()
{
   return dependency_include_directories;
}


std::vector<std::string> SymbolDependencies::get_linked_library_names()
{
   return linked_library_names;
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


bool SymbolDependencies::requires_linked_libraries()
{
   return !linked_library_names.empty();
}


} // namespace Cpp


} // namespace Blast


