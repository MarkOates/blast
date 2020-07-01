
#include <gtest/gtest.h>

#include <Blast/TaoTeChingQuoteGenerator.hpp>

TEST(Blast_TaoTeChingQuoteGeneratorTest, can_be_created_without_blowing_up)
{
   Blast::TaoTeChingQuoteGenerator tao_te_ching_quote_generator;
}

TEST(Blast_TaoTeChingQuoteGeneratorTest, pick_quote__returns_a_quote_from_the_list)
{
   Blast::TaoTeChingQuoteGenerator tao_te_ching_quote_generator;
   std::string expected_quote = "Hello World!";
   ASSERT_EQ(expected_quote, tao_te_ching_quote_generator.pick_quote());
}

TEST(Blast_TaoTeChingQuoteGeneratorTest, pick_quote__with_an_empty_list__returns_an_empty_string)
{
   std::vector<std::string> empty_list_of_quotes = {};
   Blast::TaoTeChingQuoteGenerator tao_te_ching_quote_generator(empty_list_of_quotes);
   std::string expected_empty_string = "";
   ASSERT_EQ(expected_empty_string, tao_te_ching_quote_generator.pick_quote());
}
