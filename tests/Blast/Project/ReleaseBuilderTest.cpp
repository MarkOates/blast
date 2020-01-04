
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

