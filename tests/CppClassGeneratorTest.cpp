

#include <gtest/gtest.h>

#include <Blast/CppClassGenerator.hpp>

#include <cmath>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


class CppClassGeneratorTest : public ::testing::Test
{
protected:
   static Blast::CppClassGenerator class_generator_fixture;

   virtual void SetUp()
   {
      class_generator_fixture = Blast::CppClassGenerator("User", {}, {}, {
         //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
         { "int", "last_id", "0", true, false, false, false },
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

   //std::vector<Blast::ClassAttributeProperties> expected_class_attribute_properties = {};
   //std::vector<Blast::SymbolDependencies> expected_symbol_dependencies = {};

   ASSERT_EQ("UnnamedClass", class_generator.get_class_name());
   ASSERT_FALSE(class_generator.has_namespaces());
   //ASSERT_EQ(expected_class_attribute_properties, class_generator.get_class_attribute_properties_ref());
   //ASSERT_EQ(expected_symbol_dependencies, class_generator.get_symbol_dependencies_ref());
}


TEST_F(CppClassGeneratorTest, can_get_and_set_the_class_name)
{
   Blast::CppClassGenerator class_generator;

   class_generator.set_class_name("FooClass");
   ASSERT_EQ("FooClass", class_generator.get_class_name());
   class_generator.set_class_name("Animal");
   ASSERT_EQ("Animal", class_generator.get_class_name());
   class_generator.set_class_name("ClassAttributeProperties");
   ASSERT_EQ("ClassAttributeProperties", class_generator.get_class_name());
}


TEST_F(CppClassGeneratorTest, has_parent_classes__returns_true_if_parent_classes_are_present)
{
   Blast::CppClassGenerator class_generator1("CppClassGenerator", {}, { { "Blast" } });
   ASSERT_TRUE(class_generator1.has_parent_classes());

   Blast::CppClassGenerator class_generator2("Ascend", {}, { { "ActionBase" }, { "Scriptable<Ascend>" } });
   ASSERT_TRUE(class_generator2.has_parent_classes());
}


TEST_F(CppClassGeneratorTest, has_parent_classes__returns_false_if_parent_classes_are_not_present)
{
   Blast::CppClassGenerator class_generator("User");
   ASSERT_FALSE(class_generator.has_parent_classes());
}


TEST_F(CppClassGeneratorTest, has_namespaces__returns_true_if_namespaces_are_present)
{
   Blast::CppClassGenerator class_generator1("CppClassGenerator", { "Blast" });
   ASSERT_TRUE(class_generator1.has_namespaces());

   Blast::CppClassGenerator class_generator2("Ascend", { "Fullscore", "Action", "Transform" });
   ASSERT_TRUE(class_generator2.has_namespaces());
}


TEST_F(CppClassGeneratorTest, has_namespaces__returns_false_if_namespaces_are_not_present)
{
   Blast::CppClassGenerator class_generator("User");
   ASSERT_FALSE(class_generator.has_namespaces());
}


TEST_F(CppClassGeneratorTest, private_scope_specifier__returns_a_string_formatted_with_the_appropriate_scope_specifier)
{
   std::string expected_scope_specifier = "   private:\n";
   ASSERT_EQ(expected_scope_specifier, class_generator_fixture.private_scope_specifier(1));
}


TEST_F(CppClassGeneratorTest, public_scope_specifier__returns_a_string_formatted_with_the_appropriate_scope_specifier)
{
   std::string expected_scope_specifier = "   public:\n";
   ASSERT_EQ(expected_scope_specifier, class_generator_fixture.public_scope_specifier(1));
}


TEST_F(CppClassGeneratorTest, protected_scope_specifier__returns_a_string_formatted_with_the_appropriate_scope_specifier)
{
   std::string expected_scope_specifier = "   protected:\n";
   ASSERT_EQ(expected_scope_specifier, class_generator_fixture.protected_scope_specifier(1));
}


TEST_F(CppClassGeneratorTest, namespaces_scope_opener__returns_a_formatted_string_of_the_opener_namespace_statement_without_nested_indentations)
{
   Blast::CppClassGenerator class_generator("Ascend", { "Fullscore", "Action", "Transform" });
   std::string expected_opener_namespace_statement = "namespace Fullscore\n{\nnamespace Action\n{\nnamespace Transform\n{\n";
   ASSERT_EQ(expected_opener_namespace_statement, class_generator.namespaces_scope_opener(false));
}


TEST_F(CppClassGeneratorTest, namespaces_scope_opener__returns_a_formatted_string_of_the_opener_namespace_statement_with_nested_indentations)
{
   Blast::CppClassGenerator class_generator("Ascend", { "Fullscore", "Action", "Transform" });
   std::string expected_opener_namespace_statement = "namespace Fullscore\n{\n   namespace Action\n   {\n      namespace Transform\n      {\n";
   ASSERT_EQ(expected_opener_namespace_statement, class_generator.namespaces_scope_opener(true));
}


TEST_F(CppClassGeneratorTest, namespaces_scope_opener__without_namespaces_returns_an_empty_string)
{
   ASSERT_EQ("", class_generator_fixture.namespaces_scope_opener(true));
}


TEST_F(CppClassGeneratorTest, namespaces_scope_closer__returns_a_formatted_string_of_the_closer_namespace_statement_without_nested_indentations)
{
   Blast::CppClassGenerator class_generator("Ascend", { "Fullscore", "Action", "Transform" });
   std::string expected_closer_namespace_statement = "}\n}\n}\n";
   ASSERT_EQ(expected_closer_namespace_statement, class_generator.namespaces_scope_closer(false));
}


TEST_F(CppClassGeneratorTest, namespaces_scope_closer__returns_a_formatted_string_of_the_closer_namespace_statement_with_nested_indentations)
{
   Blast::CppClassGenerator class_generator("Ascend", { "Fullscore", "Action", "Transform" });
   std::string expected_closer_namespace_statement = "      }\n   }\n}\n";
   ASSERT_EQ(expected_closer_namespace_statement, class_generator.namespaces_scope_closer(true));
}


TEST_F(CppClassGeneratorTest, namespaces_scope_closer__can_optionally_include_closer_comment)
{
   Blast::CppClassGenerator class_generator("Ascend", { "Fullscore", "Action", "Transform" });
   std::string expected_closer_namespace_statement = "      } // namespace Transform\n   } // namespace Action\n} // namespace Fullscore\n";
   ASSERT_EQ(expected_closer_namespace_statement, class_generator.namespaces_scope_closer(true, true));
}


TEST_F(CppClassGeneratorTest, namespaces_scope_closer__without_namespaces_returns_an_empty_string)
{
   ASSERT_EQ("", class_generator_fixture.namespaces_scope_closer(false));
}


TEST_F(CppClassGeneratorTest, class_declaration_inheritence_list__returns_a_formatted_string_listing_the_inherited_classes_for_a_class_opener_statement)
{
   Blast::CppClassGenerator class_generator("Ascend", {}, { { "Action", "\"ascend_action\"", "private" }, { "Scriptable<Ascend>", "", "protected" } });

   std::string expected_elements = " : private Action, protected Scriptable<Ascend>";
   ASSERT_EQ(expected_elements, class_generator.class_declaration_inheritence_list());
}


TEST_F(CppClassGeneratorTest, class_declaration_opener__returns_a_formatted_string_of_the_classes_opener_statement)
{
   Blast::CppClassGenerator class_generator("Happiness");
   std::string expected_class_opener_statement = "   class Happiness\n   {\n";
   ASSERT_EQ(expected_class_opener_statement, class_generator.class_declaration_opener(1));
}


TEST_F(CppClassGeneratorTest, class_declaration_closer_returns_a_formatted_string_of_the_classes_closing_statemet)
{
   Blast::CppClassGenerator class_generator("Happiness");
   std::string expected_closing_class_statement = "   };\n";
   ASSERT_EQ(expected_closing_class_statement, class_generator.class_declaration_closer(1));
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


TEST_F(CppClassGeneratorTest, initialization_list_elements__does_not_include_static_members)
{
   // TODO
}


TEST_F(CppClassGeneratorTest, class_declaration_opener_inheritence_elements__returns_a_list_of_formatted_inheritence_elements_for_the_class_declaration_opener)
{
   Blast::CppClassGenerator class_generator("Ascend", {}, { { "Action", "\"ascend_action\"", "private" }, { "Scriptable<Ascend>", "", "protected" } });

   std::vector<std::string> expected_elements = { "private Action", "protected Scriptable<Ascend>" };
   ASSERT_EQ(expected_elements, class_generator.class_declaration_opener_inheritence_elements());
}


TEST_F(CppClassGeneratorTest, static_attribute_definition_elements__returns_the_expected_list_of_formatted_static_attribute_definitions)
{
   std::vector<Blast::SymbolDependencies> symbol_dependencies = {
      { "int" },
      { "float" },
   };

   Blast::CppClassGenerator class_generator("User", {}, {}, {
         //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter
         { "int", "next_id", "0", true, false, false, false },
         { "int", "id", "next_id++", false, false, true, false },
         { "float", "time_velocity", "13.0f", true, false, false, false },
      },
      symbol_dependencies
   );

   std::vector<std::string> expected_elements = { "int User::next_id = 0;", "float User::time_velocity = 13.0f;" };
   ASSERT_EQ(expected_elements, class_generator.static_attribute_definition_elements());
}



TEST_F(CppClassGeneratorTest, header_filename__returns_the_filename_for_the_header_of_the_class)
{
   std::string expected_header_filename = "User.hpp";
   ASSERT_EQ(expected_header_filename, class_generator_fixture.header_filename());
}


TEST_F(CppClassGeneratorTest, source_filename__returns_the_filename_for_the_header_of_the_class)
{
   std::string expected_source_filename = "User.cpp";
   ASSERT_EQ(expected_source_filename, class_generator_fixture.source_filename());
}


TEST_F(CppClassGeneratorTest, header_include_directive__returns_the_include_line_to_include_the_class_header_file)
{
   std::string expected_header_directive = "#include <ProjectName/User.hpp>\n";
   ASSERT_EQ(expected_header_directive, class_generator_fixture.header_include_directive("ProjectName"));
}


TEST_F(CppClassGeneratorTest, dependency_include_directives__returns_a_list_of_directives_for_the_existing_dependencies_for_a_classes_properties)
{
   std::vector<Blast::SymbolDependencies> symbol_dependencies = {
      { "std::string", { "string" } },
      { "Blast::DiceRoller", { "Blast/DiceRoller.hpp" } },
   };

   Blast::CppClassGenerator class_generator("User", {}, {}, {
         { "std::string", "name", "\"[unnamed]\"", false, true, true, true },
         { "Blast::DiceRoller", "dice_roller", "{}", false, true, true, true },
      },
      symbol_dependencies
   );

   std::string expected_dependency_directives = "#include <Blast/DiceRoller.hpp>\n#include <string>\n";
   ASSERT_EQ(expected_dependency_directives, class_generator.dependency_include_directives());
}


TEST_F(CppClassGeneratorTest, dependency_include_directives__includes_the_list_of_dependencies_for_parent_classes)
{
   std::vector<Blast::SymbolDependencies> symbol_dependencies = {
      { "ActionBase", { "Fullscore/Action/ActionBase.hpp" } },
      { "Scriptable<Ascend>", { "Blast/Scriptable.hpp" } },
   };

   Blast::CppClassGenerator class_generator("Ascend", {}, { { "ActionBase" }, { "Scriptable<Ascend>" } }, {}, symbol_dependencies);

   std::string expected_dependency_directives = "#include <Blast/Scriptable.hpp>\n#include <Fullscore/Action/ActionBase.hpp>\n";
   ASSERT_EQ(expected_dependency_directives, class_generator.dependency_include_directives());
}


TEST_F(CppClassGeneratorTest, dependency_include_directives__when_no_dependencies_are_required_returns_an_empty_string)
{
   std::vector<Blast::SymbolDependencies> symbol_dependencies = {
      { "int" },
      { "float" },
   };

   Blast::CppClassGenerator class_generator("User", {}, {}, {
         //std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter
         { "int", "num_sides", "0", false, false, true, false },
         { "float", "radius", "6.0f", false, true, true, true },
      },
      symbol_dependencies
   );

   ASSERT_EQ("", class_generator.dependency_include_directives());
}


TEST_F(CppClassGeneratorTest, dependency_include_directives__when_a_symbol_dependency_is_not_defined_raises_an_exception)
{
   Blast::CppClassGenerator class_generator("User", {}, { { "SomeUndefinedParentClass" } }, {
         { "some_undefined_symbol", "foofoo", "\"foobar\"", false, false, true, false },
      }
   );

   std::string expected_error_message = "Undefined symbol for datatypes [ \"SomeUndefinedParentClass\", \"some_undefined_symbol\",  ]";
   ASSERT_THROW_WITH_MESSAGE(class_generator.dependency_include_directives(), std::runtime_error, expected_error_message);
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


TEST_F(CppClassGeneratorTest, project_source_filepath__returns_a_string_of_the_location_of_the_source_file_relative_to_the_project_root)
{
   std::string expected_project_source_filepath = "src/User.cpp";
   ASSERT_EQ(expected_project_source_filepath, class_generator_fixture.project_source_filepath());
}


TEST_F(CppClassGeneratorTest, project_header_filepath__returns_a_string_of_the_location_of_the_header_file_relative_to_the_project_root)
{
   std::string expected_project_header_filepath = "include/ProjectName/User.hpp";
   ASSERT_EQ(expected_project_header_filepath, class_generator_fixture.project_header_filepath("ProjectName"));
}


