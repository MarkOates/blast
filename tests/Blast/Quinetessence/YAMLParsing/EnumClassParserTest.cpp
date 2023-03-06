
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
   std::string yaml_content = "name: \"FooBar\"\nstart_from: 42\ntype: uint32_t\nenumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   Blast::Cpp::EnumClass enum_class = enum_class_parser.parse();

   EXPECT_EQ("FooBar", enum_class.get_name());
   EXPECT_THAT(enum_class.get_enumerators(), ::testing::ElementsAre("FOO", "FOE", "FUM"));
   EXPECT_EQ("uint32_t", enum_class.get_type());
   EXPECT_EQ(42, enum_class.get_start_from());
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest,
   parse__with_a_scope_key_defined__will_set_the_scope)
{
   std::string yaml_content = "name: \"FooBar\"\nscope: protected\nenumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   Blast::Cpp::EnumClass enum_class = enum_class_parser.parse();

   EXPECT_EQ("protected", enum_class.get_scope());
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest,
   parse__when_no_scope_key_is_defined__the_scope_will_be_set_to_the_expected_default)
{
   std::string yaml_content = "name: \"FooBar\"\nenumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   Blast::Cpp::EnumClass enum_class = enum_class_parser.parse();

   EXPECT_EQ(Blast::Cpp::EnumClass::DEFAULT_SCOPE, enum_class.get_scope());
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest,
   parse__with_a_name_key_defined__will_set_the_name__and__will_set_is_class_as_false)
{
   std::string yaml_content = "name: \"FooBar\"\nenumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   Blast::Cpp::EnumClass enum_class = enum_class_parser.parse();

   EXPECT_EQ("FooBar", enum_class.get_name());
   EXPECT_EQ(false, enum_class.get_is_class());
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest,
   parse__with_a_class_key_defined__will_set_the_name__and__will_set_is_class_as_true)
{
   std::string yaml_content = "class: \"FooBar\"\nenumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   Blast::Cpp::EnumClass enum_class = enum_class_parser.parse();

   EXPECT_EQ("FooBar", enum_class.get_name());
   EXPECT_EQ(true, enum_class.get_is_class());
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest,
   parse__when_both_a_name_key_and_a_class_key_are_defined__will_throw_an_error)
{
   std::string yaml_content = "class: \"FooBar\"\nname: \"FooBar\"\nenumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   EXPECT_THROW_WITH_MESSAGE(
      enum_class_parser.parse(),
      std::runtime_error,
      "[Blast::Quinetessence::YAMLParsing::EnumClassParser::parse]: error: An enum cannot have both "
         "the \"name\" and \"class\" present. It must be one or neither."
   );
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest, parse__when_a_class_is_not_present__does_not_throw_an_error)
{
   std::string yaml_content = "nayme: \"FooBar\"\nenumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   enum_class_parser.parse();
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest,
   parse__when_a_start_from_is_not_present__does_not_throw_an_error)
{
   std::string yaml_content = "enumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   enum_class_parser.parse();
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest, parse__when_a_type_is_not_present__does_not_throw_an_error)
{
   std::string yaml_content = "enumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   enum_class_parser.parse();
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest, parse__when_a_scope_is_not_present__does_not_throw_an_error)
{
   std::string yaml_content = "enumerators: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   enum_class_parser.parse();
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest, parse__when_enumerators_are_not_present__throws_an_error)
{
   std::string yaml_content = "class: \"FooBar\"\neyetems: [ FOO, FOE, FUM ]\n";
   YAML::Node node = YAML::Load(yaml_content);
   Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(node);
   EXPECT_THROW_WITH_MESSAGE(
      enum_class_parser.parse(),
      std::runtime_error,
      "[Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_presence_of_key]: error: expecting to "
         "find node \"enumerators\" but it is not present."
   );
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest,
   validate_elements_are_unique__will_return_true_on_an_empty_vector)
{
  std::vector<std::string> empty_vector;
  EXPECT_EQ(true, Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_elements_are_unique(empty_vector));
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest,
   validate_elements_are_unique__with_a_vector_with_unique_elements__will_return_true)
{
  std::vector<std::string> vector = {"apple", "banana", "cherry", "date"};
  EXPECT_EQ(true, Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_elements_are_unique(vector));
}


TEST(Blast_Quinetessence_YAMLParsing_EnumClassParserTest,
   validate_elements_are_unique__with_a_vector_that_does_not_contain_unique_elements__will_return_false)
{
  std::vector<std::string> vector = {"apple", "banana", "cherry", "banana"};
  EXPECT_EQ(false, Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_elements_are_unique(vector));
}


