

#include <gtest/gtest.h>

#include <Blast/CppFunctionFormatter.hpp>


// CppFunction(std::string type="void", std::string name="unnamed_function", std::vector<std::tuple<std::string, std::string, std::string>> signature={}, std::string body="return;", bool is_static=false, bool is_const=false, bool is_override=false);


TEST(CppFunctionFormatterTest, can_be_created)
{
   Blast::CppFunctionFormatter function_formatter;
}


TEST(CppFunctionFormatterTest, get_function_declaration__returns_the_expected_formatted_string)
{
   Blast::CppFunction function("void", "my_function_name", {}, "  return \"hello world!\";", false, false, false);
   Blast::CppFunctionFormatter function_formatter(function);

   std::string expected_returned_string = "void my_function_name(...);\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_declaration());
}


TEST(CppFunctionFormatterTest, get_function_declaration__with_a_class_name_returns_the_expected_formatted_string)
{
   Blast::CppFunction function("void", "my_function_name", {}, "  return \"hello world!\";", false, false, false);
   Blast::CppFunctionFormatter function_formatter(function, "MyClassName");

   std::string expected_returned_string = "void MyClassName::my_function_name(...);\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_declaration());
}


TEST(CppFunctionFormatterTest, get_function_definition__returns_the_expected_formatted_string)
{
   Blast::CppFunction function("void", "my_function_name", {}, "  return \"hello world!\";", false, false, false);
   Blast::CppFunctionFormatter function_formatter(function);

   std::string expected_returned_string = "void my_function_name(...)\n{\n  return \"hello world!\";\n}\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_definition());
}


TEST(CppFunctionFormatterTest, get_function_definition__with_a_class_name_returns_the_expected_formatted_string)
{
   Blast::CppFunction function("void", "my_function_name", {}, "  return \"hello world!\";", false, false, false);
   Blast::CppFunctionFormatter function_formatter(function, "MyClassName");

   std::string expected_returned_string = "void MyClassName::my_function_name(...)\n{\n  return \"hello world!\";\n}\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_definition());
}


