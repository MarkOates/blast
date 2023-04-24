
#include <gtest/gtest.h>

#include <Blast/Quintessence/YAMLParsers/FunctionArgumentParser.hpp>


TEST(Blast_Quintessence_YAMLParsers_FunctionArgumentParserTest, can_be_created_without_blowing_up)
{
   Blast::Quintessence::YAMLParsers::FunctionArgumentParser function_argument_parser;
}


TEST(Blast_Quintessence_YAMLParsers_FunctionArgumentParserTest,
   parse__will_return_object_with_the_expected_values)
{
   std::string yaml_content = "name: \"foo_bar\"\n"
                              "default_argument: 42\n"
                              "type: uint32_t\n"
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


