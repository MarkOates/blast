
#include <gtest/gtest.h>

#include <Blast/Project/ReleaseBuilder.hpp>

TEST(Blast_Project_ReleaseBuilderTest, can_be_created_without_blowing_up)
{
   Blast::Project::ReleaseBuilder release_builder;
}

TEST(Blast_Project_ReleaseBuilderTest, project_repo_base_path__returns_the_expected_default)
{
   Blast::Project::ReleaseBuilder release_builder;
   std::string expected_default_project_repo_base_path = "Users/markoates/Repos/";
   std::string actual_default_project_repo_base_path = release_builder.get_project_repo_base_path();

   ASSERT_EQ(expected_default_project_repo_base_path, actual_default_project_repo_base_path);
}

TEST(Blast_Project_ReleaseBuilderTest, get_source_file_listing__returns_the_expected_response)
{
   Blast::Project::ReleaseBuilder release_builder("LabyrinthOfLore");
}
