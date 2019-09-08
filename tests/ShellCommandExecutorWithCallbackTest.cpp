
#include <gtest/gtest.h>

#include <Blast/ShellCommandExecutorWithCallback.hpp>

TEST(Blast__ShellCommandExecutorWithCallbackTest, run__returns_the_expected_response)
{
   Blast::ShellCommandExecutorWithCallback program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.execute());
}
