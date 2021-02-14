#pragma once


#include <string>


namespace Blast
{
   class CamelCaseToUnderscoreConverter
   {
   private:
      std::string str;

   public:
      CamelCaseToUnderscoreConverter(std::string str="foobar");
      ~CamelCaseToUnderscoreConverter();

      std::string convert_to_underscores();
   };
}



