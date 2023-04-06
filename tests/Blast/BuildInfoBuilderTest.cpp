
#include <gtest/gtest.h>

#include <Blast/Testing/ErrorAssertions.hpp>

#include <Blast/BuildInfoBuilder.hpp>


TEST(Blast_BuildInfoBuilderTest, can_be_created_without_blowing_up)
{
   Blast::BuildInfoBuilder build_info_builder;
}


TEST(Blast_BuildInfoBuilderTest, DISABLED__build__assigns_the_allegro_version_git_hash)
{
   Blast::BuildInfoBuilder build_info_builder;
   Blast::BuildInfo build_info = build_info_builder.build();
   std::string expected_hash = "802dd8cad4be85dd0a57ed4368963ae954a9c88f";
   std::string actual_hash = build_info.get_allegro_version_git_hash();
   EXPECT_EQ(expected_hash, actual_hash);
}


TEST(Blast_BuildInfoBuilderTest, DISABLED__build__assigns_the_allegro_version_git_branch)
{
   Blast::BuildInfoBuilder build_info_builder;
   Blast::BuildInfo build_info = build_info_builder.build();
   std::string expected_branch = "remove-double-free";
   std::string actual_branch = build_info.get_allegro_version_git_branch();
   EXPECT_EQ(expected_branch, actual_branch);
}


TEST(Blast_BuildInfoBuilderTest, DISABLED__build__assigns_the_allegro_version_git_num_commits)
{
   Blast::BuildInfoBuilder build_info_builder;
   Blast::BuildInfo build_info = build_info_builder.build();
   int expected_num_commits = 11883;
   int actual_num_commits = build_info.get_allegro_version_git_num_commits();
   EXPECT_EQ(expected_num_commits, actual_num_commits);
}


