
#include <gtest/gtest.h>

#include <Blast/Project/ReleaseBuilder.hpp>
#include <Blast/DirectoryExistenceChecker.hpp>

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
   static const std::string FIXTURE_PATH = "bin/fixtures/FixtureProject2";
   Blast::Project::ReleaseBuilder release_builder(FIXTURE_PATH);

   std::vector<std::pair<std::string, std::string>> expected = {
      {
         "bin/fixtures/FixtureProject2/quintessence/ComponentWithExternalSymlinkThatIsOnlySymlink.q.yml",
         "../../test_project/quintessence/ComponentWithExternalSymlinkThatIsOnlySymlink.q.yml",
      },
      {
         "bin/fixtures/FixtureProject2/quintessence/ComponentWithExternalSymlink.q.yml",
         "../../test_project/quintessence/ComponentWithExternalSymlink.q.yml",
      },
   };
   std::vector<std::pair<std::string, std::string>> actual = release_builder.list_symlinks();

   EXPECT_EQ(expected, actual);
}

// this test has been disabled because it is destructive
TEST(DISABLED_Blast_Project_ReleaseBuilderTest,
   replace_symlinks_with_copies_of_linked_files__removes_the_symlinks_and_replaces_them_with_copies_of_the_symlink_targets)
{
   Blast::Project::ReleaseBuilder release_builder("/Users/markoates/Desktop/Release");
   release_builder.replace_symlinks_with_copies_of_linked_files();
}

TEST(Blast_Project_ReleaseBuilderTest, generate_source_release__creates_the_expected_folder)
{
   std::string folder = "/Users/markoates/Desktop/ReleaseTest";

   {
      Blast::DirectoryExistenceChecker directory_existence_checker(folder);
      EXPECT_EQ(false, directory_existence_checker.exists());
   }

   Blast::Project::ReleaseBuilder release_builder(folder);
   release_builder.generate_source_release();

   Blast::DirectoryExistenceChecker directory_existence_checker(folder);
   EXPECT_EQ(true, directory_existence_checker.exists());
}

