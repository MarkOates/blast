

#include <gtest/gtest.h>

#include <Blast/CppGoogleTestGenerator.hpp>

#include <cmath>


TEST(CppGoogleTestGeneratorTest, can_be_created)
{
   Blast::CppGoogleTestGenerator cpp_google_test_generator;
}


TEST(CppGoogleTestGeneratorTest, get_description_line__returns_the_test_description_properly_formatted)
{
   Blast::CppGoogleTestGenerator cpp_google_test_generator("FooClass", "", "returns the expected value");

   std::string expected_description = "returns_the_expected_value";
   ASSERT_EQ(expected_description, cpp_google_test_generator.get_description_line());
}


TEST(CppGoogleTestGeneratorTest, get_description_line__with_a_function_name_returns_the_test_description_with_a_prefix)
{
   Blast::CppGoogleTestGenerator cpp_google_test_generator("FooClass", "my_func", "returns the expected value");

   std::string expected_description = "my_func__returns_the_expected_value";
   ASSERT_EQ(expected_description, cpp_google_test_generator.get_description_line());
}


TEST(CppGoogleTestGeneratorTest, get_macro_opener_line__returns_the_formatted_line_of_code_for_the_test_opening_macro)
{
   Blast::CppGoogleTestGenerator cpp_google_test_generator("FooClass", "my_func", "returns the expected value", "REFUTE_FALSE(false)");

   std::string expected_macro_opener_line = "TEST(FooClassTest, my_func__returns_the_expected_value)";
   ASSERT_EQ(expected_macro_opener_line, cpp_google_test_generator.get_macro_opener_line());
}


TEST(CppGoogleTestGeneratorTest, render__returns_the_expected_fully_formatted_test)
{
   Blast::CppGoogleTestGenerator cpp_google_test_generator("FooClass", "my_func", "returns the expected value", "ASSERT_EQ(2, 1+1)");

   std::string expected_render = "TEST(FooClassTest, my_func__returns_the_expected_value)\n{\n   ASSERT_EQ(2, 1+1)\n}\n";
   ASSERT_EQ(expected_render, cpp_google_test_generator.render());
}


