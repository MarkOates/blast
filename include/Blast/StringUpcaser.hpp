#pragma once


#include <string>


namespace Blast
{
   class StringUpcaser
   {
   private:
      std::string original_text;

   public:
      StringUpcaser(std::string original_text="");
      ~StringUpcaser();

      std::string upcase();
   };
}



