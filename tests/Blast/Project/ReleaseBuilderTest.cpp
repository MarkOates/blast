
#include <gtest/gtest.h>

#include <Blast/Project/ReleaseBuilder.hpp>

TEST(Blast_Project_ReleaseBuilderTest, can_be_created_without_blowing_up)
{
   Blast::Project::ReleaseBuilder release_builder;
}

TEST(Blast_Project_ReleaseBuilderTest, run__returns_the_expected_response)
{
   Blast::Project::ReleaseBuilder release_builder;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, release_builder.run());
}
