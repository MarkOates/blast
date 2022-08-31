

#include <gtest/gtest.h>

#include <Blast/Cpp/ClassGenerator.hpp>

#include <cmath>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


class ClassGeneratorTest : public ::testing::Test
{
protected:
   static Blast::Cpp::ClassGenerator class_generator_fixture;

   virtual void SetUp()
   {
      Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {
         //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter
         { "int", "last_id", "0", true, false, false, false, false, false, false },
         { "int", "id", "last_id++", false, false, true, false, false, false, false },
         { "std::string", "name", "\"[unnamed]\"", false, true, true, false, false, true, false },
         { "type_t", "type", "MAGE", false, true, true, false, false, true, false },
      });

      class_generator_fixture = Blast::Cpp::ClassGenerator(cpp_class);
   }
};


Blast::Cpp::ClassGenerator ClassGeneratorTest::class_generator_fixture = Blast::Cpp::ClassGenerator();


///////


TEST_F(ClassGeneratorTest, can_be_created)
{
   Blast::Cpp::ClassGenerator class_generator;
}


TEST_F(ClassGeneratorTest, private_scope_specifier__returns_a_string_formatted_with_the_appropriate_scope_specifier)
{
   std::string expected_scope_specifier = "   private:\n";
   ASSERT_EQ(expected_scope_specifier, class_generator_fixture.private_scope_specifier(1));
}


TEST_F(ClassGeneratorTest, public_scope_specifier__returns_a_string_formatted_with_the_appropriate_scope_specifier)
{
   std::string expected_scope_specifier = "   public:\n";
   ASSERT_EQ(expected_scope_specifier, class_generator_fixture.public_scope_specifier(1));
}


TEST_F(ClassGeneratorTest, protected_scope_specifier__returns_a_string_formatted_with_the_appropriate_scope_specifier)
{
   std::string expected_scope_specifier = "   protected:\n";
   ASSERT_EQ(expected_scope_specifier, class_generator_fixture.protected_scope_specifier(1));
}


TEST_F(ClassGeneratorTest,
   namespaces_scope_opener__returns_a_formatted_string_of_the_opener_namespace_statement_without_nested_indentations)
{
   Blast::Cpp::Class cpp_class("Ascend", { "Fullscore", "Action", "Transform" });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);
   std::string expected_opener_namespace_statement = "namespace Fullscore\n{\nnamespace Action\n{\nnamespace Transform\n{\n";
   ASSERT_EQ(expected_opener_namespace_statement, class_generator.namespaces_scope_opener(false));
}


TEST_F(ClassGeneratorTest,
   namespaces_scope_opener__returns_a_formatted_string_of_the_opener_namespace_statement_with_nested_indentations)
{
   Blast::Cpp::Class cpp_class("Ascend", { "Fullscore", "Action", "Transform" });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);
   std::string expected_opener_namespace_statement = "namespace Fullscore\n{\n   namespace Action\n   {\n      namespace Transform\n      {\n";
   ASSERT_EQ(expected_opener_namespace_statement, class_generator.namespaces_scope_opener(true));
}


TEST_F(ClassGeneratorTest, namespaces_scope_opener__without_namespaces_returns_an_empty_string)
{
   Blast::Cpp::Class cpp_class("Ascend");
   Blast::Cpp::ClassGenerator class_generator(cpp_class);
   ASSERT_EQ("", class_generator.namespaces_scope_opener(true));
}


TEST_F(ClassGeneratorTest,
   namespaces_scope_closer__returns_a_formatted_string_of_the_closer_namespace_statement_without_nested_indentations)
{
   Blast::Cpp::Class cpp_class("Ascend", { "Fullscore", "Action", "Transform" });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);
   std::string expected_closer_namespace_statement = "} // namespace Transform\n} // namespace Action\n} // namespace Fullscore\n";
   ASSERT_EQ(expected_closer_namespace_statement, class_generator.namespaces_scope_closer(false));
}


TEST_F(ClassGeneratorTest,
   namespaces_scope_closer__returns_a_formatted_string_of_the_closer_namespace_statement_with_nested_indentations)
{
   Blast::Cpp::Class cpp_class("Ascend", { "Fullscore", "Action", "Transform" });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);
   std::string expected_closer_namespace_statement = "      } // namespace Transform\n   } // namespace Action\n} // namespace Fullscore\n";
   ASSERT_EQ(expected_closer_namespace_statement, class_generator.namespaces_scope_closer(true));
}


