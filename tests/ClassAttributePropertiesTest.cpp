

#include <gtest/gtest.h>

#include <Blast/ClassAttributeProperties.hpp>

#include <cmath>


TEST(ClassAttributePropertiesTest, can_be_created)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", true, false, false);
}


TEST(ClassAttributePropertiesTest, as_constructor_argument_in_declaration__when_not_a_constructor_argument_returns_an_empty_string)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false);

   ASSERT_EQ("", attribute_properties.as_constructor_argument_in_declaration());
}


TEST(ClassAttributePropertiesTest, as_constructor_argument_in_declaration__returns_the_expected_string)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", true, false, false);

   std::string expected_string = "std::string my_variable=\"Hello World!\"";
   ASSERT_EQ(expected_string, attribute_properties.as_constructor_argument_in_declaration());
}


TEST(ClassAttributePropertiesTest, as_constructor_argument_in_definition__returns_the_expected_string)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", true, false, false);

   std::string expected_string = "std::string my_variable";
   ASSERT_EQ(expected_string, attribute_properties.as_constructor_argument_in_definition());
}


TEST(ClassAttributePropertiesTest, as_argument_in_initialization_list__when_is_a_constructor_argument__returns_a_string_with_a_variable_assignment)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", true, false, false);

   std::string expected_string = "my_variable(my_variable)";
   ASSERT_EQ(expected_string, attribute_properties.as_argument_in_initialization_list());
}


TEST(ClassAttributePropertiesTest, as_argument_in_initialization_list__when_is_not_a_constructor_argument__returns_a_string_with_the_initialization_value)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false);

   std::string expected_string = "my_variable(\"Hello World!\")";
   ASSERT_EQ(expected_string, attribute_properties.as_argument_in_initialization_list());
}


TEST(ClassAttributePropertiesTest, as_class_property__formats_the_attribute_as_listed_in_a_class_declaration)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false);

   std::string expected_string = "std::string my_variable";
   ASSERT_EQ(expected_string, attribute_properties.as_class_property());
}


TEST(ClassAttributePropertiesTest, getter_function_declaration__formats_the_function_as_a_getter_function_listed_in_a_class_declaration)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false);

   std::string expected_string = "std::string get_my_variable();";
   ASSERT_EQ(expected_string, attribute_properties.getter_function_declaration());
}


TEST(ClassAttributePropertiesTest, getter_function_definition__formats_the_function_as_a_getter_function_listed_in_a_class_definition)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false);

   std::string expected_string = "std::string FooClass::get_my_variable()\n{\n   return my_variable;\n}\n";
   ASSERT_EQ(expected_string, attribute_properties.getter_function_definition("FooClass"));
}


TEST(ClassAttributePropertiesTest, setter_function_declaration__formats_the_function_as_a_setter_function_listed_in_a_class_declaration)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false);

   std::string expected_string = "void set_my_variable(std::string my_variable);";
   ASSERT_EQ(expected_string, attribute_properties.setter_function_declaration());
}


TEST(ClassAttributePropertiesTest, setter_function_definition__formats_the_function_as_a_setter_function_listed_in_a_class_definition)
{
   ClassAttributeProperties attribute_properties("std::string", "my_variable", "\"Hello World!\"", false, false, false);

   std::string expected_string = "void FooClass::set_my_variable(std::string my_variable)\n{\n   this->my_variable = my_variable;\n}\n";
   ASSERT_EQ(expected_string, attribute_properties.setter_function_definition("FooClass"));
}


