
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


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest, parse__when_items_is_not_present__throws_an_error)
{
   std::string yaml_content = "name: \"FooBar\"\neyetems: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   EXPECT_THROW_WITH_MESSAGE(
      enum_class_parser.parse(),
      std::runtime_error,
      "[Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_presence_of_key]: error: expecting to "
         "find node \"items\" but it is not present."
   );
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest, EmptyVector)
{
  std::vector<std::string> empty_vector;
  EXPECT_TRUE(Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_elements_are_unique(empty_vector));
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest, StringVectorWithUniqueElements)
{
  std::vector<std::string> vector = {"apple", "banana", "cherry", "date"};
  EXPECT_TRUE(Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_elements_are_unique(vector));
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest, StringVectorWithDuplicateElements)
{
  std::vector<std::string> vector = {"apple", "banana", "cherry", "banana"};
  EXPECT_FALSE(Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_elements_are_unique(vector));
}


