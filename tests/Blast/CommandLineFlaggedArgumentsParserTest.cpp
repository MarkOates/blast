

#include <gtest/gtest.h>

#include <Blast/CommandLineFlaggedArgumentsParser.hpp>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


class CommandLineFlaggedArgumentsParserTest : public ::testing::Test
{
protected:
   static std::vector<std::string> args_fixture;

   virtual void SetUp()
   {
      args_fixture = {
         "-c", "ClassName",
         "-i", "InterfaceName",
         "-f", "folder_name",
         "-n", "ModuleName",
         "-a", "named_arg_1", "named_arg_2:'default_value'",
         "-m", "method_name", "method_named_arg:'another_default'",
         "-m", "another_method_name", "another_method_named_arg:'another_default'",
      };
   }
};


std::vector<std::string> CommandLineFlaggedArgumentsParserTest::args_fixture = {};


TEST_F(CommandLineFlaggedArgumentsParserTest, can_be_created)
{
   Blast::CommandLineFlaggedArgumentsParser parser(args_fixture);
}


TEST_F(CommandLineFlaggedArgumentsParserTest, with_constructor_1__can_be_created)
{
   Blast::CommandLineFlaggedArgumentsParser parser(args_fixture({}));
}


TEST_F(CommandLineFlaggedArgumentsParserTest, with_constructor_2__can_be_created)
{
   Blast::CommandLineFlaggedArgumentsParser parser(args_fixture(0, nullptr));
}


DISABLE_TEST_F(CommandLineFlaggedArgumentsParserTest, with_constructor_2__properly_parses_the_passed_arguments)
{
   // UNTESTED
}


TEST_F(CommandLineFlaggedArgumentsParserTest, get_flagged_args__with_a_given_flag_returns_the_expected_passed_arguments)
{
   Blast::CommandLineFlaggedArgumentsParser parser(args_fixture);

   std::vector<std::vector<std::string>> expected_results = { { "named_arg_1", "named_arg_2:'default_value'" } };
   std::vector<std::vector<std::string>> returned_results = parser.get_flagged_args("-a");

   ASSERT_EQ(expected_results, returned_results);
}


TEST_F(CommandLineFlaggedArgumentsParserTest, get_flagged_args__when_multiple_instances_of_a_flag_are_present__returns_the_expected_passed_arguments)
{
   Blast::CommandLineFlaggedArgumentsParser parser(args_fixture);

   std::vector<std::vector<std::string>> expected_results = {
      { "method_name", "method_named_arg:'another_default'" },
      { "another_method_name", "another_method_named_arg:'another_default'" },
   };
   std::vector<std::vector<std::string>> returned_results = parser.get_flagged_args("-m");

   ASSERT_EQ(expected_results, returned_results);
}


TEST_F(CommandLineFlaggedArgumentsParserTest, get_flagged_args__with_a_flag_that_is_not_present_returns_empty_results)
{
   Blast::CommandLineFlaggedArgumentsParser parser(args_fixture);

   std::vector<std::vector<std::string>> expected_results = { };
   std::vector<std::vector<std::string>> returned_results = parser.get_flagged_args("-x");

   ASSERT_EQ(expected_results, returned_results);
}


TEST_F(CommandLineFlaggedArgumentsParserTest, has_flag__raises_an_exception_if_the_passed_flag_does_not_match_the_flag_format)
{
   Blast::CommandLineFlaggedArgumentsParser parser(args_fixture);

   std::string expected_error_message = "[CommandLineFlaggedArgumentsParser::has_flag] error: \"not-a-flag\" is not " \
      "a valid formatted flag; It must start with '-' character.";

   ASSERT_THROW_WITH_MESSAGE(parser.has_flag("not-a-flag"), std::runtime_error, expected_error_message)
}


TEST_F(CommandLineFlaggedArgumentsParserTest, has_flag__returns_true_if_a_flag_is_present)
{
   Blast::CommandLineFlaggedArgumentsParser parser(args_fixture);

   ASSERT_TRUE(parser.has_flag("-n"));
}


TEST_F(CommandLineFlaggedArgumentsParserTest, has_flag__returns_false_if_a_flag_is_present)
{
   Blast::CommandLineFlaggedArgumentsParser parser(args_fixture);

   ASSERT_FALSE(parser.has_flag("-x"));
}


