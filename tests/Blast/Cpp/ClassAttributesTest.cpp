

#include <gtest/gtest.h>

#include <Blast/Cpp/ClassAttributes.hpp>

#include <cmath>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


TEST(ClassAttributesTest, can_be_created)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, true, false, false, false, false, false, false, false
   );
}


TEST(ClassAttributesTest, as_constructor_argument_in_declaration__when_not_a_constructor_argument_returns_an_empty_string)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   ASSERT_EQ("", attribute_properties.as_constructor_argument_in_declaration());
}


TEST(ClassAttributesTest, as_constructor_argument_in_declaration__returns_the_expected_string)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, true, false, false, false, false, false, false, false
   );

   std::string expected_string = "std::string my_variable=\"Hello World!\"";
   ASSERT_EQ(expected_string, attribute_properties.as_constructor_argument_in_declaration());
}


TEST(ClassAttributesTest, as_constructor_argument_in_declaration__when_called_on_a_static_variable_raises_an_exception)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", true, true, false, false, false, false, false, false, false
   );

   std::string expected_error_message = "Class attribute \"my_variable\" cannot be a constructor argument in a declaration; is static.";
   ASSERT_THROW_WITH_MESSAGE(attribute_properties.as_constructor_argument_in_declaration(), std::runtime_error, expected_error_message);
}


TEST(ClassAttributesTest, as_constructor_argument_in_definition__returns_the_expected_string)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, true, false, false, false, false, false, false, false
   );

   std::string expected_string = "std::string my_variable";
   ASSERT_EQ(expected_string, attribute_properties.as_constructor_argument_in_definition());
}


TEST(ClassAttributesTest, as_constructor_argument_in_definition__when_called_on_a_static_variable_raises_an_exception)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", true, true, false, false, false, false, false, false, false
   );

   std::string expected_error_message = "Class attribute \"my_variable\" cannot be a constructor argument in a definition; is static.";
   ASSERT_THROW_WITH_MESSAGE(attribute_properties.as_constructor_argument_in_definition(), std::runtime_error, expected_error_message);
}


TEST(ClassAttributesTest, as_argument_in_initialization_list__when_is_a_constructor_argument__returns_a_string_with_a_variable_assignment)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, true, false, false, false, false, false, false, false
   );

   std::string expected_string = "my_variable(my_variable)";
   ASSERT_EQ(expected_string, attribute_properties.as_argument_in_initialization_list());
}


TEST(ClassAttributesTest, as_argument_in_initialization_list__when_is_not_a_constructor_argument__returns_a_string_with_the_initialization_value)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "my_variable(\"Hello World!\")";
   ASSERT_EQ(expected_string, attribute_properties.as_argument_in_initialization_list());
}


TEST(ClassAttributesTest, as_class_property__formats_the_attribute_as_listed_in_a_class_declaration)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "std::string my_variable";
   ASSERT_EQ(expected_string, attribute_properties.as_class_property());
}


TEST(ClassAttributesTest, as_class_property__formats_the_attribute_as_listed_in_a_class_declaration_with_the_appropriate_static_qualifier)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", true, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "static std::string my_variable";
   ASSERT_EQ(expected_string, attribute_properties.as_class_property());
}


TEST(ClassAttributesTest, as_static_definition__formats_the_attribute_as_defined_as_a_static_member)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", true, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "std::string FooClass::my_variable = \"Hello World!\";";
   ASSERT_EQ(expected_string, attribute_properties.as_static_definition("FooClass"));
}


TEST(ClassAttributesTest, getter_function_symbol__returns_the_symbol_used_for_the_getter_function)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "get_my_variable";
   ASSERT_EQ(expected_string, attribute_properties.getter_function_symbol());
}


TEST(ClassAttributesTest,
   getter_function_declaration__formats_the_function_as_a_getter_function_listed_in_a_class_declaration)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "std::string get_my_variable() const;";
   ASSERT_EQ(expected_string, attribute_properties.getter_function_declaration());
}


TEST(ClassAttributesTest,
   getter_function_declaration__formats_the_function_as_a_static_function_listed_in_a_class__and_does_not_include_const)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", true, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "static std::string get_my_variable();";
   ASSERT_EQ(expected_string, attribute_properties.getter_function_declaration());
}


TEST(ClassAttributesTest,
   getter_function_definition__formats_the_function_as_a_getter_function_listed_in_a_class_definition)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "std::string FooClass::get_my_variable() const\n{\n   return my_variable;\n}\n";
   ASSERT_EQ(expected_string, attribute_properties.getter_function_definition("FooClass"));
}


TEST(ClassAttributesTest, getter_ref_function_symbol__returns_the_symbol_used_for_the_getter_ref_function)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "get_my_variable_ref";
   ASSERT_EQ(expected_string, attribute_properties.getter_ref_function_symbol());
}


TEST(ClassAttributesTest, getter_ref_function_declaration__formats_the_function_as_a_getter_ref_function_listed_in_a_class_declaration)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "std::string &get_my_variable_ref();";
   ASSERT_EQ(expected_string, attribute_properties.getter_ref_function_declaration());
}


TEST(ClassAttributesTest, getter_ref_function_declaration__formats_the_function_as_a_getter_ref_function_listed_in_a_static_class_declaration)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", true, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "static std::string &get_my_variable_ref();";
   ASSERT_EQ(expected_string, attribute_properties.getter_ref_function_declaration());
}


TEST(ClassAttributesTest, getter_ref_function_definition__formats_the_function_as_a_getter_ref_function_listed_in_a_class_definition)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "std::string &FooClass::get_my_variable_ref()\n{\n   return my_variable;\n}\n";
   ASSERT_EQ(expected_string, attribute_properties.getter_ref_function_definition("FooClass"));
}


TEST(ClassAttributesTest, setter_function_symbol__returns_the_symbol_used_for_the_setter_function)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "set_my_variable";
   ASSERT_EQ(expected_string, attribute_properties.setter_function_symbol());
}


TEST(ClassAttributesTest, setter_function_declaration__formats_the_function_as_a_setter_function_listed_in_a_class_declaration)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "void set_my_variable(std::string my_variable);";
   ASSERT_EQ(expected_string, attribute_properties.setter_function_declaration());
}


TEST(ClassAttributesTest, setter_function_definition__formats_the_function_as_a_setter_function_listed_in_a_class_definition)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );

   std::string expected_string = "void FooClass::set_my_variable(std::string my_variable)\n{\n   this->my_variable = my_variable;\n}\n";
   ASSERT_EQ(expected_string, attribute_properties.setter_function_definition("FooClass"));
}


TEST(ClassAttributesTest,
  setter_function_definition__when_before_init_setter_is_true__formats_the_function_as_a_setter_function_with_the_\
expectd_guard_clause)
{
   Blast::Cpp::ClassAttributes attribute_properties(
      "std::string", "my_variable", "\"Hello World!\"", false, false, false, false, false, false, false, false, false
   );
   attribute_properties.has_before_init_setter = true;

   std::string expected_string = R"END(void FooClass::set_my_variable(std::string my_variable)
{
   if (get_initialized()) throw std::runtime_error("[FooClass::set_my_variable]: error: guard \"get_initialized()\" not met.");
   this->my_variable = my_variable;
}
)END";
   ASSERT_EQ(expected_string, attribute_properties.setter_function_definition("FooClass"));
}


