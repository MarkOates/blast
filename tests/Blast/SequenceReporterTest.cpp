
#include <gtest/gtest.h>

#include <Blast/SequenceReporter.hpp>

TEST(Blast__SequenceReporterTest, run__returns_the_expected_response)
{
   Blast::SequenceReporter program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
