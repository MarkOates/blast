
#include <gtest/gtest.h>

#include <ShellCommandExecutorWithCallback.hpp>

TEST(ShellCommandExecutorWithCallbackTest, run__returns_the_expected_response)
{
   ShellCommandExecutorWithCallback program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
