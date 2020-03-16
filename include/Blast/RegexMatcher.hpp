#pragma once


#include <vector>


namespace Blast
{
   class RegexMatcher
   {
   private:

   public:
      RegexMatcher();
      ~RegexMatcher();


   std::vector<std::pair<int, int>> get_match_info();
   };
}



