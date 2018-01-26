#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class SymbolDependencies
   {
   private:
      std::string symbol;
      std::vector<std::string> include_header_files;
      std::vector<std::string> dependency_include_directories;
      std::vector<std::string> linked_library_names;

   public:
      SymbolDependencies(std::string symbol, std::vector<std::string> include_header_files={}, std::vector<std::string> dependency_include_directories={}, std::vector<std::string> linked_library_names={});
      ~SymbolDependencies();

      void set_symbol(std::string symbol);
      void set_include_header_files(std::vector<std::string> include_header_files);
      void set_dependency_include_directories(std::vector<std::string> dependency_include_directories);
      void set_linked_library_names(std::vector<std::string> linked_library_names);

      std::string get_symbol();
      std::vector<std::string> get_include_header_files();
      std::vector<std::string> get_dependency_include_directories();
      std::vector<std::string> get_linked_library_names();

      bool is_symbol(std::string symbol);
      std::vector<std::string> get_include_directives();
      bool requires_header_files();
      bool requires_linked_libraries();
   };
}


