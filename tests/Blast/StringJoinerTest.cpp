

#include <gtest/gtest.h>

#include <Blast/StringJoiner.hpp>


TEST(Blast__StringJoinerTest, can_be_created)
{
   Blast::StringJoiner string_joiner;
}


TEST(Blast__StringJoinerTest, when_created_without_arguments_has_the_expected_values)
{
   std::vector<std::string> words = { "Tony", "John", "Phil", "Henry" };
   Blast::StringJoiner string_joiner(words, ", ");

   std::string expected_string = "Tony, John, Phil, Henry";

   ASSERT_EQ(expected_string, string_joiner.join());
}


