#pragma once


#include <Blast/CppClassGenerator.hpp>
#include <Blast/CppGoogleTestSuiteGenerator.hpp>
#include <Blast/libraries/json.hpp>
#include <string>


namespace Blast
{
   class QuintessenceLoader
   {
   private:
      CppClassGenerator cpp_class_generator;
      CppGoogleTestSuiteGenerator cpp_google_test_suite_generator;
      nlohmann::json json;

   public:
      QuintessenceLoader();
      ~QuintessenceLoader();

      CppClassGenerator get_cpp_class_generator();
      CppGoogleTestSuiteGenerator get_cpp_google_test_suite_generator();
      nlohmann::json get_json();

      void parse(std::string json_string);
      void load(std::string filename);
   };
}


