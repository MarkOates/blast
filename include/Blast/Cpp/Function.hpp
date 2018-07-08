#pragma once


#include <Blast/Cpp/FunctionArgument.hpp>
#include <string>
#include <vector>


namespace Blast
{
   namespace Cpp
   {
      class Function
      {
      private:
         std::string type;
         std::string name;
         std::vector<Blast::Cpp::FunctionArgument> signature;
         std::string body;
         bool is_static;
         bool is_const;
         bool is_override;

      public:
         Function(std::string type="void", std::string name="unnamed_function", std::vector<Blast::Cpp::FunctionArgument> signature={}, std::string body="return;", bool is_static=false, bool is_const=false, bool is_override=false);
         ~Function();


         std::string get_type();
         std::string get_name();
         std::vector<Blast::Cpp::FunctionArgument> get_signature();
         std::string get_body();
         bool get_is_static();
         bool get_is_const();
         bool get_is_override();
      };
   }
}



