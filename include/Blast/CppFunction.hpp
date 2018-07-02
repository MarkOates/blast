#pragma once


#include <Blast/CppFunctionArgument.hpp>
#include <string>
#include <vector>


namespace Blast
{
   class CppFunction
   {
   private:
      std::string type;
      std::string name;
      std::vector<Blast::CppFunctionArgument> signature;
      std::string body;
      bool is_static;
      bool is_const;
      bool is_override;

   public:
      CppFunction(std::string type="void", std::string name="unnamed_function", std::vector<Blast::CppFunctionArgument> signature={}, std::string body="return;", bool is_static=false, bool is_const=false, bool is_override=false);
      ~CppFunction();


      std::string get_type();
      std::string get_name();
      std::vector<Blast::CppFunctionArgument> get_signature();
      std::string get_body();
      bool get_is_static();
      bool get_is_const();
      bool get_is_override();
   };
}



