#pragma once


#include <Blast/Cpp/GoogleTestGenerator.hpp>
#include <vector>


namespace Blast
{
   namespace Cpp
   {
      class GoogleTestSuiteGenerator
      {
      private:
         std::string class_name;
         std::vector<std::string> namespaces;
         std::vector<GoogleTestGenerator> tests;
         int blank_line_padding;

      public:
         GoogleTestSuiteGenerator(std::string class_name="UnnamedClass", std::vector<std::string> namespaces={}, std::vector<Blast::Cpp::GoogleTestGenerator> tests={});
         ~GoogleTestSuiteGenerator();

         std::string class_header_filename();
         std::string test_filename();
         std::string test_filepath();
         std::string class_include_directive();
         std::vector<std::string> generate_test_cases();
         std::string render();
      };
   }
}


