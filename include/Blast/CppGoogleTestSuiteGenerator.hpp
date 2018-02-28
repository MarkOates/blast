#pragma once


#include <Blast/CppGoogleTestGenerator.hpp>
#include <vector>


namespace Blast
{
   class CppGoogleTestSuiteGenerator
   {
   private:
      std::string class_name;
      std::vector<std::string> namespaces;
      std::vector<CppGoogleTestGenerator> tests;
      int blank_line_padding;

   public:
      CppGoogleTestSuiteGenerator(std::string class_name="UnnamedClass", std::vector<std::string> namespaces={}, std::vector<CppGoogleTestGenerator> tests={});
      ~CppGoogleTestSuiteGenerator();

      std::string class_header_filename();
      std::string test_filename();
      std::string test_filepath();
      std::string class_include_directive();
      std::vector<std::string> generate_test_cases();
      std::string render();
   };
}


