#pragma once


#include <string>
#include <vector>


namespace quintessences
{
   class StringSplitter
   {
   private:
      std::string string;
      char delimiter;

   protected:


   public:
      StringSplitter(std::string string="", char delimiter=' ');
      ~StringSplitter();

      std::vector<std::string> split();
   };
}



