

#include <Blast/CppGoogleTestSuiteGenerator.hpp>

#include <sstream>


namespace Blast
{


CppGoogleTestSuiteGenerator::CppGoogleTestSuiteGenerator(std::string class_name, std::vector<std::string> namespaces, std::vector<CppGoogleTestGenerator> tests)
   : class_name(class_name)
   , namespaces(namespaces)
   , tests(tests)
   , blank_line_padding(2)
{
}


CppGoogleTestSuiteGenerator::~CppGoogleTestSuiteGenerator()
{
}


std::string CppGoogleTestSuiteGenerator::test_filename()
{
   return class_name + "Test.cpp";
}


std::string CppGoogleTestSuiteGenerator::test_filepath()
{
   std::stringstream result;

   result << "tests";
   for (unsigned i=0; i<namespaces.size(); i++) result << "/" << namespaces[i];
   result << "/" << test_filename();

   return result.str();
}


std::string CppGoogleTestSuiteGenerator::class_header_filename()
{
   return class_name + ".hpp";
}


std::string CppGoogleTestSuiteGenerator::class_include_directive()
{
   std::stringstream result;
   result << "#include <";
   for (auto &ns : namespaces) result << ns << "/";
   result << class_header_filename() << ">\n";

   return result.str();
}


std::vector<std::string> CppGoogleTestSuiteGenerator::generate_test_cases()
{
   std::vector<std::string> result;
   for (auto &test : tests) result.push_back(test.render());
   return result;
}


std::string CppGoogleTestSuiteGenerator::render()
{
   std::stringstream result;
   std::vector<std::string> pieces = {};

   pieces.push_back("#include <gtest/gtest.h>");
   pieces.push_back(class_include_directive());
   for (auto &test_case : generate_test_cases()) pieces.push_back(test_case);

   result << std::string(blank_line_padding, '\n');
   for (auto &piece : pieces) result << piece << std::string(blank_line_padding, '\n');

   return result.str();
}


} // namespace Blast


