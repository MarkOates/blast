

#include <gtest/gtest.h>

#include <Blast/Cpp/GoogleTestSuiteGenerator.hpp>


TEST(GoogleTestSuiteGeneratorTest, can_be_created)
{
   ASSERT_NO_THROW(Blast::Cpp::GoogleTestSuiteGenerator());
}


TEST(GoogleTestSuiteGeneratorTest, class_include_directive__returns_the_expected_formatted_include_directive)
{
   Blast::Cpp::GoogleTestSuiteGenerator cpp_google_test_suite_generator("FooClass", { "Blast" });

   std::string expected_include_directive = "#include <Blast/FooClass.hpp>\n";
   ASSERT_EQ(expected_include_directive, cpp_google_test_suite_generator.class_include_directive());
}


TEST(GoogleTestSuiteGeneratorTest, class_include_directive__without_namespaces_returns_the_expected_formatted_include_directive)
{
   Blast::Cpp::GoogleTestSuiteGenerator cpp_google_test_suite_generator("FooClass");

   std::string expected_include_directive = "#include <FooClass.hpp>\n";
   ASSERT_EQ(expected_include_directive, cpp_google_test_suite_generator.class_include_directive());
}


