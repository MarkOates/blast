#pragma once


#include <regex>
#include <string>
#include <utility>
#include <vector>


namespace Blast
{
   class RegexMatcher
   {
   private:
      std::string source_string;
      std::string regex_expression;
      std::vector<std::regex_constants::syntax_option_type> options;
      std::regex re;
      bool compiled;

   protected:


   public:
      RegexMatcher(std::string source_string="", std::string regex_expression="", std::vector<std::regex_constants::syntax_option_type> options={});
      ~RegexMatcher();

      void set_source_string(std::string source_string);
      std::string get_source_string() const;
      std::string get_regex_expression() const;
      std::vector<std::regex_constants::syntax_option_type> get_options() const;
      void set_regex_expression(std::string regex_expression="");
      void set_options(std::vector<std::regex_constants::syntax_option_type> options={});
      void compile();
      std::vector<std::pair<int, int>> get_match_info();
   };
}