TEST_F(ClassGeneratorTest, namespaces_scope_closer__can_optionally_remove_closer_comment)
{
   Blast::Cpp::Class cpp_class("Ascend", { "Fullscore", "Action", "Transform" });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);
   std::string expected_closer_namespace_statement = "      }\n   }\n}\n";
   ASSERT_EQ(expected_closer_namespace_statement, class_generator.namespaces_scope_closer(true, false));
}


TEST_F(ClassGeneratorTest, namespaces_scope_closer__without_namespaces_returns_an_empty_string)
{
   Blast::Cpp::Class cpp_class("Ascend");
   Blast::Cpp::ClassGenerator class_generator(cpp_class);
   ASSERT_EQ("", class_generator.namespaces_scope_closer(false));
}


TEST_F(ClassGeneratorTest,
   class_declaration_inheritence_list__returns_a_formatted_string_listing_the_inherited_classes_for_a_class_opener_statement)
{
   Blast::Cpp::Class cpp_class(
      "Ascend", {}, { { "Action", "\"ascend_action\"", "private" }, { "Scriptable<Ascend>", "", "protected" } }
   );
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::string expected_elements = " : private Action, protected Scriptable<Ascend>";
   ASSERT_EQ(expected_elements, class_generator.class_declaration_inheritence_list());
}


TEST_F(ClassGeneratorTest, class_declaration_opener__returns_a_formatted_string_of_the_classes_opener_statement)
{
   Blast::Cpp::Class cpp_class("Happiness");
   Blast::Cpp::ClassGenerator class_generator(cpp_class);
   std::string expected_class_opener_statement = "   class Happiness\n   {\n";
   ASSERT_EQ(expected_class_opener_statement, class_generator.class_declaration_opener(1));
}


TEST_F(ClassGeneratorTest, class_declaration_closer_returns_a_formatted_string_of_the_classes_closing_statemet)
{
   Blast::Cpp::Class cpp_class("Happiness");
   Blast::Cpp::ClassGenerator class_generator(cpp_class);
   std::string expected_closing_class_statement = "   };\n";
   ASSERT_EQ(expected_closing_class_statement, class_generator.class_declaration_closer(1));
}


TEST_F(ClassGeneratorTest, getter_ref_function_declarations__returns_the_expected_)
{
   // TODO
}


TEST_F(ClassGeneratorTest, __returns_a_reference_to_the_symbol_dependencies)
{
   // TODO
}


TEST_F(ClassGeneratorTest, constructor_declaration_elements__returns_the_expected_set_of_elements_in_a_declaration)
{
   std::vector<std::string> expected_elements = { "std::string name=\"[unnamed]\"", "type_t type=MAGE" };
   ASSERT_EQ(expected_elements, class_generator_fixture.constructor_declaration_elements());
}


TEST_F(ClassGeneratorTest, constructor_definition_elements__returns_the_expected_set_of_elements_in_a_definition)
{
   std::vector<std::string> expected_elements = { "std::string name", "type_t type" };
   ASSERT_EQ(expected_elements, class_generator_fixture.constructor_definition_elements());
}


TEST_F(ClassGeneratorTest, initialization_list_elements__when_properties_are_constructor_parameters__returns_variable_assigned_arguments)
{
   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "last_id", "0", true, false, false, false, false, false, false },
      { "int", "id", "last_id++", false, true, true, false, false, false, false },
      { "std::string", "name", "\"[unnamed]\"", false, true, true, false, false, true, false },
      { "type_t", "type", "MAGE", false, true, true, false, false, true, false },
   });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::vector<std::string> expected_elements = { "id(id)", "name(name)", "type(type)" };
   ASSERT_EQ(expected_elements, class_generator.initialization_list_elements());
}


TEST_F(ClassGeneratorTest, initialization_list_elements__when_properties_are_not_constructor_parameters__returns_initialization_value_assigned_elements)
{
   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "last_id", "0", true, false, false, false, false, false, false },
      { "int", "id", "last_id++", false, false, false, false, false, true, false },
      { "std::string", "name", "\"[unnamed]\"", false, false, true, false, false, true, false },
      { "type_t", "type", "MAGE", false, false, true, false, false, true, false },
   });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::vector<std::string> expected_elements = { "id(last_id++)", "name(\"[unnamed]\")", "type(MAGE)" };
   ASSERT_EQ(expected_elements, class_generator.initialization_list_elements());
}


