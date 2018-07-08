#pragma once


#include <Blast/Cpp/FunctionArgument.hpp>


namespace Blast
{
   namespace Cpp
   {
      class FunctionArgumentFormatter
      {
      private:
         Blast::Cpp::FunctionArgument function_argument;

      public:
         FunctionArgumentFormatter(Blast::Cpp::FunctionArgument function_argument={});
         ~FunctionArgumentFormatter();

         Blast::Cpp::FunctionArgument get_function_argument();

         std::string get_as_function_definition();
         std::string get_as_function_declaration();
      };
   }
}



