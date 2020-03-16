#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class RegexMatcher
   {
   private:
      std::string source_string;
      std::string regex_expression;

   public:
      RegexMatcher(std::string source_string="", std::string regex_expression="");
      ~RegexMatcher();


      std::string get_source_string();
      std::string get_regex_expression();
   std::vector<std::pair<int, int>> get_match_info();
   };
}



