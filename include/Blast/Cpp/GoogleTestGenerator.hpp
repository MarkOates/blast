#pragma once


#include <Blast/Cpp/ClassAttributes.hpp>
#include <Blast/Cpp/ParentClassProperties.hpp>
#include <Blast/Cpp/SymbolDependencies.hpp>


namespace Blast
{
   namespace Cpp
   {
      class GoogleTestGenerator
      {
      private:
         std::string class_name;
         std::string function_name;
         std::string description_sentence;
         std::string body;

      public:
         GoogleTestGenerator(std::string class_name="UnnamedClass", std::string function_name="", std::string description_sentence="is true", std::string body="ASSERT_TRUE(true);");
         ~GoogleTestGenerator();

         std::string get_description_line();
         std::string get_macro_opener_line();
         std::string get_body();

         std::string render();
      };
   }
}


