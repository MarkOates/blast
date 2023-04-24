
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Blast/Quintessence/YAMLParsers/FunctionArgumentParser.hpp>


TEST(Blast_Quintessence_YAMLParsers_FunctionArgumentParserTest, can_be_created_without_blowing_up)
{
   Blast::Quintessence::YAMLParsers::FunctionArgumentParser function_argument_parser;
}


TEST(Blast_Quintessence_YAMLParsers_FunctionArgumentParserTest,
   parse__will_return_object_with_the_expected_values)
{
   std::string yaml_content = "name: \"foo_bar\"\n"
                              "type: uint32_t\n"
                              "default_argument: 42\n"
                              "default_argument_dependency_symbols: [ foo, foe, fum ]\n"
                              ;
   YAML::Node node = YAML::Load(yaml_content);

   Blast::Quintessence::YAMLParsers::FunctionArgumentParser function_argument_parser(node);
   Blast::Cpp::FunctionArgument function_argument = function_argument_parser.parse();
   std::vector<std::string> expected_default_value_dependency_symbols = { "foo", "foe", "fum" };

   EXPECT_EQ("foo_bar", function_argument.get_name());
   EXPECT_EQ("uint32_t", function_argument.get_type());
   EXPECT_EQ("42", function_argument.get_default_value());
   EXPECT_EQ(
      function_argument.get_default_value_dependency_symbols(),
      expected_default_value_dependency_symbols
   );
}


TEST(Blast_Quintessence_YAMLParsers_FunctionArgumentParserTest,
   consolidate_default_value_dependency_symbols__will_return_a_consolidated_list_of_dependency_symbols_from_all_of_the\
function_arguments)
{
   std::vector<Blast::Cpp::FunctionArgument> function_arguments = {
      Blast::Cpp::FunctionArgument("", "", "", { "foo", "bar", "baz" }),
      Blast::Cpp::FunctionArgument("", "", "", { "baz", "biz" }),
      Blast::Cpp::FunctionArgument("", "", "", { "basil", "bonk", "buzz" }),
   };

   std::vector<std::string> expected_consolidated_default_value_dependency_symbols = {
      "foo", "bar", "baz", "biz", "basil", "bonk", "buzz"
   };

   std::vector<std::string> actual_consolidated_default_value_dependency_symbols =
      Blast::Quintessence::YAMLParsers::FunctionArgumentParser::consolidate_default_value_dependency_symbols(
         function_arguments
      );

   EXPECT_THAT(
      actual_consolidated_default_value_dependency_symbols,
      ::testing::UnorderedElementsAreArray(expected_consolidated_default_value_dependency_symbols)
   );
}


TEST(Blast_Quintessence_YAMLParsers_FunctionArgumentParserTest,
   consolidate_default_value_dependency_symbols__when_no_default_value_dependency_symbols_are_present__will_be_fine)
{
   std::vector<Blast::Cpp::FunctionArgument> function_arguments = {
      Blast::Cpp::FunctionArgument("", "", "", {}),
      Blast::Cpp::FunctionArgument("", "", "", {}),
      Blast::Cpp::FunctionArgument("", "", "", {}),
   };

   std::vector<std::string> expected_consolidated_default_value_dependency_symbols = {};

   std::vector<std::string> actual_consolidated_default_value_dependency_symbols =
      Blast::Quintessence::YAMLParsers::FunctionArgumentParser::consolidate_default_value_dependency_symbols(
         function_arguments
      );

   EXPECT_THAT(
      actual_consolidated_default_value_dependency_symbols,
      ::testing::UnorderedElementsAreArray(expected_consolidated_default_value_dependency_symbols)
   );
}


