#pragma once


#include <string>


namespace Blast
{
   class CppFunctionArgument
   {
   private:
      std::string type;
      std::string name;
      std::string default_value;

   public:
      CppFunctionArgument(std::string type="std::string", std::string name="unnamed_parameter", std::string default_value="\"\"");
      ~CppFunctionArgument();


      std::string get_type();
      std::string get_name();
      std::string get_default_value();
   };
}



