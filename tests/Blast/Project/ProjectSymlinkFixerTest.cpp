
#include <gtest/gtest.h>

#include <Blast/Project/ProjectSymlinkFixer.hpp>

TEST(Blast_Project_ProjectSymlinkFixerTest, can_be_created_without_blowing_up)
{
   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
}

TEST(Blast_Project_ProjectSymlinkFixerTest, project_foler__has_getter_and_is_set_with_the_expected_default_value)
{
   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
   std::string expected_default_directory = ".";
   ASSERT_EQ(expected_default_directory, project_symlink_fixer.get_project_folder());
}

TEST(Blast_Project_ProjectSymlinkFixerTest,
   likey_an_intended_symlink__returns_true_if_the_file_is_actually_a_symlink)
{
}

TEST(Blast_Project_ProjectSymlinkFixerTest,
   likey_an_intended_symlink__returns_true_if_the_file_is_likely_intended_to_be_a_symlink)
{
}

TEST(Blast_Project_ProjectSymlinkFixerTest, run__returns_the_expected_response)
{
   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
   //std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, project_symlink_fixer.run());
}
