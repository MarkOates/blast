

#include <gtest/gtest.h>

#include <Blast/Cpp/FunctionFormatter.hpp>


// CppFunction(std::string type="void", std::string name="unnamed_function", std::vector<std::tuple<std::string, std::string, std::string>> signature={}, std::string body="return;", bool is_static=false, bool is_const=false, bool is_override=false);


TEST(FunctionFormatterTest, can_be_created)
{
   Blast::Cpp::FunctionFormatter function_formatter;
}


TEST(FunctionFormatterTest, get_function_declaration__returns_the_expected_formatted_string)
{
   Blast::Cpp::Function function("void", "my_function_name", {}, "return \"hello world!\";", false, false, false);
   Blast::Cpp::FunctionFormatter function_formatter(function);

   std::string expected_returned_string = "void my_function_name();\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_declaration());
}


TEST(FunctionFormatterTest, get_function_declaration__with_a_function_with_parameter__returns_the_expected_formatted_string)
{
   Blast::Cpp::FunctionArgument function_argument("std::vector<std::string>", "my_parameter", "{ \"one-default-element\" }");
   Blast::Cpp::Function function("void", "my_function_name", { function_argument }, "  return \"hello world!\";", false, false, false);
   Blast::Cpp::FunctionFormatter function_formatter(function);

   std::string expected_returned_string = "void my_function_name(std::vector<std::string> my_parameter={ \"one-default-element\" });\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_declaration());
}


TEST(FunctionFormatterTest, get_function_declaration__with_a_class_name_returns_the_expected_formatted_string)
{
   Blast::Cpp::Function function("void", "my_function_name", {}, "  return \"hello world!\";", false, false, false);
   Blast::Cpp::FunctionFormatter function_formatter(function, "MyClassName");

   std::string expected_returned_string = "void MyClassName::my_function_name();\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_declaration());
}


TEST(FunctionFormatterTest, get_function_declaration__with_an_override_function_returns_the_expected_formatted_string)
{
   Blast::Cpp::Function function("void", "my_function_name", {}, "  return \"hello world!\";", false, false, true, true, false);
   Blast::Cpp::FunctionFormatter function_formatter(function, "MyClassName");

   std::string expected_returned_string = "virtual void MyClassName::my_function_name() override;\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_declaration());
}


TEST(FunctionFormatterTest, get_function_declaration__with_a_virtual_function_returns_the_expected_formatted_string)
{
   Blast::Cpp::Function function("void", "my_function_name", {}, "  return \"hello world!\";", false, false, false, true, false);
   Blast::Cpp::FunctionFormatter function_formatter(function, "MyClassName");

   std::string expected_returned_string = "virtual void MyClassName::my_function_name();\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_declaration());
}


TEST(FunctionFormatterTest, get_function_declaration__with_a_pure_virtual_function_returns_the_expected_formatted_string)
{
   Blast::Cpp::Function function("void", "my_function_name", {}, "  return \"hello world!\";", false, false, false, false, true);
   Blast::Cpp::FunctionFormatter function_formatter(function, "MyClassName");

   std::string expected_returned_string = "virtual void MyClassName::my_function_name() = 0;\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_declaration());
}


TEST(FunctionFormatterTest, get_function_definition__returns_the_expected_formatted_string)
{
   Blast::Cpp::Function function("void", "my_function_name", {}, "return \"hello world!\";", false, false, false);
   Blast::Cpp::FunctionFormatter function_formatter(function);

   std::string expected_returned_string = "void my_function_name()\n{\n   return \"hello world!\";\n}\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_definition());
}


TEST(FunctionFormatterTest, get_function_definition__with_a_function_with_parameter__returns_the_expected_formatted_string)
{
   Blast::Cpp::FunctionArgument function_argument("std::vector<std::string>", "my_parameter", "{ \"one-default-element\" }");
   Blast::Cpp::Function function("void", "my_function_name", { function_argument }, "return \"hello world!\";", false, false, false);
   Blast::Cpp::FunctionFormatter function_formatter(function);

   std::string expected_returned_string = "void my_function_name(std::vector<std::string> my_parameter)\n{\n   return \"hello world!\";\n}\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_definition());
}


TEST(FunctionFormatterTest, get_function_definition__with_a_class_name_returns_the_expected_formatted_string)
{
   Blast::Cpp::Function function("void", "my_function_name", {}, "return \"hello world!\";", false, false, false);
   Blast::Cpp::FunctionFormatter function_formatter(function, "MyClassName");

   std::string expected_returned_string = "void MyClassName::my_function_name()\n{\n   return \"hello world!\";\n}\n";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_definition());
}


TEST(FunctionFormatterTest, get_function_definition__with_a_pure_virtual_function_returns_the_expected_empty_string)
{
   Blast::Cpp::Function function("void", "my_function_name", {}, "return \"hello world!\";", false, false, false, false, true);
   Blast::Cpp::FunctionFormatter function_formatter(function, "MyClassName");

   std::string expected_returned_string = "";
   ASSERT_EQ(expected_returned_string, function_formatter.get_function_definition());
}


