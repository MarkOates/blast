#pragma once


#include <vector>
#include <string>


namespace Blast
{
   namespace Cpp
   {
      class FunctionArgument
      {
      private:
         std::string type;
         std::string name;
         std::string default_value;
         std::vector<std::string> default_value_dependency_symbols;

      public:
         FunctionArgument(
            std::string type="std::string",
            std::string name="unnamed_parameter",
            std::string default_value="\"\"",
            std::vector<std::string> default_value_dependency_symbols={}
         );
         ~FunctionArgument();


         std::string get_type();
         std::string get_name();
         std::string get_default_value();
         std::vector<std::string> get_default_value_dependency_symbols();
      };
   }
}



