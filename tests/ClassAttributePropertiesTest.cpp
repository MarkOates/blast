

#include <gtest/gtest.h>

#include <Blast/ClassAttributeProperties.hpp>

#include <cmath>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


TEST(ClassAttributePropertiesTest, can_be_created)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, true, false, false);
}


TEST(ClassAttributePropertiesTest, as_constructor_argument_in_declaration__when_not_a_constructor_argument_returns_an_empty_string)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false, false);

   ASSERT_EQ("", attribute_properties.as_constructor_argument_in_declaration());
}


TEST(ClassAttributePropertiesTest, as_constructor_argument_in_declaration__returns_the_expected_string)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, true, false, false);

   std::string expected_string = "std::string my_variable=\"Hello World!\"";
   ASSERT_EQ(expected_string, attribute_properties.as_constructor_argument_in_declaration());
}


TEST(ClassAttributePropertiesTest, as_constructor_argument_in_declaration__when_called_on_a_static_variable_raises_an_exception)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", true, true, false, false);

   std::string expected_error_message = "Class attribute \"my_variable\" cannot be a constructor argument in a declaration; is static.";
   ASSERT_THROW_WITH_MESSAGE(attribute_properties.as_constructor_argument_in_declaration(), std::runtime_error, expected_error_message);
}


TEST(ClassAttributePropertiesTest, as_constructor_argument_in_definition__returns_the_expected_string)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, true, false, false);

   std::string expected_string = "std::string my_variable";
   ASSERT_EQ(expected_string, attribute_properties.as_constructor_argument_in_definition());
}


TEST(ClassAttributePropertiesTest, as_constructor_argument_in_definition__when_called_on_a_static_variable_raises_an_exception)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", true, true, false, false);

   std::string expected_error_message = "Class attribute \"my_variable\" cannot be a constructor argument in a definition; is static.";
   ASSERT_THROW_WITH_MESSAGE(attribute_properties.as_constructor_argument_in_definition(), std::runtime_error, expected_error_message);
}


TEST(ClassAttributePropertiesTest, as_argument_in_initialization_list__when_is_a_constructor_argument__returns_a_string_with_a_variable_assignment)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, true, false, false);

   std::string expected_string = "my_variable(my_variable)";
   ASSERT_EQ(expected_string, attribute_properties.as_argument_in_initialization_list());
}


TEST(ClassAttributePropertiesTest, as_argument_in_initialization_list__when_is_not_a_constructor_argument__returns_a_string_with_the_initialization_value)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false, false);

   std::string expected_string = "my_variable(\"Hello World!\")";
   ASSERT_EQ(expected_string, attribute_properties.as_argument_in_initialization_list());
}


TEST(ClassAttributePropertiesTest, as_class_property__formats_the_attribute_as_listed_in_a_class_declaration)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false, false);

   std::string expected_string = "std::string my_variable";
   ASSERT_EQ(expected_string, attribute_properties.as_class_property());
}


TEST(ClassAttributePropertiesTest, as_class_property__formats_the_attribute_as_listed_in_a_class_declaration_with_the_appropriate_static_qualifier)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", true, false, false, false);

   std::string expected_string = "static std::string my_variable";
   ASSERT_EQ(expected_string, attribute_properties.as_class_property());
}


TEST(ClassAttributePropertiesTest, as_static_definition__formats_the_attribute_as_defined_as_a_static_member)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", true, false, false, false);

   std::string expected_string = "std::string FooClass::my_variable = \"Hello World!\";";
   ASSERT_EQ(expected_string, attribute_properties.as_static_definition("FooClass"));
}


TEST(ClassAttributePropertiesTest, getter_function_symbol__returns_the_symbol_used_for_the_getter_function)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false, false);

   std::string expected_string = "get_my_variable";
   ASSERT_EQ(expected_string, attribute_properties.getter_function_symbol());
}


TEST(ClassAttributePropertiesTest, getter_function_declaration__formats_the_function_as_a_getter_function_listed_in_a_class_declaration)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false, false);

   std::string expected_string = "std::string get_my_variable();";
   ASSERT_EQ(expected_string, attribute_properties.getter_function_declaration());
}


TEST(ClassAttributePropertiesTest, getter_function_declaration__formats_the_function_as_a_getter_function_listed_in_a_static_class_declaration)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", true, false, false, false);

   std::string expected_string = "static std::string get_my_variable();";
   ASSERT_EQ(expected_string, attribute_properties.getter_function_declaration());
}


TEST(ClassAttributePropertiesTest, getter_function_definition__formats_the_function_as_a_getter_function_listed_in_a_class_definition)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false, false);

   std::string expected_string = "std::string FooClass::get_my_variable()\n{\n   return my_variable;\n}\n";
   ASSERT_EQ(expected_string, attribute_properties.getter_function_definition("FooClass"));
}


TEST(ClassAttributePropertiesTest, setter_function_symbol__returns_the_symbol_used_for_the_setter_function)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false, false);

   std::string expected_string = "set_my_variable";
   ASSERT_EQ(expected_string, attribute_properties.setter_function_symbol());
}


TEST(ClassAttributePropertiesTest, setter_function_declaration__formats_the_function_as_a_setter_function_listed_in_a_class_declaration)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false, false);

   std::string expected_string = "void set_my_variable(std::string my_variable);";
   ASSERT_EQ(expected_string, attribute_properties.setter_function_declaration());
}


TEST(ClassAttributePropertiesTest, setter_function_definition__formats_the_function_as_a_setter_function_listed_in_a_class_definition)
{
   Blast::ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false, false);

   std::string expected_string = "void FooClass::set_my_variable(std::string my_variable)\n{\n   this->my_variable = my_variable;\n}\n";
   ASSERT_EQ(expected_string, attribute_properties.setter_function_definition("FooClass"));
}


