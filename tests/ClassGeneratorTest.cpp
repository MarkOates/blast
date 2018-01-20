

#include <gtest/gtest.h>

#include <Blast/ClassGenerator.hpp>

#include <cmath>


TEST(ClassGeneratorTest, can_be_created)
{
   ClassGenerator class_generator;
}


TEST(ClassGeneratorTest, without_arguments_sets_the_expected_default_values)
{
   ClassGenerator class_generator;
}


TEST(ClassGeneratorTest, constructor_declaration_elements__returns_the_expected_set_of_elements_in_a_declaration)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", true, true, true },
      { "type_t", "type", "MAGE", true, true, true },
   });

   std::vector<std::string> expected_elements = {
      "std::string name=\"[unnamed]\"",
      "type_t type=MAGE",
   };

   ASSERT_EQ(expected_elements, class_generator.constructor_declaration_elements());
}


TEST(ClassGeneratorTest, constructor_definition_elements__returns_the_expected_set_of_elements_in_a_definition)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", true, true, true },
      { "type_t", "type", "MAGE", true, true, true },
   });

   std::vector<std::string> expected_elements = {
      "std::string name",
      "type_t type",
   };

   ASSERT_EQ(expected_elements, class_generator.constructor_definition_elements());
}


TEST(ClassGeneratorTest, initialization_list_elements__when_properties_are_constructor_parameters__returns_variable_assigned_arguments)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", true, true, false },
      { "std::string", "name", "\"[unnamed]\"", true, true, true },
      { "type_t", "type", "MAGE", true, true, true },
   });

   std::vector<std::string> expected_elements = {
      "id(id)",
      "name(name)",
      "type(type)",
   };

   ASSERT_EQ(expected_elements, class_generator.initialization_list_elements());
}


TEST(ClassGeneratorTest, initialization_list_elements__when_properties_are_not_constructor_parameters__returns_initialization_value_assigned_elements)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", false, true, true },
      { "type_t", "type", "MAGE", false, true, true },
   });

   std::vector<std::string> expected_elements = {
      "id(last_id++)",
      "name(\"[unnamed]\")",
      "type(MAGE)",
   };

   ASSERT_EQ(expected_elements, class_generator.initialization_list_elements());
}


TEST(ClassGeneratorTest, class_property_list__returns_the_expected_formatted_string_of_class_properties)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", false, true, true },
      { "type_t", "type", "MAGE", false, true, true },
   });

   std::string expected_property_list = "   int id;\n   std::string name;\n   type_t type;\n";
   ASSERT_EQ(expected_property_list, class_generator.class_property_list());
}


TEST(ClassGeneratorTest, initialization_list__returns_the_expected_formatted_string)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", true, true, true },
      { "type_t", "type", "MAGE", true, true, true },
   });

   std::string expected_initialization_list = "   : id(last_id++)\n   , name(name)\n   , type(type)\n";
   ASSERT_EQ(expected_initialization_list, class_generator.initialization_list());
}


TEST(ClassGeneratorTest, constructor_declaration__returns_the_expected_string)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", true, true, true },
      { "type_t", "type", "MAGE", true, true, true },
   });

   ASSERT_EQ("User(std::string name=\"[unnamed]\", type_t type=MAGE);", class_generator.constructor_declaration());
}


TEST(ClassGeneratorTest, constructor_definition_returns_the_expected_string)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", true, true, true },
      { "type_t", "type", "MAGE", true, true, true },
   });

   ASSERT_EQ("User::User(std::string name, type_t type)\n   : id(last_id++)\n   , name(name)\n   , type(type)\n{\n}\n", class_generator.constructor_definition());
}


TEST(ClassGeneratorTest, destructor_declaration__returns_the_expected_string)
{
   ClassGenerator class_generator("User", {});
   ASSERT_EQ("~User();", class_generator.destructor_declaration());
}


TEST(ClassGeneratorTest, destructor_definition_returns_the_expected_string)
{
   ClassGenerator class_generator("User", {});
   ASSERT_EQ("User::~User()\n{\n}\n", class_generator.destructor_definition());
}


