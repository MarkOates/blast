#pragma once


#include <Blast/CppFunctionArgument.hpp>


namespace Blast
{
   class CppFunctionArgumentFormatter
   {
   private:
      Blast::CppFunctionArgument function_argument;

   public:
      CppFunctionArgumentFormatter(Blast::CppFunctionArgument function_argument={});
      ~CppFunctionArgumentFormatter();

      Blast::CppFunctionArgument get_function_argument();

      std::string get_as_function_definition();
      std::string get_as_function_declaration();
   };
}



