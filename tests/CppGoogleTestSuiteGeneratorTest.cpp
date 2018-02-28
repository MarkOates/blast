

#include <gtest/gtest.h>

#include <Blast/CppGoogleTestSuiteGenerator.hpp>


TEST(CppGoogleTestSuiteGeneratorTest, can_be_created)
{
   ASSERT_NO_THROW(Blast::CppGoogleTestSuiteGenerator());
}


TEST(CppGoogleTestSuiteGeneratorTest, class_include_directive__returns_the_expected_formatted_include_directive)
{
   Blast::CppGoogleTestSuiteGenerator cpp_google_test_suite_generator("FooClass", { "Blast" });

   std::string expected_include_directive = "#include <Blast/FooClass.hpp>\n";
   ASSERT_EQ(expected_include_directive, cpp_google_test_suite_generator.class_include_directive());
}


TEST(CppGoogleTestSuiteGeneratorTest, class_include_directive__without_namespaces_returns_the_expected_formatted_include_directive)
{
   Blast::CppGoogleTestSuiteGenerator cpp_google_test_suite_generator("FooClass");

   std::string expected_include_directive = "#include <FooClass.hpp>\n";
   ASSERT_EQ(expected_include_directive, cpp_google_test_suite_generator.class_include_directive());
}


