
#include <gtest/gtest.h>

#include <Blast/Project/SourceReleaseBuilder.hpp>
#include <Blast/DirectoryExistenceChecker.hpp>
#include <Blast/Testing/TemporaryDirectoryCreator.hpp>
#include <filesystem>

//#define TEMP_SANDBOX_FOLDER ("tmp/test_sandbox")
//std::filesystem::create_directories(TEMP_SANDBOX_FOLDER);
#include <fstream>
static std::string get_file_contents(std::string filename)
{
   std::ifstream t(filename);
   std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
   return str;
}



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
   static const std::string FIXTURE_PATH = "tests/fixtures/FixtureProject2";
   Blast::Project::SourceReleaseBuilder release_builder(FIXTURE_PATH);

   std::vector<std::pair<std::string, std::string>> expected = {
      {
         "tests/fixtures/FixtureProject2/quintessence/ComponentWithExternalSymlink.q.yml",
         "../../test_project/quintessence/ComponentWithExternalSymlink.q.yml",
      },
      {
         "tests/fixtures/FixtureProject2/quintessence/ComponentWithExternalSymlinkThatIsOnlySymlink.q.yml",
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
   // TODO: Make this a 
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


TEST(Blast_Project_SourceReleaseBuilderTest,
   build_source_release_app_info_file_contents__will_return_the_expected_content_for_the_app_info)
{
   static const std::string FIXTURE_PATH = "tests/fixtures/";
   Blast::Project::SourceReleaseBuilder release_builder(
      "/Users/markoates/Releases/", // TODO: Use a fixture path
      "FixtureProject2",
      FIXTURE_PATH + "FixtureProject2"
   );
   std::string expected_app_info_file_contents = "app_icon_filename=data/icons/my-custom-app-icon-01.png\n";
   EXPECT_EQ(expected_app_info_file_contents, release_builder.build_source_release_app_info_file_contents());
}


TEST(Blast_Project_SourceReleaseBuilderTest, get_makefile_content__will_return_the_expected_content)
{
   static const std::string FIXTURE_PATH = "tests/fixtures/";
   std::string GENERATED_MAKEFILE_FIXTURE_FILENAME = FIXTURE_PATH + "GeneratedMakefile.txt";
   EXPECT_EQ(true, std::filesystem::exists(GENERATED_MAKEFILE_FIXTURE_FILENAME));
   std::string expected_makefile_content = get_file_contents(GENERATED_MAKEFILE_FIXTURE_FILENAME);

   Blast::Project::SourceReleaseBuilder release_builder; //(
      //"/Users/markoates/Releases/",
      //"FixtureProject2",
      //FIXTURE_PATH + "FixtureProject2"
   //);
   std::string makefile_content = release_builder.get_makefile_content();

   EXPECT_EQ(expected_makefile_content, makefile_content);
}


TEST(Blast_Project_SourceReleaseBuilderTest,
   DISABLED__get_makefile_content__will_roduce_that_will_build_as_expected)
{
   // TODO
}