TEST_F(ClassGeneratorTest, initialization_list_elements__does_not_include_static_members)
{
   // TODO
}


TEST_F(ClassGeneratorTest, class_declaration_opener_inheritence_elements__returns_a_list_of_formatted_inheritence_elements_for_the_class_declaration_opener)
{
   Blast::Cpp::Class cpp_class("Ascend", {}, { { "Action", "\"ascend_action\"", "private" }, { "Scriptable<Ascend>", "", "protected" } });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::vector<std::string> expected_elements = { "private Action", "protected Scriptable<Ascend>" };
   ASSERT_EQ(expected_elements, class_generator.class_declaration_opener_inheritence_elements());
}


TEST_F(ClassGeneratorTest,
   static_attribute_definition_elements__returns_the_expected_list_of_formatted_static_attribute_definitions)
{
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = {
      { "int" },
      { "float" },
   };

   Blast::Cpp::Class cpp_class("User", {}, {}, {
         //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter
         { "int", "next_id", "0", true, false, false, false, false, false, false },
         { "int", "id", "next_id++", false, false, true, false, false, false, false },
         { "float", "time_velocity", "13.0f", true, false, false, false, false, false, false },
      },
      {},
      symbol_dependencies
   );
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::vector<std::string> expected_elements = { "int User::next_id = 0;", "float User::time_velocity = 13.0f;" };
   ASSERT_EQ(expected_elements, class_generator.static_attribute_definition_elements());
}

TEST_F(ClassGeneratorTest,
   static_attribute_definition_elements__will_not_include_constexpr_attributes_even_though_they_are_static_by_default)
{
   // HERE
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = {
      { "int" },
      { "float" },
   };

   Blast::Cpp::Class cpp_class("User", {}, {}, {
         //std::string datatype, std::string variable_name, std::string initialization_value,
            //bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter
         { "int", "next_id", "0", true, false, false, false, false, false, false },
         { "int", "id", "next_id++", false, false, true, false, false, false, false },
         { "float", "time_velocity", "13.0f", true, false, false, false, false, false, false },
         { "float", "PI", "3.141592f", true, false, false, false, false, false, true }, // constexpr
      },
      {},
      symbol_dependencies
   );
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::vector<std::string> expected_elements = { "int User::next_id = 0;", "float User::time_velocity = 13.0f;" };
   ASSERT_EQ(expected_elements, class_generator.static_attribute_definition_elements());
}


TEST_F(ClassGeneratorTest, header_filename__returns_the_filename_for_the_header_of_the_class)
{
   std::string expected_header_filename = "User.hpp";
   ASSERT_EQ(expected_header_filename, class_generator_fixture.header_filename());
}


TEST_F(ClassGeneratorTest, source_filename__returns_the_filename_for_the_header_of_the_class)
{
   std::string expected_source_filename = "User.cpp";
   ASSERT_EQ(expected_source_filename, class_generator_fixture.source_filename());
}


TEST_F(ClassGeneratorTest, get_class_name_with_namespaces__will_return_the_class_name_prefixed_with_its_namespaces)
{
   Blast::Cpp::Class cpp_class("Ascend", { "Fullscore", "Action", "Transform" });
   Blast::Cpp::ClassGenerator cpp_class_generator(cpp_class);
   ASSERT_EQ("Fullscore::Action::Transform::Ascend", cpp_class_generator.get_class_name_with_namespaces());
}



TEST_F(ClassGeneratorTest, header_include_directive__returns_the_include_line_to_include_the_class_header_file)
{
   std::string expected_header_directive = "#include <ProjectName/User.hpp>";
   ASSERT_EQ(expected_header_directive, class_generator_fixture.header_include_directive());
}


TEST_F(ClassGeneratorTest, header_include_directive__on_a_class_with_no_namespaces_returns_the_expected_header_filename)
{
   Blast::Cpp::Class cpp_class("User");
   Blast::Cpp::ClassGenerator cpp_class_generator(cpp_class);

   std::string expected_header_directive = "#include <User.hpp>";
   ASSERT_EQ(expected_header_directive, cpp_class_generator.header_include_directive());
}


