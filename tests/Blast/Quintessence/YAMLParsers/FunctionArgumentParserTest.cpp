
#include <gtest/gtest.h>

#include <Blast/Quintessence/YAMLParsers/FunctionArgumentParser.hpp>


TEST(Blast_Quintessence_YAMLParsers_FunctionArgumentParserTest, can_be_created_without_blowing_up)
{
   Blast::Quintessence::YAMLParsers::FunctionArgumentParser function_argument_parser;
}

TEST(Blast_Quintessence_YAMLParsers_FunctionArgumentParserTest,
   parse__will_return_object_with_the_expected_values)
{
   std::string yaml_content = "name: \"FooBar\"\nstart_from: 42\ntype: uint32_t\nenumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);

   Blast::Quintessence::YAMLParsers::FunctionArgumentParser function_argument_parser(node);
   Blast::Cpp::FunctionArgument function_argument = function_argument_parser.parse();

   // TODO: Validate parsed object
   //EXPECT_EQ("FooBar", function_argument_parser.get_name());
   //EXPECT_THAT(function_argument_parser.get_enumerators(), ::testing::ElementsAre("FOO", "FOE", "FUM"));
   //EXPECT_EQ("uint32_t", function_argument_parser.get_type());
   //EXPECT_EQ(42, function_argument_parser.get_start_from());
}


