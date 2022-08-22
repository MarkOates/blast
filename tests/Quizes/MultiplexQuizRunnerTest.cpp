
#include <gtest/gtest.h>

#include <Quizes/MultiplexQuizRunner.hpp>



TEST(Quizes_MultiplexQuizRunnerTest, can_be_created_without_blowing_up)
{
   Quizes::MultiplexQuizRunner multiplex_quiz_runner;
}


TEST(Quizes_MultiplexQuizRunnerTest, DISABLED__run__runs_the_quiz_program)
{
   Quizes::MultiplexQuizRunner multiplex_quiz_runner;
   // DISABLED because destructive
   multiplex_quiz_runner.run();
   SUCCEED();
}