TEST_F(ClassGeneratorTest,
   dependency_include_directives__returns_a_list_of_directives_for_the_existing_dependencies_for_a_classes_properties)
{
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = {
      { "std::string", { "string" } },
      { "Blast::DiceRoller", { "Blast/DiceRoller.hpp" } },
   };

   Blast::Cpp::Class cpp_class("User", {}, {}, {
         { "std::string", "name", "\"[unnamed]\"", false, true, true, false, false, true, false },
         { "Blast::DiceRoller", "dice_roller", "{}", false, true, true, false, false, true, false },
      },
      {},
      symbol_dependencies
   );
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::string expected_dependency_directives = "#include <Blast/DiceRoller.hpp>\n#include <string>\n";
   ASSERT_EQ(expected_dependency_directives, class_generator.dependency_include_directives());
}


TEST_F(ClassGeneratorTest, dependency_include_directives__includes_the_list_of_dependencies_for_parent_classes)
{
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = {
      { "ActionBase", { "Fullscore/Action/ActionBase.hpp" } },
      { "Scriptable<Ascend>", { "Blast/Scriptable.hpp" } },
      { "Scriptable", { "Blast/Scriptable.hpp" } },
      { "Ascend", { "MyDomain/Ascend.hpp" } },
   };

   Blast::Cpp::Class cpp_class("Ascend", {}, { { "ActionBase" }, { "Scriptable<Ascend>" } }, {}, {}, symbol_dependencies);
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::string expected_dependency_directives = "#include <Blast/Scriptable.hpp>\n"
                                                "#include <Fullscore/Action/ActionBase.hpp>\n"
                                                "#include <MyDomain/Ascend.hpp>\n";
   ASSERT_EQ(expected_dependency_directives, class_generator.dependency_include_directives());
}


TEST_F(ClassGeneratorTest, dependency_include_directives__when_no_dependencies_are_required_returns_an_empty_string)
{
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = {
      { "int" },
      { "float" },
   };

   Blast::Cpp::Class cpp_class("User", {}, {}, {
         //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter
         { "int", "num_sides", "0", false, false, true, false, false, false, false },
         { "float", "radius", "6.0f", false, true, true, false, false, true, false },
      },
      {},
      symbol_dependencies
   );
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   ASSERT_EQ("", class_generator.dependency_include_directives());
}


TEST_F(ClassGeneratorTest,
   DISABLED__dependency_include_directives__when_a_symbol_dependency_is_not_defined_raises_an_exception)
   // test is fine, it's just undergoing a lot of development and changing frequently
{
   Blast::Cpp::Class cpp_class("User", {}, { { "SomeUndefinedParentClass" } }, {
         { "some_undefined_symbol", "foofoo", "\"foobar\"", false, false, true, false, false, false, false },
      }
   );
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::string expected_error_message = "When consolidating dependencies for:\n"
                                        "\n"
                                        "  User\n"
                                        "\n"
                                        "There are undefined symbols for datatypes [ \"SomeUndefinedParentClass\", "
                                        "\"some_undefined_symbol\",  ]";

   std::string expected_appended_error_message = "\n\nUser appears to be missing the following dependencies:\n"
                                                 "\n"
                                                 "  - SomeUndefinedParentClass\n"
                                                 "  - some_undefined_symbol\n"
                                                 "\n"
                                                 "\n"
                                               ;

   std::string full_error_message = expected_error_message + expected_appended_error_message;
   ASSERT_THROW_WITH_MESSAGE(class_generator.dependency_include_directives(), std::runtime_error, full_error_message);
}


TEST_F(ClassGeneratorTest, class_property_list__returns_the_expected_formatted_string_of_class_properties)
{
   std::string expected_property_list = "   static int last_id;\n   int id;\n   std::string name;\n   type_t type;\n";
   ASSERT_EQ(expected_property_list, class_generator_fixture.class_property_list(1));
}


TEST_F(ClassGeneratorTest, static_attribute_definitions__returns_a_string_formatted_with_the_expected_definitions)
{
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = {
      { "int" },
      { "float" },
   };

   Blast::Cpp::Class cpp_class("User", {}, {}, {
         //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter
         { "int", "next_id", "0", true, false, false, false, false, false, false },
         { "int", "id", "next_id++", false, false, true, false, false, false, false },
         { "float", "time_velocity", "13.0f", true, false, false, false, false, false, false },
      },
      {},
      symbol_dependencies
   );
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::string expected_property_list = "   int User::next_id = 0;\n\n\n   float User::time_velocity = 13.0f;\n\n\n";
   ASSERT_EQ(expected_property_list, class_generator.static_attribute_definitions(1));
}


