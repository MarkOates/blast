#pragma once


#include <string>
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
   std::vector<std::pair<std::string, std::string>> build_inflections_list();
   };
}



