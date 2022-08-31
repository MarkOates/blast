#pragma once


#include <string>


namespace Blast
{
   class CamelCaseToConstantConverter
   {
   private:
      std::string str;

   protected:


   public:
      CamelCaseToConstantConverter(std::string str="foobar");
      ~CamelCaseToConstantConverter();

      std::string convert_to_constant();
   };
}



