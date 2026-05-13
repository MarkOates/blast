
#include <gtest/gtest.h>

#include <Blast/YAMLValidator.hpp>


TEST(Blast_YAMLValidatorTest, can_be_created_without_blowing_up)
{
   Blast::YAMLValidator yaml_cpp_validator;
}


TEST(Blast_YAMLValidatorTest, validate_elements_are_unique__will_return_true_on_an_empty_vector)
{
   std::vector<std::string> empty_vector;
   EXPECT_EQ(true, Blast::YAMLValidator::validate_elements_are_unique(empty_vector));
}


TEST(Blast_YAMLValidatorTest, validate_elements_are_unique__with_a_vector_with_unique_elements__will_return_true)
{
   std::vector<std::string> vector = {"apple", "banana", "cherry", "date"};
   EXPECT_EQ(true, Blast::YAMLValidator::validate_elements_are_unique(vector));
}


TEST(Blast_YAMLValidatorTest,
   validate_elements_are_unique__with_a_vector_that_does_not_contain_unique_elements__will_return_false)
{
   std::vector<std::string> vector = {"apple", "banana", "cherry", "banana"};
   EXPECT_EQ(false, Blast::YAMLValidator::validate_elements_are_unique(vector));
}


TEST(Blast_YAMLValidatorTest,
   validate_node_has_unsigned_int_value__will_return_true_if_the_node_contains_a_positive_integer)
{
   std::vector<std::string> test_data = { "1234", "1", "999999", "0" };
   // TODO: Test on other datatypes (float, bool, etc)

   for (auto &test_data_item : test_data)
   {
      YAML::Node node;
      node["key"] = test_data_item;
      EXPECT_EQ(true, Blast::YAMLValidator::validate_node_has_unsigned_int_value(node, "key"));
   }
}


TEST(Blast_YAMLValidatorTest,
   validate_node_has_unsigned_int_value__will_return_false_if_the_node_does_not_contain_an_unsigned_integer)
{
   std::vector<std::string> test_data = { "-1234", "-1", "-999999", "012", "-0", "&abier", " wohoasd", " ", "    \n" };
   // TODO: Test on other datatypes (float, bool, etc)

   for (auto &test_data_item : test_data)
   {
      YAML::Node node;
      node["key"] = test_data_item;
      EXPECT_EQ(false, Blast::YAMLValidator::validate_node_has_unsigned_int_value(node, "key"));
   }
}


TEST(Blast_YAMLValidatorTest,
   extract_sequence_as_string_array__will_return_the_sequence_as_a_vector_of_strings)
{
   YAML::Node node = YAML::Load("[foo, bar, baz]");
   // TODO: This tests
   std::vector<std::string> expected_extracted_data = {
      "foo",
      "bar",
      "baz",
   };
   std::vector<std::string> actual_extracted_data =
      Blast::YAMLValidator::extract_sequence_as_string_array(node);

   EXPECT_EQ(expected_extracted_data, actual_extracted_data);
}


// Gemini:


TEST(Blast_YAMLValidatorTest, 
   validate_presence_of_only_one_of_mulitple_possible_keys__with_exactly_one_key_present__will_return_true_with_the_found_key)
{
   YAML::Node node = YAML::Load("name: 'Hubert'\nage: 42\ncolor: 'blue'");
   std::vector<std::string> keys_to_check = { "location", "age", "height" };

   std::pair<bool, std::string> expected_result = { true, "age" };
   std::pair<bool, std::string> actual_result = 
      Blast::YAMLValidator::validate_presence_of_only_one_of_mulitple_possible_keys(node, keys_to_check);

   EXPECT_EQ(expected_result, actual_result);
}


TEST(Blast_YAMLValidatorTest, 
   validate_presence_of_only_one_of_mulitple_possible_keys__with_no_keys_present__returns_false)
{
   YAML::Node node = YAML::Load("name: 'Hubert'\ncolor: 'blue'");
   std::vector<std::string> keys_to_check = { "location", "height" };

   // We set throw_on_error to false so it returns the pair instead of throwing
   std::pair<bool, std::string> actual_result = 
      Blast::YAMLValidator::validate_presence_of_only_one_of_mulitple_possible_keys(node, keys_to_check, false);

   EXPECT_FALSE(actual_result.first);
}


TEST(Blast_YAMLValidatorTest, 
   validate_presence_of_only_one_of_mulitple_possible_keys__with_more_than_one_key_present__returns_false)
{
   YAML::Node node = YAML::Load("name: 'Hubert'\nage: 42\nheight: 180");
   std::vector<std::string> keys_to_check = { "name", "age", "height" };

   std::pair<bool, std::string> actual_result = 
      Blast::YAMLValidator::validate_presence_of_only_one_of_mulitple_possible_keys(node, keys_to_check, false);

   EXPECT_FALSE(actual_result.first);
}


TEST(Blast_YAMLValidatorTest, 
   validate_presence_of_only_one_of_mulitple_possible_keys__when_throw_on_error_is_true__and_keys_are_not_valid__throws_an_exception)
{
   YAML::Node node = YAML::Load("name: 'Hubert'\nage: 42");
   std::vector<std::string> keys_to_check = { "name", "age" }; // Two keys present, should trigger error

   EXPECT_THROW({
      Blast::YAMLValidator::validate_presence_of_only_one_of_mulitple_possible_keys(node, keys_to_check, true);
   }, std::runtime_error);
}

