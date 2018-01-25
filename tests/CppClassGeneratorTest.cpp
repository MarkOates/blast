

#include <gtest/gtest.h>

#include <Blast/CppClassGenerator.hpp>

#include <cmath>


class CppClassGeneratorTest : public ::testing::Test
{
protected:
   static Blast::CppClassGenerator class_generator_fixture;

   virtual void SetUp()
   {
      class_generator_fixture = Blast::CppClassGenerator("User", {
         //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
         { "int", "id", "last_id++", false, false, true, false },
         { "std::string", "name", "\"[unnamed]\"", false, true, true, true },
         { "type_t", "type", "MAGE", false, true, true, true },
      });
   }
};


Blast::CppClassGenerator CppClassGeneratorTest::class_generator_fixture = Blast::CppClassGenerator();


///////


TEST_F(CppClassGeneratorTest, can_be_created)
{
   Blast::CppClassGenerator class_generator;
}


TEST_F(CppClassGeneratorTest, without_arguments_sets_the_expected_default_values)
{
   Blast::CppClassGenerator class_generator;
}


TEST_F(CppClassGeneratorTest, get_class_attribute_properties_ref__returns_a_reference_to_the_class_attribute_properties)
{
   // TODO
}


TEST_F(CppClassGeneratorTest, get_symbol_dependencies_ref__returns_a_reference_to_the_symbol_dependencies)
{
   // TODO
}


TEST_F(CppClassGeneratorTest, constructor_declaration_elements__returns_the_expected_set_of_elements_in_a_declaration)
{
   std::vector<std::string> expected_elements = { "std::string name=\"[unnamed]\"", "type_t type=MAGE" };
   ASSERT_EQ(expected_elements, class_generator_fixture.constructor_declaration_elements());
}


TEST_F(CppClassGeneratorTest, constructor_definition_elements__returns_the_expected_set_of_elements_in_a_definition)
{
   std::vector<std::string> expected_elements = { "std::string name", "type_t type" };
   ASSERT_EQ(expected_elements, class_generator_fixture.constructor_definition_elements());
}


TEST_F(CppClassGeneratorTest, initialization_list_elements__when_properties_are_constructor_parameters__returns_variable_assigned_arguments)
{
   for (auto &class_attribute_property : class_generator_fixture.get_class_attribute_properties_ref())
      class_attribute_property.is_constructor_parameter = true;

   std::vector<std::string> expected_elements = { "id(id)", "name(name)", "type(type)" };
   ASSERT_EQ(expected_elements, class_generator_fixture.initialization_list_elements());
}


TEST_F(CppClassGeneratorTest, initialization_list_elements__when_properties_are_not_constructor_parameters__returns_initialization_value_assigned_elements)
{
   for (auto &class_attribute_property : class_generator_fixture.get_class_attribute_properties_ref())
      class_attribute_property.is_constructor_parameter = false;

   std::vector<std::string> expected_elements = { "id(last_id++)", "name(\"[unnamed]\")", "type(MAGE)" };
   ASSERT_EQ(expected_elements, class_generator_fixture.initialization_list_elements());
}


TEST_F(CppClassGeneratorTest, header_filename__returns_the_filename_for_the_header_of_the_class)
{
   std::string expected_header_filename = "User.hpp";
   ASSERT_EQ(expected_header_filename, class_generator_fixture.header_filename());
}


TEST_F(CppClassGeneratorTest, header_include_directive__returns_the_include_line_to_include_the_class_header_file)
{
   std::string expected_header_directive = "#include <Blast/User.hpp>\n";
   ASSERT_EQ(expected_header_directive, class_generator_fixture.header_include_directive());
}


TEST_F(CppClassGeneratorTest, class_property_list__returns_the_expected_formatted_string_of_class_properties)
{
   std::string expected_property_list = "   int id;\n   std::string name;\n   type_t type;\n";
   ASSERT_EQ(expected_property_list, class_generator_fixture.class_property_list(1));
}


TEST_F(CppClassGeneratorTest, getter_function_declarations__returns_the_expected_formatted_string_for_properties_with_getter_functions)
{
   std::vector<Blast::ClassAttributeProperties> &class_attribute_properties = class_generator_fixture.get_class_attribute_properties_ref();
   class_attribute_properties[0].has_getter = true;
   class_attribute_properties[1].has_getter = false;
   class_attribute_properties[2].has_getter = true;

   std::string expected_declarations_list = "   int get_id();\n   type_t get_type();\n";
   ASSERT_EQ(expected_declarations_list, class_generator_fixture.getter_function_declarations(1));
}


TEST_F(CppClassGeneratorTest, getter_function_definitions__returns_the_expected_formatted_definitions_for_properties_with_getter_functions)
{
   std::vector<Blast::ClassAttributeProperties> &class_attribute_properties = class_generator_fixture.get_class_attribute_properties_ref();
   class_attribute_properties[0].has_getter = true;
   class_attribute_properties[1].has_getter = false;
   class_attribute_properties[2].has_getter = true;

   std::string expected_definition_list = "int User::get_id()\n{\n   return id;\n}\n\n\ntype_t User::get_type()\n{\n   return type;\n}\n\n\n";
   ASSERT_EQ(expected_definition_list, class_generator_fixture.getter_function_definitions());
}


TEST_F(CppClassGeneratorTest, setter_function_declarations_returns_the_expected_formatted_declarations_for_properties_with_setter_functions)
{
   std::string expected_declarations_list = "   void set_name(std::string name);\n   void set_type(type_t type);\n";
   ASSERT_EQ(expected_declarations_list, class_generator_fixture.setter_function_declarations(1));
}


TEST_F(CppClassGeneratorTest, setter_function_definitions__returns_the_expected_formatted_definitions_for_properties_with_setter_functions)
{
   std::string expected_definition_list = "void User::set_name(std::string name)\n{\n   this->name = name;\n}\n\n\nvoid User::set_type(type_t type)\n{\n   this->type = type;\n}\n\n\n";
   ASSERT_EQ(expected_definition_list, class_generator_fixture.setter_function_definitions(0));
}


TEST_F(CppClassGeneratorTest, initialization_list__returns_the_expected_formatted_string)
{
   std::string expected_initialization_list = "   : id(last_id++)\n   , name(name)\n   , type(type)\n";
   ASSERT_EQ(expected_initialization_list, class_generator_fixture.initialization_list(1));
}


TEST_F(CppClassGeneratorTest, constructor_declaration__returns_the_expected_string)
{
   std::string expected_constructor_declaration = "User(std::string name=\"[unnamed]\", type_t type=MAGE);\n";
   ASSERT_EQ(expected_constructor_declaration, class_generator_fixture.constructor_declaration());
}


TEST_F(CppClassGeneratorTest, constructor_definition_returns_the_expected_string)
{
   std::string expected_constructor_definition = "User::User(std::string name, type_t type)\n   : id(last_id++)\n   , name(name)\n   , type(type)\n{\n}\n";
   ASSERT_EQ(expected_constructor_definition, class_generator_fixture.constructor_definition(0));
}


TEST_F(CppClassGeneratorTest, destructor_declaration__returns_the_expected_string)
{
   std::string expected_destructor_declaration = "~User();\n";
   ASSERT_EQ(expected_destructor_declaration, class_generator_fixture.destructor_declaration());
}


TEST_F(CppClassGeneratorTest, destructor_definition_returns_the_expected_string)
{
   std::string expected_destructor_definition = "User::~User()\n{\n}\n";
   ASSERT_EQ(expected_destructor_definition, class_generator_fixture.destructor_definition());
}


