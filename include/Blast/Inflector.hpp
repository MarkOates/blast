#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class Inflector
   {
   private:

   public:
      Inflector();
      ~Inflector();


   std::vector<std::pair<std::string, std::string>> build_inflections_list();
   };
}



