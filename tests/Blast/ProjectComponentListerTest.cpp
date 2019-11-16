
#include <gtest/gtest.h>

#include <Blast/ProjectComponentLister.hpp>

TEST(Blast_ProjectComponentListerTest, run__returns_the_expected_response)
{
   Blast::ProjectComponentLister program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
