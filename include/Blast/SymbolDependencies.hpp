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
      std::string dependency_include_directory;
      std::string linked_library_name;

   public:
      SymbolDependencies(std::string symbol, std::vector<std::string> include_header_files={}, std::string dependency_include_directory="", std::string linked_library_name="");
      ~SymbolDependencies();

      void set_symbol(std::string symbol);
      void set_include_header_files(std::vector<std::string> include_header_files);
      void set_dependency_include_directory(std::string dependency_include_directory);
      void set_linked_library_name(std::string linked_library_name);

      std::string get_symbol();
      std::vector<std::string> get_include_header_files();
      std::string get_dependency_include_directory();
      std::string get_linked_library_name();

      bool is_symbol(std::string symbol);
      std::vector<std::string> get_include_directives();
      bool requires_header_files();
      bool has_linked_library();
   };
}


