

#include <gtest/gtest.h>

#include <Blast/DirectoryExistenceChecker.hpp>


TEST(DirectoryExistenceCheckerTest, can_be_created_without_arguments)
{
   Blast::DirectoryExistenceChecker directory_existence_checker;
}


TEST(DirectoryExistenceCheckerTest, exists__returns_true_when_a_directory_is_present)
{
   std::string directory_that_should_exist = "quintessence"; // this directory is expected to exist on the filesystem
                                                             // note that this test executable must be run from the
                                                             // directory where this expected directory is to be located
   Blast::DirectoryExistenceChecker directory_existence_checker(directory_that_should_exist);
   ASSERT_TRUE(directory_existence_checker.exists());
}


TEST(DirectoryExistenceCheckerTest, exists__returns_false_when_a_directory_is_not_present)
{
   Blast::DirectoryExistenceChecker directory_existence_checker("directory_that_does_not_exist");
   ASSERT_FALSE(directory_existence_checker.exists());
}


TEST(DirectoryExistenceCheckerTest, exists__without_arguments__does_not_blow_up)
{
   Blast::DirectoryExistenceChecker directory_existence_checker;
   directory_existence_checker.exists();
   SUCCEED();
}


TEST(DirectoryExistenceCheckerTest, exists__with_an_empty_string_directory__returns_false)
{
   Blast::DirectoryExistenceChecker directory_existence_checker("");
   ASSERT_FALSE(directory_existence_checker.exists());
}


