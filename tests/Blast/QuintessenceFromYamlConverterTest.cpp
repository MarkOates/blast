
#include <gtest/gtest.h>

#include <Blast/QuintessenceFromYamlConverter.hpp>

TEST(QuintessenceFromYamlConverterTest, run__returns_the_expected_response)
{
   Blast::QuintessenceFromYamlConverter program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}

