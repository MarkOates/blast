
#include <gtest/gtest.h>

#include <Blast/Build/Celebrator.hpp>

TEST(Blast_Build_CelebratorTest, can_be_created_without_blowing_up)
{
   Blast::Build::Celebrator celebrator;
}

TEST(Blast_Build_CelebratorTest, run__outputs_a_string_of_the_expected_default_length)
{
   Blast::Build::Celebrator celebrator;
   EXPECT_EQ(80, celebrator.generate_full_width_output_banner("Hello World!").size());
}

TEST(Blast_Build_CelebratorTest, run__outputs_strings_of_varying_lengths)
{
   std::vector<int> lengths_to_attempt = { 30, 60, 83, 521 };
   for (auto &length_to_attempt : lengths_to_attempt)
   {
      Blast::Build::Celebrator celebrator;
      EXPECT_EQ(length_to_attempt, celebrator.generate_full_width_output_banner("Hello World!", length_to_attempt).size());
   }
}

TEST(Blast_Build_CelebratorTest, run__returns_the_expected_response)
{
   Blast::Build::Celebrator celebrator;
   std::string message = "Hello World!";
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, celebrator.generate_full_width_output_banner(message));
}

