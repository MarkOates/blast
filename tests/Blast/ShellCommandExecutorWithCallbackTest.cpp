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


TEST(ShellCommandExecutorWithCallbackTest, execute__when_capture_stderr_is_false__will_not_include_stderr_in_the_output)
{
   std::string expected_string = "hello shell command!";
   std::stringstream command;
   command << "printf \"" << expected_string << "\" && cd a-directory-that-does-not-exist/";

   Blast::ShellCommandExecutorWithCallback executor(command.str());
   executor.set_capture_stderr(false);

   EXPECT_EQ(expected_string, executor.execute());
}


TEST(ShellCommandExecutorWithCallbackTest, execute__when_capture_stderr_is_true__will_include_stderr_in_the_output)
{
   std::stringstream command;
   command << "printf \"hello shell command!\" && cd a-directory-that-does-not-exist/";

   Blast::ShellCommandExecutorWithCallback executor(command.str());
   executor.set_capture_stderr(true);

   std::string expected_result =
      "hello shell command!sh: line 0: cd: a-directory-that-does-not-exist/: No such file or directory\n";
   EXPECT_EQ(expected_result, executor.execute());
}


TEST(ShellCommandExecutorWithCallbackTest,
   executed_successfully__after_execute___will_return_false_if_there_was_an_error_during_execution)
{
   std::stringstream command;
   command << "cd a-directory-that-does-not-exist";

   Blast::ShellCommandExecutorWithCallback executor(command.str());

   EXPECT_EQ("sh: line 0: cd: a-directory-that-does-not-exist: No such file or directory\n", executor.execute());
   EXPECT_EQ(true, executor.get_finished());
   EXPECT_EQ(false, executor.get_executed_successfully());
   EXPECT_EQ(1, executor.get_exit_status());
}


TEST(ShellCommandExecutorWithCallbackTest,
   executed_successfully__after_execute___will_return_true_if_there_was_no_error_during_execution)
{
   std::string expected_string = "hello shell command!";
   std::stringstream command;
   command << "printf \"" << expected_string << "\"";

   Blast::ShellCommandExecutorWithCallback executor(command.str());

   EXPECT_EQ(expected_string, executor.execute());
   EXPECT_EQ(true, executor.get_executed_successfully());
   EXPECT_EQ(0, executor.get_exit_status());
}


TEST(ShellCommandExecutorWithCallbackTest, capture_stderr__is_true_by_default)
{
   Blast::ShellCommandExecutorWithCallback executor;
   EXPECT_EQ(true, executor.get_capture_stderr());
}


