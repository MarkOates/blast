
#include <gtest/gtest.h>

#include <Blast/Project/ProgramLister.hpp>

TEST(Blast_Project_ProgramListerTest, can_be_created_without_blowing_up)
{
   Blast::Project::ProgramLister program_lister;
}

TEST(Blast_Project_ProgramListerTest, run__returns_the_expected_response)
{
   Blast::Project::ProgramLister program_lister;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_lister.run());
}
