#include <gtest/gtest.h>


#include <Blast/ShellCommandExecutorWithCallback.hpp>


#include <iostream>


TEST(ShellCommandExecutorWithCallbackTest, can_be_created)
{
   Blast::ShellCommandExecutorWithCallback executor("ls");
}


TEST(ShellCommandExecutorWithCallbackTest, execute__executes_a_command_and_returns_the_output)
{
   std::string expected_string = "hello shell command!";
   std::stringstream command;
   command << "printf \"" << expected_string << "\"";

   Blast::ShellCommandExecutorWithCallback executor(command.str());

   ASSERT_EQ(expected_string, executor.execute());
}
