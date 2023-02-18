
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Blast/Quinetessence/YAMLParsing/EnumClassParser.hpp>

#include <Blast/Testing/ErrorAssertions.hpp>


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest, can_be_created_without_blowing_up)
{
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser;
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest,
   parse__will_return_an_enum_class_object_with_the_expected_values)
{
   std::string yaml_content = "name: \"FooBar\"\nitems: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   Blast::Cpp::EnumClass enum_class = enum_class_parser.parse();

   EXPECT_EQ("FooBar", enum_class.get_enum_name());
   EXPECT_THAT(enum_class.get_elements(), ::testing::ElementsAre("FOO", "FOE", "FUM"));
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest, parse__when_a_name_is_not_present__throws_an_error)
{
   std::string yaml_content = "nayme: \"FooBar\"\nitems: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   EXPECT_THROW_WITH_MESSAGE(
      enum_class_parser.parse(),
      std::runtime_error,
      "[Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_presence_of_key]: error: expecting to "
         "find node \"name\" but it is not present."
   );
}


