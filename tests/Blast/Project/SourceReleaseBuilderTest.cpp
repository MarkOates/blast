
#include <gtest/gtest.h>

#include <Blast/Project/SourceReleaseBuilder.hpp>
#include <Blast/DirectoryExistenceChecker.hpp>

//#define TEMP_SANDBOX_FOLDER ("tmp/test_sandbox")
//std::filesystem::create_directories(TEMP_SANDBOX_FOLDER);


TEST(Blast_Project_SourceReleaseBuilderTest, can_be_created_without_blowing_up)
{
   Blast::Project::SourceReleaseBuilder release_builder;
}


TEST(Blast_Project_SourceReleaseBuilderTest, list_symlinks__returns_the_expected_response)
{
   Blast::Project::SourceReleaseBuilder release_builder;
   std::vector<std::pair<std::string, std::string>> expected = {};
   std::vector<std::pair<std::string, std::string>> actual = release_builder.list_symlinks();

   EXPECT_EQ(expected, actual);
}


TEST(Blast_Project_SourceReleaseBuilderTest, list_symlinks__returns_the_list_of_all_symlinks_in_the_base_directory)
{
   static const std::string FIXTURE_PATH = "bin/fixtures/FixtureProject2";
   Blast::Project::SourceReleaseBuilder release_builder(FIXTURE_PATH);

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
TEST(DISABLED_Blast_Project_SourceReleaseBuilderTest,
   replace_symlinks_with_copies_of_linked_files__removes_the_symlinks_and_replaces_them_with_copies_of_the_symlink_targets)
{
   Blast::Project::SourceReleaseBuilder release_builder("/Users/markoates/Desktop/SourceRelease");
   release_builder.replace_symlinks_with_copies_of_linked_files();
}


TEST(DISABLED_Blast_Project_SourceReleaseBuilderTest, generate_source_release__creates_the_expected_folder)
{
   std::string folder = "/Users/markoates/Desktop/SourceReleaseTest";

   {
      Blast::DirectoryExistenceChecker directory_existence_checker(folder);
      EXPECT_EQ(false, directory_existence_checker.exists());
   }

   Blast::Project::SourceReleaseBuilder release_builder(folder);
   release_builder.generate_source_release();

   Blast::DirectoryExistenceChecker directory_existence_checker(folder);
   EXPECT_EQ(true, directory_existence_checker.exists());
}


TEST(Blast_Project_SourceReleaseBuilderTest, generate_macos_release__creates_the_expected_folder)
{
}


