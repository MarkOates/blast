

#include <gtest/gtest.h>

#include <Blast/Cpp/ParentClassProperties.hpp>

#include <cmath>


TEST(ParentClassPropertiesTest, can_be_created)
{
   Blast::Cpp::ParentClassProperties parent_class_properties;
}


TEST(ParentClassPropertiesTest, when_created_without_arguments_has_the_expected_values)
{
   Blast::Cpp::ParentClassProperties parent_class_properties;

   ASSERT_EQ("", parent_class_properties.get_class_name());
   ASSERT_EQ("", parent_class_properties.get_constructor_arguments());
   ASSERT_EQ("public", parent_class_properties.get_scope_specifier());
}


TEST(ParentClassPropertiesTest, when_created_with_arguments_sets_the_expected_values)
{
   Blast::Cpp::ParentClassProperties parent_class_properties("Donkey", "13", "private");

   ASSERT_EQ("Donkey", parent_class_properties.get_class_name());
   ASSERT_EQ("13", parent_class_properties.get_constructor_arguments());
   ASSERT_EQ("private", parent_class_properties.get_scope_specifier());
}


TEST(ParentClassPropertiesTest, can_get_and_set_class_name)
{
   Blast::Cpp::ParentClassProperties parent_class_properties;

   parent_class_properties.set_class_name("Animal");
   ASSERT_EQ("Animal", parent_class_properties.get_class_name());
   parent_class_properties.set_class_name("Blast::Cpp::ParentClassProperties");
   ASSERT_EQ("Blast::Cpp::ParentClassProperties", parent_class_properties.get_class_name());
   parent_class_properties.set_class_name("Hamster");
   ASSERT_EQ("Hamster", parent_class_properties.get_class_name());
}


TEST(ParentClassPropertiesTest, can_get_and_set_scope_specifier)
{
   Blast::Cpp::ParentClassProperties parent_class_properties;

   parent_class_properties.set_scope_specifier("public");
   ASSERT_EQ("public", parent_class_properties.get_scope_specifier());
   parent_class_properties.set_scope_specifier("private");
   ASSERT_EQ("private", parent_class_properties.get_scope_specifier());
   parent_class_properties.set_scope_specifier("protected");
   ASSERT_EQ("protected", parent_class_properties.get_scope_specifier());
}


TEST(ParentClassPropertiesTest, when_constructing_with_an_invalid_scope_specifier_raises_an_exception)
{
   ASSERT_THROW(Blast::Cpp::ParentClassProperties("Donkey", "13", "not a valid property"), std::invalid_argument);
}


TEST(ParentClassPropertiesTest, when_setting_a_scope_specifier_to_an_invalid_value_raises_an_exception)
{
   Blast::Cpp::ParentClassProperties parent_class_properties;
   ASSERT_THROW(parent_class_properties.set_scope_specifier("not a valid property"), std::invalid_argument);
}


TEST(ParentClassPropertiesTest, can_get_and_set_constructor_arguments)
{
   Blast::Cpp::ParentClassProperties parent_class_properties;

   parent_class_properties.set_constructor_arguments("\"Donkey\"");
   ASSERT_EQ("\"Donkey\"", parent_class_properties.get_constructor_arguments());
   parent_class_properties.set_constructor_arguments("1234, \"tree\", new SurfaceAreaBox(3, 5, 7, 13)");
   ASSERT_EQ("1234, \"tree\", new SurfaceAreaBox(3, 5, 7, 13)", parent_class_properties.get_constructor_arguments());
}


TEST(ParentClassPropertiesTest, as_class_inheritence_declaration__returns_a_string_formatted_for_class_inheritence_declaration)
{
   Blast::Cpp::ParentClassProperties parent_class_properties("Donkey", "1234, \"tree\", new SurfaceAreaBox(3, 5, 7, 13)", "private");
   std::string expected_initialization_list_argument = "private Donkey";
   ASSERT_EQ(expected_initialization_list_argument, parent_class_properties.as_class_inheritence_declaration());
}


TEST(ParentClassPropertiesTest, as_argument_in_initialization_list__returns_a_string_formatted_for_an_initialization_list)
{
   Blast::Cpp::ParentClassProperties parent_class_properties("Donkey", "1234, \"tree\", new SurfaceAreaBox(3, 5, 7, 13)", "private");
   std::string expected_initialization_list_argument = "Donkey(1234, \"tree\", new SurfaceAreaBox(3, 5, 7, 13))";
   ASSERT_EQ(expected_initialization_list_argument, parent_class_properties.as_argument_in_initialization_list());
}


