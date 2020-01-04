
#include <gtest/gtest.h>

#include <Blast/Project/ReleaseBuilder.hpp>

TEST(Blast_Project_ReleaseBuilderTest, can_be_created_without_blowing_up)
{
   Blast::Project::ReleaseBuilder release_builder;
}

TEST(Blast_Project_ReleaseBuilderTest, swap_symlinks__returns_the_expected_response)
{
   Blast::Project::ReleaseBuilder release_builder;
   std::pair<std::string, std::string> expected = {};
   std::pair<std::string, std::string> actual = release_builder.list_symlinks();

   EXPECT_EQ(expected, actual);
}
