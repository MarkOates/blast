
#include <gtest/gtest.h>

#include <Blast/Project/SourceReleaseBuilder.hpp>
#include <Blast/DirectoryExistenceChecker.hpp>
#include <Blast/Testing/TemporaryDirectoryCreator.hpp>

//#define TEMP_SANDBOX_FOLDER ("tmp/test_sandbox")
//std::filesystem::create_directories(TEMP_SANDBOX_FOLDER);


TEST(Blast_Project_SourceReleaseBuilderTest, can_be_created_without_blowing_up)
{
   Blast::Project::SourceReleaseBuilder release_builder;
}


TEST(Blast_Project_SourceReleaseBuilderTest, list_symlinks__returns_empty_on_an_empty_project)
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
         "bin/fixtures/FixtureProject2/quintessence/ComponentWithExternalSymlink.q.yml",
         "../../test_project/quintessence/ComponentWithExternalSymlink.q.yml",
      },
      {
         "bin/fixtures/FixtureProject2/quintessence/ComponentWithExternalSymlinkThatIsOnlySymlink.q.yml",
         "../../test_project/quintessence/ComponentWithExternalSymlinkThatIsOnlySymlink.q.yml",
      },
   };
   std::vector<std::pair<std::string, std::string>> actual = release_builder.list_symlinks();

   EXPECT_EQ(expected, actual);
}


// this test has been disabled because it is destructive
TEST(Blast_Project_SourceReleaseBuilderTest,
   replace_symlinks_with_copies_of_linked_files__replaces_the_symlinks_with_copies_of_the_symlink_targets)
{
   Blast::Project::SourceReleaseBuilder release_builder;
   release_builder.replace_symlinks_with_copies_of_linked_files();
}


TEST(DISABLED__Blast_Project_SourceReleaseBuilderTest, generate_source_release__creates_the_expected_folder)
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


TEST(Blast_Project_SourceReleaseBuilderTest, get_top_level_folders_in_include__will_return_the_folder_names_in_include)
{
   // TODO: direct this test to a safer test project folder
   std::string base_folder = "/Users/markoates/Repos/blast";
   std::vector<std::string> expected_folder_names = {
      "Hexagon",
      "NcursesArt",
      "Blast",
      "ncurses_art",
      "Quizes"
   };
   std::vector<std::string> actual_folder_names =
      Blast::Project::SourceReleaseBuilder::get_top_level_folders_in_include(base_folder);

   EXPECT_EQ(expected_folder_names, actual_folder_names); 
}


TEST(Blast_Project_SourceReleaseBuilderTest, get_top_level_folders_in_src__will_return_the_folder_names_in_include)
{
   // TODO: direct this test to a safer test project folder
   std::string base_folder = "/Users/markoates/Repos/blast";
   std::vector<std::string> expected_folder_names = {
      "Hexagon",
      "NcursesArt",
      "Blast",
      "ncurses_art",
      "Quizes"
   };
   std::vector<std::string> actual_folder_names =
      Blast::Project::SourceReleaseBuilder::get_top_level_folders_in_src(base_folder);

   EXPECT_EQ(expected_folder_names, actual_folder_names); 
}


TEST(Blast_Project_SourceReleaseBuilderTest, DISABLED__generate_source_release__will_not_blow_up)
{
   // WIP
   //std::string temp_directory = Blast::Testing::TemporaryDirectoryCreator.create();

   //Blast::Project::SourceReleaseBuilder release_builder;
   //release_builder.set_releases_base_folder(temp_directory);

   // TODO: Check expected files are created
   // TODO: Check files have the expected content
   // TODO: Check expected allegro_flare folders are present
   // TODO: Check expected removed allegro_flare folders are not present
}


