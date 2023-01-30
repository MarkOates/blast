#pragma once


#include <map>
#include <string>
#include <vector>


namespace Blast
{
   class DependencyHeadersSuggester
   {
   private:
      std::map<std::string, std::vector<std::string>> suggested_symbol_headers;

   protected:


   public:
      DependencyHeadersSuggester();
      ~DependencyHeadersSuggester();

      std::vector<std::string> suggested_headers(std::string symbol="[unset-symbol]");
      std::string suggested_headers_csv(std::string symbol="[unset-symbol]");
      std::map<std::string, std::vector<std::string>> get_default_suggested_symbol_headers();
   };
}



