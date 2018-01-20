

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
   ASSERT_EQ(expected_property_list, class_generator.class_property_list(1));
}


TEST(ClassGeneratorTest, getter_function_declarations__returns_the_expected_formatted_string_for_properties_with_getter_functions)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", false, false, true },
      { "type_t", "type", "MAGE", false, true, true },
   });

   std::string expected_declarations_list = "   int get_id();\n   type_t get_type();\n";
   ASSERT_EQ(expected_declarations_list, class_generator.getter_function_declarations(1));
}


TEST(ClassGeneratorTest, getter_function_definitions__returns_the_expected_formatted_definitions_for_properties_with_getter_functions)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", false, false, true },
      { "type_t", "type", "MAGE", false, true, true },
   });

   std::string expected_definition_list = "int User::get_id()\n{\n   return id;\n}\n\n\ntype_t User::get_type()\n{\n   return type;\n}\n\n\n";
   ASSERT_EQ(expected_definition_list, class_generator.getter_function_definitions());
}


TEST(ClassGeneratorTest, setter_function_declarations_returns_the_expected_formatted_declarations_for_properties_with_setter_functions)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", false, false, true },
      { "type_t", "type", "MAGE", false, true, true },
   });

   std::string expected_declarations_list = "   void set_name(std::string name);\n   void set_type(type_t type);\n";
   ASSERT_EQ(expected_declarations_list, class_generator.setter_function_declarations(1));
}


TEST(ClassGeneratorTest, setter_function_definitions__returns_the_expected_formatted_definitions_for_properties_with_setter_functions)
{
   ClassGenerator class_generator("User", {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "id", "last_id++", false, true, false },
      { "std::string", "name", "\"[unnamed]\"", false, false, true },
      { "type_t", "type", "MAGE", false, true, true },
   });

   std::string expected_definition_list = "void User::set_name(std::string name)\n{\n   this->name = name;\n}\n\n\nvoid User::set_type(type_t type)\n{\n   this->type = type;\n}\n\n\n";
   ASSERT_EQ(expected_definition_list, class_generator.setter_function_definitions(0));
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
   ASSERT_EQ(expected_initialization_list, class_generator.initialization_list(1));
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

   ASSERT_EQ("User::User(std::string name, type_t type)\n   : id(last_id++)\n   , name(name)\n   , type(type)\n{\n}\n", class_generator.constructor_definition(0));
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


