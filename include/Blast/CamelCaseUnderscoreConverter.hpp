#pragma once


#include <string>


namespace Blast
{
   class CamelCaseUnderscoreConverter
   {
   private:
      std::string str;

   public:
      CamelCaseUnderscoreConverter(std::string str="foobar");
      ~CamelCaseUnderscoreConverter();


   std::string convert_to_underscores();
   };
}



