
#include <gtest/gtest.h>

#include <Blast/YamlCppValidators.hpp>


TEST(Blast_YamlCppValidatorTest, can_be_created_without_blowing_up)
{
   Blast::YamlCppValidators yaml_cpp_validators;
}


TEST(Blast_YamlCppValidatorTest, validate_elements_are_unique__will_return_true_on_an_empty_vector)
{
   std::vector<std::string> empty_vector;
   EXPECT_EQ(true, Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_elements_are_unique(empty_vector));
}


TEST(Blast_YamlCppValidatorTest, validate_elements_are_unique__with_a_vector_with_unique_elements__will_return_true)
{
   std::vector<std::string> vector = {"apple", "banana", "cherry", "date"};
   EXPECT_EQ(true, Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_elements_are_unique(vector));
}


TEST(Blast_YamlCppValidatorTest,
   validate_elements_are_unique__with_a_vector_that_does_not_contain_unique_elements__will_return_false)
{
   std::vector<std::string> vector = {"apple", "banana", "cherry", "banana"};
   EXPECT_EQ(false, Blast::Quinetessence::YAMLParsing::EnumClassParser::validate_elements_are_unique(vector));
}


