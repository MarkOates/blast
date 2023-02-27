
#include <gtest/gtest.h>

#include <Blast/BuildSystem/BuildStages/ShellCommand.hpp>


TEST(Blast_BuildSystem_BuildStages_ShellCommandTest, can_be_created_without_blowing_up)
{
   Blast::BuildSystem::BuildStages::ShellCommand shell_command;
}


TEST(Blast_BuildSystem_BuildStages_ShellCommandTest, has_the_expected_type)
{
   Blast::BuildSystem::BuildStages::ShellCommand shell_command;
   EXPECT_EQ("ShellCommand", shell_command.get_type());
}


TEST(Blast_BuildSystem_BuildStages_ShellCommandTest,
   execute__will_execute_the_shell_command_and_capture_the_result)
{
   std::string shell_command = "printf \"this is test output\"";
   Blast::BuildSystem::BuildStages::ShellCommand shell_command_build_stage(shell_command);

   shell_command_build_stage.execute();

   EXPECT_EQ("this is test output", shell_command_build_stage.get_shell_command_result());
}


