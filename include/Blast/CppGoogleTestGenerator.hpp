#pragma once


#include <Blast/ClassAttributeProperties.hpp>
#include <Blast/ParentClassProperties.hpp>
#include <Blast/SymbolDependencies.hpp>


namespace Blast
{
   class CppGoogleTestGenerator
   {
   private:
      std::string class_name;
      std::string function_name;
      std::string description_sentence;
      std::string body;

   public:
      CppGoogleTestGenerator(std::string class_name="UnnamedClass", std::string function_name="", std::string description_sentence="is true", std::string body="ASSERT_TRUE(true);");
      ~CppGoogleTestGenerator();

      std::string get_description_line();
      std::string get_macro_opener_line();
      std::string get_body();

      std::string render();
   };
}


