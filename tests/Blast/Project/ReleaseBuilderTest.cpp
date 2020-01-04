
#include <gtest/gtest.h>

#include <Blast/Project/ReleaseBuilder.hpp>

TEST(Blast_Project_ReleaseBuilderTest, can_be_created_without_blowing_up)
{
   Blast::Project::ReleaseBuilder release_builder;
}

TEST(Blast_Project_ReleaseBuilderTest, project_repo_base_path__returns_the_expected_default)
{
   Blast::Project::ReleaseBuilder release_builder;
   std::string expected_default_project_repo_base_path = "/Users/markoates/Repos/";
   std::string actual_default_project_repo_base_path = release_builder.get_project_repo_base_path();

   ASSERT_EQ(expected_default_project_repo_base_path, actual_default_project_repo_base_path);
   ASSERT_EQ(expected_default_project_repo_base_path, actual_default_project_repo_base_path);
}

TEST(Blast_Project_ReleaseBuilderTest, get_source_file_listings__returns_the_expected_response)
{
   std::string fixture_base_path = "/Users/markoates/Repos/blast/bin/fixtures/";
   std::string fixture_project_name = "FixtureProject2";
   Blast::Project::ReleaseBuilder release_builder(fixture_project_name, fixture_base_path);

   std::vector<std::string> expected = {
      "src/ComponentB.cpp",
      "src/Nested/ComponentC.cpp",
   };
   std::vector<std::string> actual = release_builder.get_source_file_listings();

   ASSERT_EQ(expected, actual);
}

TEST(Blast_Project_ReleaseBuilderTest, build_repo_base_path_directory_components__returns_the_expected_path_components)
{
   std::string fixture_base_path = "Users/markoates/Repos/blast/bin/fixtures/";
   std::string fixture_project_name = "FixtureProject2";
   Blast::Project::ReleaseBuilder release_builder(fixture_project_name, fixture_base_path);

   std::vector<std::string> expected = {
      "Users", "markoates", "Repos", "blast", "bin", "fixtures",
   };

   std::vector<std::string> actual = release_builder.build_repo_base_path_directory_components();

   ASSERT_EQ(expected, actual);
}

TEST(Blast_Project_ReleaseBuilderTest, build_include_folder_directory_components__returns_the_expected_path_components)
{
   std::string fixture_base_path = "Users/markoates/Repos/blast/bin/fixtures/";
   std::string fixture_project_name = "FixtureProject2";
   Blast::Project::ReleaseBuilder release_builder(fixture_project_name, fixture_base_path);

   std::vector<std::string> expected = {
      "Users", "markoates", "Repos", "blast", "bin", "fixtures", "releases", "include",
   };

   std::vector<std::string> actual = release_builder.build_include_folder_directory_components();

   ASSERT_EQ(expected, actual);
}

TEST(Blast_Project_ReleaseBuilderTest, build_src_folder_directory_components__returns_the_expected_path_components)
{
   std::string fixture_base_path = "Users/markoates/Repos/blast/bin/fixtures/";
   std::string fixture_project_name = "FixtureProject2";
   Blast::Project::ReleaseBuilder release_builder(fixture_project_name, fixture_base_path);

   std::vector<std::string> expected = {
      "Users", "markoates", "Repos", "blast", "bin", "fixtures", "releases", "src",
   };

   std::vector<std::string> actual = release_builder.build_src_folder_directory_components();

   ASSERT_EQ(expected, actual);
}

TEST(Blast_Project_ReleaseBuilderTest, build_data_folder_directory_components__returns_the_expected_path_components)
{
   std::string fixture_base_path = "Users/markoates/Repos/blast/bin/fixtures/";
   std::string fixture_project_name = "FixtureProject2";
   Blast::Project::ReleaseBuilder release_builder(fixture_project_name, fixture_base_path);

   std::vector<std::string> expected = {
      "Users", "markoates", "Repos", "blast", "bin", "fixtures", "releases", "data",
   };

   std::vector<std::string> actual = release_builder.build_data_folder_directory_components();

   ASSERT_EQ(expected, actual);
}

TEST(Blast_Project_ReleaseBuilderTest, create_folders__creates_all_of_the_expected_folders)
{
   std::string fixture_base_path = "Users/markoates/Repos/blast/bin/fixtures/";
   std::string fixture_project_name = "FixtureProject2";
   Blast::Project::ReleaseBuilder release_builder(fixture_project_name, fixture_base_path);

   release_builder.create_folders();

   //ASSERT_EQ(expected, actual);
}

TEST(Blast_Project_ReleaseBuilderTest, duplicate_source_files__creates_folders_for_all_the_components)
{
   std::string fixture_base_path = "Users/markoates/Repos/blast/bin/fixtures/";
   std::string fixture_project_name = "FixtureProject2";
   Blast::Project::ReleaseBuilder release_builder(fixture_project_name, fixture_base_path);

   release_builder.duplicate_source_files();

   //ASSERT_EQ(expected, actual);
}

