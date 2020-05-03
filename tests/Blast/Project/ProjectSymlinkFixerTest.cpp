
#include <gtest/gtest.h>

#include <Blast/Project/ProjectSymlinkFixer.hpp>

TEST(Blast_Project_ProjectSymlinkFixerTest, can_be_created_without_blowing_up)
{
   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
}

TEST(Blast_Project_ProjectSymlinkFixerTest, run__returns_the_expected_response)
{
   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, project_symlink_fixer.run());
}
