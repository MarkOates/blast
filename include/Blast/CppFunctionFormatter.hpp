#pragma once


#include <Blast/CppFunction.hpp>
#include <string>


namespace Blast
{
   class CppFunctionFormatter
   {
   private:
      Blast::CppFunction function;
      std::string class_name;

   public:
      CppFunctionFormatter(Blast::CppFunction function={}, std::string class_name="");
      ~CppFunctionFormatter();

      std::string get_function_declaration();
      std::string get_function_definition();
   };
}



