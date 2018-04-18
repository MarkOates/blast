#include <gtest/gtest.h>


#include <Blast/ShellCommandExecutor.hpp>


#include <iostream>


TEST(ShellCommandExecutorTest, can_be_created)
{
   Blast::ShellCommandExecutor shell_command_executor("ls");
}


TEST(ShellCommandExecutorTest, executes_a_shell_command_and_returns_the_output)
{
   std::string expected_string = "hello shell command!";
   std::stringstream command;
   command << "printf \"" << expected_string << "\"";

   Blast::ShellCommandExecutor shell_command_executor(command.str());

   ASSERT_EQ(expected_string, shell_command_executor.execute());
}


