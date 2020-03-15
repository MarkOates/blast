
#include <gtest/gtest.h>

#include <Blast/Inflector.hpp>

TEST(Blast_InflectorTest, can_be_created_without_blowing_up)
{
   Blast::Inflector inflector;
}

TEST(Blast_InflectorTest, run__returns_the_expected_response)
{
   Blast::Inflector inflector;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, inflector.run());
}
