
#include <gtest/gtest.h>

#include <Blast/TaoTeChingQuoteGenerator.hpp>

TEST(Blast_TaoTeChingQuoteGeneratorTest, can_be_created_without_blowing_up)
{
   Blast::TaoTeChingQuoteGenerator tao_te_ching_quote_generator;
}

TEST(Blast_TaoTeChingQuoteGeneratorTest, pluck_quote__returns_a_quote_from_the_list)
{
   Blast::TaoTeChingQuoteGenerator tao_te_ching_quote_generator;
   std::string expected_quote = "Hello World!";
   EXPECT_EQ(expected_quote, tao_te_ching_quote_generator.pluck_quote());
}
