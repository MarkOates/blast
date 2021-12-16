
#include <gtest/gtest.h>

#include <Blast/FileExistenceChecker.hpp>


#ifdef _WIN32
#define TEST_FIXTURES_DIRECTORY 'THIS/FILE/PATH/NOT/SET/FOR/WIN'
#else
#define TEST_FIXTURES_DIRECTORY "/Users/markoates/Repos/blast/bin/fixtures/";
#endif


TEST(Blast_FileExistenceCheckerTest, can_be_created_without_blowing_up)
{
   Blast::FileExistenceChecker file_existence_checker;
}

TEST(Blast_FileExistenceCheckerTest, exists__returns_true_for_regular_files)
{
   std::string test_fixtures_directory = TEST_FIXTURES_DIRECTORY;
   std::string expected_file_to_exist = test_fixtures_directory + "file_that_exists.txt";

   Blast::FileExistenceChecker file_existence_checker(expected_file_to_exist);
   EXPECT_EQ(true, file_existence_checker.exists());
}

TEST(Blast_FileExistenceCheckerTest, exists__returns_false_for_files_that_are_missing)
{
   Blast::FileExistenceChecker file_existence_checker("file_that_does_not_exist.txt");
   EXPECT_EQ(false, file_existence_checker.exists());
}

TEST(DISABLED_Blast_FileExistenceCheckerTest, exists__returns_false_for_directories)
{
}

TEST(DISABLED_Blast_FileExistenceCheckerTest, exists__returns_true_for_symlinks)
{
}
