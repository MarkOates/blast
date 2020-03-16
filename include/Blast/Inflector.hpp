#pragma once


#include <regex>
#include <string>
#include <tuple>
#include <vector>


namespace Blast
{
   class Inflector
   {
   private:
      std::string word;

   public:
      Inflector(std::string word="");
      ~Inflector();


   std::string pluralize();
   std::vector<std::tuple<std::string, std::string, std::regex_constants::syntax_option_type>> build_inflections_list();
   };
}



