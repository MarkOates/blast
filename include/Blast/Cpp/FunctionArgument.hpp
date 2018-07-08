#pragma once


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

      public:
         FunctionArgument(std::string type="std::string", std::string name="unnamed_parameter", std::string default_value="\"\"");
         ~FunctionArgument();


         std::string get_type();
         std::string get_name();
         std::string get_default_value();
      };
   }
}



