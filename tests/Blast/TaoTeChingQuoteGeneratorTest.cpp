
#include <gtest/gtest.h>

#include <Blast/TaoTeChingQuoteGenerator.hpp>

#include <gmock/gmock.h>
using ::testing::AnyOfArray;

#include <gmock/gmock.h>
using ::testing::IsSupersetOf;

TEST(Blast_TaoTeChingQuoteGeneratorTest, can_be_created_without_blowing_up)
{
   Blast::TaoTeChingQuoteGenerator tao_te_ching_quote_generator;
}

TEST(Blast_TaoTeChingQuoteGeneratorTest, pick_quote__returns_a_quote_from_the_list)
{
   std::vector<std::string> test_quotes = { "Hello, Test quote." };
   Blast::TaoTeChingQuoteGenerator tao_te_ching_quote_generator(test_quotes);
   std::string expected_quote = "Hello, Test quote.";
   ASSERT_EQ(expected_quote, tao_te_ching_quote_generator.pick_quote());
}

TEST(Blast_TaoTeChingQuoteGeneratorTest, pick_quote__with_an_empty_list__returns_an_empty_string)
{
   std::vector<std::string> empty_list_of_quotes = {};
   Blast::TaoTeChingQuoteGenerator tao_te_ching_quote_generator(empty_list_of_quotes);
   std::string expected_empty_string = "";
   ASSERT_EQ(expected_empty_string, tao_te_ching_quote_generator.pick_quote());
}

TEST(Blast_TaoTeChingQuoteGeneratorTest, pick_quote__will_select_a_random_quote_from_the_list_of_provided_quotes)
{
   std::vector<std::string> list_of_test_quotes = {
      "Darkness within darkness. The gateway to all understanding.",
      "Accomplish the great task by a series of small acts.",
      "The greatest art seems unsophisticated, the greatest love seems indifferent, the greatest wisdom seems childish.",
   };
   Blast::TaoTeChingQuoteGenerator tao_te_ching_quote_generator(list_of_test_quotes);

   for (unsigned i=0; i<list_of_test_quotes.size(); i++)
   {
      std::string returned_quote = tao_te_ching_quote_generator.pick_quote();
      EXPECT_THAT(returned_quote, AnyOfArray(list_of_test_quotes));
   }
}

TEST(DISABLED_Blast_TaoTeChingQuoteGeneratorTest,
   pick_quote__will_exhaust_random_quotes_from_the_list_of_provided_quotes)
{
   // tooo
}
