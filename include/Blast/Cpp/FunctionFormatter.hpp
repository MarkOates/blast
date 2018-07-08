#pragma once


#include <Blast/Cpp/Function.hpp>
#include <string>


namespace Blast
{
   namespace Cpp
   {
      class FunctionFormatter
      {
      private:
         Blast::Cpp::Function function;
         std::string class_name;

      public:
         FunctionFormatter(Blast::Cpp::Function function={}, std::string class_name="");
         ~FunctionFormatter();

         std::string get_function_declaration();
         std::string get_function_definition();
      };
   }
}



