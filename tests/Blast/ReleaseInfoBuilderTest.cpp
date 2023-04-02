
#include <gtest/gtest.h>

#include <Blast/Testing/ErrorAssertions.hpp>

#include <Blast/ReleaseInfoBuilder.hpp>


TEST(Blast_ReleaseInfoBuilderTest, can_be_created_without_blowing_up)
{
   Blast::ReleaseInfoBuilder release_info_builder;
}


TEST(Blast_ReleaseInfoBuilderTest, build__when_a_project_folder_does_not_exist__raises_an_exception)
{
   Blast::ReleaseInfoBuilder release_info_builder("ProjectThatDoesNotExist");
   EXPECT_THROW_GUARD_ERROR(
      release_info_builder.build(),
      "ReleaseInfoBuilder::build",
      "project_folder_exists()"
   );
}


TEST(Blast_ReleaseInfoBuilderTest, build__with_an_invalid_project_name__throws_an_error)
{
   // TODO: Make a list of invalid project names to test against
   Blast::ReleaseInfoBuilder release_info_builder(" ");
   EXPECT_THROW_GUARD_ERROR(
      release_info_builder.build(),
      "ReleaseInfoBuilder::build",
      "project_name_is_valid()"
   );
}


TEST(Blast_ReleaseInfoBuilderTest, build__with_an_empty_project_name__throws_an_error)
{
   Blast::ReleaseInfoBuilder release_info_builder("");
   EXPECT_THROW_GUARD_ERROR(
      release_info_builder.build(),
      "ReleaseInfoBuilder::build",
      "project_name_is_valid()"
   );
}


TEST(Blast_ReleaseInfoBuilderTest, DISABLED__build__assigns_the_project_git_hash)
{
   Blast::ReleaseInfoBuilder release_info_builder("blast");
   Blast::ReleaseInfo release_info = release_info_builder.build();
   std::string expected_hash = "b70dda5c5c18921fd56474ffe68310c234880488";
   std::string actual_hash = release_info.get_project_git_hash();
   EXPECT_EQ(expected_hash, actual_hash);
}


TEST(Blast_ReleaseInfoBuilderTest, build__assigns_the_project_git_branch)
{
   Blast::ReleaseInfoBuilder release_info_builder("blast");
   Blast::ReleaseInfo release_info = release_info_builder.build();
   std::string expected_branch = "master";
   std::string actual_branch = release_info.get_project_git_branch();
   EXPECT_EQ(expected_branch, actual_branch);
}


TEST(Blast_ReleaseInfoBuilderTest, build__assigns_the_project_git_num_commits)
{
   Blast::ReleaseInfoBuilder release_info_builder("blast");
   Blast::ReleaseInfo release_info = release_info_builder.build();
   int expected_num_commits = 1292;
   int actual_num_commits = release_info.get_project_git_num_commits();
   EXPECT_EQ(expected_num_commits, actual_num_commits);
}


TEST(Blast_ReleaseInfoBuilderTest, build__assigns_the_allegro_version_git_hash)
{
   Blast::ReleaseInfoBuilder release_info_builder("blast");
   Blast::ReleaseInfo release_info = release_info_builder.build();
   std::string expected_hash = "802dd8cad4be85dd0a57ed4368963ae954a9c88f";
   std::string actual_hash = release_info.get_allegro_version_git_hash();
   EXPECT_EQ(expected_hash, actual_hash);
}


TEST(Blast_ReleaseInfoBuilderTest, build__assigns_the_allegro_version_git_branch)
{
   Blast::ReleaseInfoBuilder release_info_builder("blast");
   Blast::ReleaseInfo release_info = release_info_builder.build();
   std::string expected_branch = "remove-double-free";
   std::string actual_branch = release_info.get_allegro_version_git_branch();
   EXPECT_EQ(expected_branch, actual_branch);
}


TEST(Blast_ReleaseInfoBuilderTest, build__assigns_the_allegro_version_git_num_commits)
{
   Blast::ReleaseInfoBuilder release_info_builder("blast");
   Blast::ReleaseInfo release_info = release_info_builder.build();
   int expected_num_commits = 11883;
   int actual_num_commits = release_info.get_allegro_version_git_num_commits();
   EXPECT_EQ(expected_num_commits, actual_num_commits);
}


TEST(Blast_ReleaseInfoBuilderTest, build__assigns_the_allegro_flare_version_git_hash)
{
   Blast::ReleaseInfoBuilder release_info_builder("blast");
   Blast::ReleaseInfo release_info = release_info_builder.build();
   std::string expected_hash = "df55f94015ad9f40aade3ab999cde05b8518a0a6";
   std::string actual_hash = release_info.get_allegro_flare_version_git_hash();
   EXPECT_EQ(expected_hash, actual_hash);
}


TEST(Blast_ReleaseInfoBuilderTest, build__assigns_the_allegro_flare_version_git_branch)
{
   Blast::ReleaseInfoBuilder release_info_builder("blast");
   Blast::ReleaseInfo release_info = release_info_builder.build();
   std::string expected_branch = "master";
   std::string actual_branch = release_info.get_allegro_flare_version_git_branch();
   EXPECT_EQ(expected_branch, actual_branch);
}


TEST(Blast_ReleaseInfoBuilderTest, build__assigns_the_allegro_flare_version_git_num_commits)
{
   Blast::ReleaseInfoBuilder release_info_builder("blast");
   Blast::ReleaseInfo release_info = release_info_builder.build();
   int expected_num_commits = 3746;
   int actual_num_commits = release_info.get_allegro_flare_version_git_num_commits();
   EXPECT_EQ(expected_num_commits, actual_num_commits);
}


