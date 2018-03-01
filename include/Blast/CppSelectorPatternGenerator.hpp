#pragma once


#include <iostream>
#include <string>
#include <vector>


namespace Blast
{
   class CppSelectorPatternGenerator
   {
   private:
      std::string class_name;
      std::string function_name;
      std::string selector_condition;
      std::string casted_type;

   public:
      CppSelectorPatternGenerator(std::string class_name="ClassName", std::string function_name="function_name", std::string selector_condition="", std::string casted_type="");
      ~CppSelectorPatternGenerator();

      std::string render_declaration();
      std::string render_definition();
   };
}


