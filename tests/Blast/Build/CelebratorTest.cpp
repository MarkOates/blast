
#include <gtest/gtest.h>

#include <Blast/Build/Celebrator.hpp>

TEST(Blast_Build_CelebratorTest, can_be_created_without_blowing_up)
{
   Blast::Build::Celebrator celebrator;
}

TEST(Blast_Build_CelebratorTest, run__returns_the_expected_response)
{
   Blast::Build::Celebrator celebrator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, celebrator.generate_output_banner());
}
