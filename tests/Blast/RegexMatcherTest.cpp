
#include <gtest/gtest.h>

#include <Blast/RegexMatcher.hpp>

TEST(Blast_RegexMatcherTest, can_be_created_without_blowing_up)
{
   Blast::RegexMatcher regex_matcher;
}


TEST(Blast_RegexMatcherTest, get_match_info__returns_a_list_of_matches__test_1)
{
   Blast::RegexMatcher regex_matcher("Hello World!", "World");
   std::vector<std::pair<int, int>> expected_matches = { { 6, 5 } };
   std::vector<std::pair<int, int>> actual_matches = regex_matcher.get_match_info();

   EXPECT_EQ(expected_matches, actual_matches);
}


TEST(Blast_RegexMatcherTest, get_match_info__returns_a_list_of_matches__test_2)
{
   Blast::RegexMatcher regex_matcher("Hello World!", "o");
   std::vector<std::pair<int, int>> expected_matches = { { 4, 1 }, { 7, 1 } };
   std::vector<std::pair<int, int>> actual_matches = regex_matcher.get_match_info();

   EXPECT_EQ(expected_matches, actual_matches);
}


TEST(Blast_RegexMatcherTest, get_match_info__incorporates_options_passed_during_construction)
{
   Blast::RegexMatcher regex_matcher("Hello World!", "world", { std::regex::icase });
   std::vector<std::pair<int, int>> expected_matches = { { 6, 5 } };
   std::vector<std::pair<int, int>> actual_matches = regex_matcher.get_match_info();

   EXPECT_EQ(expected_matches, actual_matches);
}


TEST(DISABLED_Blast_RegexMatcherTest, get_match_info__only_supports_icase_option)
{
   // This feature has incomplete implementation
}


