
#include <gtest/gtest.h>

#include <Blast/RegexMatcher.hpp>

TEST(Blast_RegexMatcherTest, can_be_created_without_blowing_up)
{
   Blast::RegexMatcher regex_matcher;
}

TEST(Blast_RegexMatcherTest, get_match_info__returns_a_list_of_matches__test_1)
{
   Blast::RegexMatcher regex_matcher;
   std::vector<std::pair<int, int>> expected_matches = {};
   std::vector<std::pair<int, int>> actual_matches = regex_matcher.get_match_info();

   EXPECT_EQ(expected_matches, actual_matches);
}
