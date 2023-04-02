
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


