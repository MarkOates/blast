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

   EXPECT_EQ(expected_string, executor.execute());
}


TEST(ShellCommandExecutorWithCallbackTest, execute__when_capture_stderr_is_true__will_also_include_stderr_in_the_output)
{
   std::stringstream command;
   command << "printf \"hello shell command!\" && cd a-directory-that-does-not-exist/";

   Blast::ShellCommandExecutorWithCallback executor(command.str());
   executor.set_capture_stderr(true);

   std::string expected_result =
      "hello shell command!sh: line 0: cd: a-directory-that-does-not-exist/: No such file or directory\n";
   EXPECT_EQ(expected_result, executor.execute());
}


TEST(ShellCommandExecutorWithCallbackTest, execute__when_capture_stderr_is_false__will_not_include_stderr_in_the_output)
{
   std::string expected_string = "hello shell command!";
   std::stringstream command;
   command << "printf \"" << expected_string << "\" && cd a-directory-that-does-not-exist/";

   Blast::ShellCommandExecutorWithCallback executor(command.str());
   executor.set_capture_stderr(false);

   EXPECT_EQ(expected_string, executor.execute());
}