TEST_F(ClassGeneratorTest,
   getter_function_declarations__when_the_function_is_static__will_not_include_the_const_qualifier)
{
   // Handled with other tests
}


TEST_F(ClassGeneratorTest,
   getter_function_declarations__returns_the_expected_formatted_string_for_properties_with_getter_functions)
{
   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "last_id", "0", true, false, true, false, false, false, false },
      { "int", "id", "last_id++", false, false, true, false, false, false, false },
      { "std::string", "name", "\"[unnamed]\"", false, true, false, false, false, true, false },
      { "type_t", "type", "MAGE", false, true, true, false, false, true, false },
   });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::string expected_declarations_list = "   static int get_last_id();\n   int get_id() const;\n   type_t get_type() const;\n";
   ASSERT_EQ(expected_declarations_list, class_generator.getter_function_declarations(1));
}


TEST_F(ClassGeneratorTest,
   getter_function_definitions__returns_the_expected_formatted_definitions_for_properties_with_getter_functions)
{
   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter
      { "int", "last_id", "0", true, false, true, false, false, false, false },
      { "int", "id", "last_id++", false, false, true, false, false, false, false },
      { "std::string", "name", "\"[unnamed]\"", false, true, false, false, false, true, false },
      { "type_t", "type", "MAGE", false, true, true, false, false, true, false },
   });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::string expected_definition_list = "int User::get_last_id()\n{\n   return last_id;\n}\n\n\n"
                                          "int User::get_id() const\n{\n   return id;\n}\n\n\n"
                                          "type_t User::get_type() const\n{\n   return type;\n}\n\n\n";
   ASSERT_EQ(expected_definition_list, class_generator.getter_function_definitions());
}


TEST_F(ClassGeneratorTest, getter_ref_function_declarations__returns_the_expected_formatted_string_for_properties_with_getter_ref_functions)
{
   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {
      //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_getter_ref, bool has_setter)
      { "int", "last_id", "0", true, false, true, false, true, false, false },
      { "int", "id", "last_id++", false, false, true, false, true, false, false },
      { "std::string", "name", "\"[unnamed]\"", false, true, false, false, false, true, false },
      { "type_t", "type", "MAGE", false, true, true, false, true, true, false },
   });
   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::string expected_declarations_list = "   static int &get_last_id_ref();\n   int &get_id_ref();\n   type_t &get_type_ref();\n";
   ASSERT_EQ(expected_declarations_list, class_generator.getter_ref_function_declarations(1));
}


TEST_F(ClassGeneratorTest, setter_function_declarations_returns_the_expected_formatted_declarations_for_properties_with_setter_functions)
{
   std::string expected_declarations_list = "   void set_name(std::string name);\n   void set_type(type_t type);\n";
   ASSERT_EQ(expected_declarations_list, class_generator_fixture.setter_function_declarations(1));
}


TEST_F(ClassGeneratorTest, setter_function_definitions__returns_the_expected_formatted_definitions_for_properties_with_setter_functions)
{
   std::string expected_definition_list = "void User::set_name(std::string name)\n{\n   this->name = name;\n}\n\n\nvoid User::set_type(type_t type)\n{\n   this->type = type;\n}\n\n\n";
   ASSERT_EQ(expected_definition_list, class_generator_fixture.setter_function_definitions(0));
}


TEST_F(ClassGeneratorTest, initialization_list__returns_the_expected_formatted_string)
{
   std::string expected_initialization_list = "   : id(last_id++)\n   , name(name)\n   , type(type)\n";
   ASSERT_EQ(expected_initialization_list, class_generator_fixture.initialization_list(1));
}


TEST_F(ClassGeneratorTest, constructor_declaration__returns_the_expected_string)
{
   std::string expected_constructor_declaration = "User(std::string name=\"[unnamed]\", type_t type=MAGE);\n";
   ASSERT_EQ(expected_constructor_declaration, class_generator_fixture.constructor_declaration());
}


