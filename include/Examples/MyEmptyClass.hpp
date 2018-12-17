#pragma once


#include <string>


namespace Examples
{
   class MyEmptyClass
   {
   private:
      std::string string;

   public:
      MyEmptyClass(std::string string="my-default-value");
      ~MyEmptyClass();


   };
}



