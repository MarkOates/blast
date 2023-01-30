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
      std::string __replace(std::string str="source string", std::string from="source", std::string to="result");

   protected:


   public:
      DependencyHeadersSuggester();
      ~DependencyHeadersSuggester();

      std::string generate_autofill_suggestion_for_symbol(std::string symbol="[unset-symbol]");
      std::vector<std::string> find_suggested_headers(std::string symbol="[unset-symbol]", bool autogenerate_a_header_if_one_is_not_present=true);
      std::string find_suggested_headers_csv(std::string symbol="[unset-symbol]", bool autogenerate_a_header_if_one_is_not_present=true);
      std::map<std::string, std::vector<std::string>> get_default_suggested_symbol_headers();
   };
}



