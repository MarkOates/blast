
#include <gtest/gtest.h>

#include <Blast/Project/ProgramLister.hpp>

static std::string TEST_PROJECT_ROOT_DIRECTORY = "tests/fixtures/FixtureProject2/";


TEST(Blast_Project_ProgramListerTest, can_be_created_without_blowing_up)
{
   Blast::Project::ProgramLister program_lister;
}


TEST(Blast_Project_ProgramListerTest,
   build_program_lister_shell_command__returns_the_expected_shell_command)
{
   Blast::Project::ProgramLister program_lister("/Project/root/directory");
   std::string expected_shell_command = "cd /Project/root/directory && find programs -type f -name \"*\"";
   std::string actual_shell_command = program_lister.build_program_lister_shell_command();
   EXPECT_EQ(expected_shell_command, actual_shell_command);
}


TEST(Blast_Project_ProgramListerTest, program_filenames__returns_the_sorted_list_of_program_filenames_in_the_project)
{
   Blast::Project::ProgramLister program_lister(TEST_PROJECT_ROOT_DIRECTORY);
   std::vector<std::string> expected_program_filenames = {
         "programs/nested/nested_program.cpp",
         "programs/program1.cpp",
         "programs/program2.cpp",
      };
   EXPECT_EQ(expected_program_filenames, program_lister.program_filenames());
}


