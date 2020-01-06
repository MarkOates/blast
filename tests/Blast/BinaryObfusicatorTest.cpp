
#include <gtest/gtest.h>

#include <Blast/BinaryObfusicator.hpp>

TEST(Blast_BinaryObfusicatorTest, can_be_created_without_blowing_up)
{
   Blast::BinaryObfusicator binary_obfusicator;
}

TEST(Blast_BinaryObfusicatorTest, run__returns_the_expected_response)
{
   Blast::BinaryObfusicator binary_obfusicator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, binary_obfusicator.run());
}
