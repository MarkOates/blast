

#include <gtest/gtest.h>

#include <Blast/DirectoryCreator.hpp>

#include <Blast/DirectoryExistenceChecker.hpp>
#include <Blast/StringJoiner.hpp>

#include <fstream>
bool file_exists(const std::string& filename)
{
   return Blast::DirectoryExistenceChecker(filename).exists();
}

#include <cstdio>
bool remove_directory(const std::string& file_or_directory)
{
   return (remove(file_or_directory.c_str()) == 0);
}

bool ensure_nonexistent_testing_directory(const std::string &file_or_directory)
{
   if (file_exists(file_or_directory)) return remove_directory(file_or_directory);
   return true;
}


TEST(DirectoryCreatorTest, can_be_created_without_arguments)
{
   Blast::DirectoryCreator directory_creator;
}


TEST(DirectoryCreatorTest, create__returns_true_when_a_directory_is_present)
{
   std::vector<std::string> directories_that_should_exist = { "quintessence" };

   for (auto &directory_that_should_exist : directories_that_should_exist)
      ASSERT_TRUE(file_exists(directory_that_should_exist));

   Blast::DirectoryCreator directory_creator(directories_that_should_exist);
   ASSERT_TRUE(directory_creator.create());
}


TEST(DirectoryCreatorTest, create__returns_false_when_passing_a_string_that_contains_a_backslash_delimiter)
{
   std::vector<std::string> directories_that_should_exist = { "directory_that_does_not_exist/and_has_a_nested_directory/" };

   for (auto &directory_that_should_exist : directories_that_should_exist)
      ASSERT_FALSE(file_exists(directory_that_should_exist));

   Blast::DirectoryCreator directory_creator(directories_that_should_exist);
   ASSERT_FALSE(directory_creator.create());
}


TEST(DirectoryCreatorTest, create__returns_true_when_attempting_to_create_multiple_nested_directories)
{
   std::vector<std::string> directories_that_will_exist = { "tmp", "directory_that_does_not_exist", "and_has_a_nested_directory" };

   std::string composite_directory = Blast::StringJoiner(directories_that_will_exist, "/").join();

   ASSERT_TRUE(ensure_nonexistent_testing_directory(composite_directory));

   Blast::DirectoryCreator directory_creator(directories_that_will_exist);
   ASSERT_TRUE(directory_creator.create());

   EXPECT_TRUE(remove_directory(composite_directory)) << "Test cleanup failed.";
}


