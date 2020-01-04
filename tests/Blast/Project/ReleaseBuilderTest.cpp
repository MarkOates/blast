
#include <gtest/gtest.h>

#include <Blast/Project/ReleaseBuilder.hpp>

TEST(Blast_Project_ReleaseBuilderTest, can_be_created_without_blowing_up)
{
   Blast::Project::ReleaseBuilder release_builder;
}

TEST(Blast_Project_ReleaseBuilderTest, swap_symlinks__returns_the_expected_response)
{
   Blast::Project::ReleaseBuilder release_builder;
   std::vector<std::pair<std::string, std::string>> expected = {};
   std::vector<std::pair<std::string, std::string>> actual = release_builder.list_symlinks();

   EXPECT_EQ(expected, actual);
}

TEST(Blast_Project_ReleaseBuilderTest, list_symlinks__returns_the_list_of_all_symlinks_in_the_base_directory)
{
   static const std::string FIXTURE_PATH = "/Users/markoates/Repos/blast/bin/fixtures/FixtureProject2";
   Blast::Project::ReleaseBuilder release_builder(FIXTURE_PATH);

   std::vector<std::pair<std::string, std::string>> expected = {
      { "/Users/markoates/Repos/blast/bin/fixtures/FixtureProject2/quintessence/ComponentWithExternalSymlink.q.yml", "/Users/markoates/Repos/blast/bin/fixtures/test_project/quintessence/ComponentWithExternalSymlink.q.yml" },
   };
   std::vector<std::pair<std::string, std::string>> actual = release_builder.list_symlinks();

   EXPECT_EQ(expected, actual);
}

TEST(DISABLED_Blast_Project_ReleaseBuilderTest, replace_symlinks_with_copies_of_linked_files__removes_the_symlinks_and_replaces_them_with_copies_of_the_symlink_targets)
{
   Blast::Project::ReleaseBuilder release_builder("/Users/markoates/Desktop/Release");
   // this test has been disabled because it is destructive
   //release_builder.replace_symlinks_with_copies_of_linked_files();
}

TEST(DISABLED_Blast_Project_ReleaseBuilderTest, generate_source_release__creates_the_release)
{
   Blast::Project::ReleaseBuilder release_builder("/Users/markoates/Desktop/Release");
   //release_builder.generate_source_release();
}