TEST_F(ClassGeneratorTest, constructor_definition_returns_the_expected_string)
{
   std::string expected_constructor_definition = "User::User(std::string name, type_t type)\n   : id(last_id++)\n   , name(name)\n   , type(type)\n{\n}\n";
   ASSERT_EQ(expected_constructor_definition, class_generator_fixture.constructor_definition(0));
}


TEST_F(ClassGeneratorTest, destructor_declaration__returns_the_expected_string)
{
   std::string expected_destructor_declaration = "~User();\n";
   ASSERT_EQ(expected_destructor_declaration, class_generator_fixture.destructor_declaration());
}


TEST_F(ClassGeneratorTest,
   when_multiple_identical_dependencies_are_present__will_only_render_one_of_them)
{
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = {
      { "std::string", { "string" } },
      { "Blast::DiceRoller", { "Blast/DiceRoller.hpp" } },
   };

   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {}, {
      Blast::Cpp::Function("std::string", "unnamed_function",         {}, "return;", false, false, false, false, true),
      Blast::Cpp::Function("std::string", "another_unnamed_function", {}, "return;", false, false, false, true, false),
   }, symbol_dependencies);

   Blast::Cpp::ClassGenerator cpp_class_generator(cpp_class);
   std::string expected_dependency_directives = "#include <string>\n";
   ASSERT_EQ(expected_dependency_directives, cpp_class_generator.dependency_include_directives());
}


TEST_F(ClassGeneratorTest,
   function_body_dependency_include_directives__when_multiple_identical_dependencies_are_present__will_only_render_one_of_them)
{
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = {
      { "std::string", { "string" } },
      { "Blast::DiceRoller", { "Blast/DiceRoller.hpp" } },
   };

   std::vector<Blast::Cpp::SymbolDependencies> function_body_symbol_dependencies = {
      { "Blast::DiceRoller", { "Blast/DiceRoller.hpp" } },
      { "Blast::DiceRoller", { "Blast/DiceRoller.hpp" } },
   };

   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {}, {
      Blast::Cpp::Function("std::string", "unnamed_function",         {}, "return;", false, false, false, false, true),
      Blast::Cpp::Function("std::string", "another_unnamed_function", {}, "return;", false, false, false, true, false),
   }, symbol_dependencies, function_body_symbol_dependencies );

   // will need to use (to copy set to vector)
   //std::copy(input.begin(), input.end(), std::back_inserter(output));
   
   // HERE
   Blast::Cpp::ClassGenerator cpp_class_generator(cpp_class);
   std::string expected_dependency_directives = "#include <Blast/DiceRoller.hpp>";
   ASSERT_EQ(expected_dependency_directives, cpp_class_generator.function_body_dependency_include_directives());
}



TEST_F(ClassGeneratorTest, destructor_declaration__when_virtual_or_pure_virtual_functions_are_present_on_the_class__returns_the_expected_virtual_destructor_string)
{
   Blast::Cpp::Class cpp_class("User", { "ProjectName" }, {}, {}, {
      Blast::Cpp::Function("void", "unnamed_function",         {}, "return;", false, false, false, false, true),
      Blast::Cpp::Function("void", "another_unnamed_function", {}, "return;", false, false, false, true, false),
   });

   Blast::Cpp::ClassGenerator class_generator(cpp_class);

   std::string expected_destructor_declaration = "virtual ~User();\n";
   ASSERT_EQ(expected_destructor_declaration, class_generator.destructor_declaration());
}


TEST_F(ClassGeneratorTest, destructor_definition_returns_the_expected_string)
{
   std::string expected_destructor_definition = "User::~User()\n{\n}\n";
   ASSERT_EQ(expected_destructor_definition, class_generator_fixture.destructor_definition());
}


TEST_F(ClassGeneratorTest, project_source_filepath__returns_a_string_of_the_location_of_the_source_file_relative_to_the_project_root)
{
   std::string expected_project_source_filepath = "src/ProjectName/User.cpp";
   ASSERT_EQ(expected_project_source_filepath, class_generator_fixture.project_source_filepath());
}


TEST_F(ClassGeneratorTest, project_header_filepath__returns_a_string_of_the_location_of_the_header_file_relative_to_the_project_root)
{
   std::string expected_project_header_filepath = "include/ProjectName/User.hpp";
   ASSERT_EQ(expected_project_header_filepath, class_generator_fixture.project_header_filepath());
}


