#pragma once


#include <regex>
#include <string>
#include <vector>


namespace Blast
{
   class RegexMatcher
   {
   private:
      std::string source_string;
      std::string regex_expression;
      std::vector<std::regex_constants::syntax_option_type> options;

   public:
      RegexMatcher(std::string source_string="", std::string regex_expression="", std::vector<std::regex_constants::syntax_option_type> options={});
      ~RegexMatcher();

      std::string get_source_string() const;
      std::string get_regex_expression() const;
      std::vector<std::regex_constants::syntax_option_type> get_options() const;
      std::vector<std::pair<int, int>> get_match_info();
   };
}



