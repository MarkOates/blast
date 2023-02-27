
#include <gtest/gtest.h>

#include <Blast/BuildSystem/BuildStageRenderers/ShellCommand.hpp>


TEST(Blast_BuildSystem_BuildStageRenderers_ShellCommandTest, can_be_created_without_blowing_up)
{
   Blast::BuildSystem::BuildStageRenderers::ShellCommand shell_command;
}


TEST(Blast_BuildSystem_BuildStageRenderers_ShellCommandTest, has_the_expected_type)
{
   Blast::BuildSystem::BuildStageRenderers::ShellCommand shell_command;
   EXPECT_EQ("ShellCommand", shell_command.get_type());
}


