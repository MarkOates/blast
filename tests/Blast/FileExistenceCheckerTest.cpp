
#include <gtest/gtest.h>

#include <Blast/FileExistenceChecker.hpp>

TEST(Blast_FileExistenceCheckerTest, can_be_created_without_blowing_up)
{
   Blast::FileExistenceChecker file_existence_checker;
}

TEST(Blast_FileExistenceCheckerTest, run__returns_the_expected_response)
{
   Blast::FileExistenceChecker file_existence_checker("foobar");
   EXPECT_EQ(false, file_existence_checker.exists());
}

TEST(DISABLED_Blast_FileExistenceCheckerTest, exists__returns_true_for_regular_files)
{
}

TEST(DISABLED_Blast_FileExistenceCheckerTest, exists__returns_false_for_directories)
{
}

TEST(DISABLED_Blast_FileExistenceCheckerTest, exists__returns_true_for_symlinks)
{
}
