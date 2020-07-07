
#include <gtest/gtest.h>

#include <Blast/Project/ActionCreator.hpp>

TEST(Blast_Project_ActionCreatorTest, can_be_created_without_blowing_up)
{
   Blast::Project::ActionCreator action_creator;
}

TEST(Blast_Project_ActionCreatorTest, run__returns_the_expected_response)
{
   Blast::Project::ActionCreator action_creator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, action_creator.run());
}
