

#include <gtest/gtest.h>

#include <Blast/DirectoryCreator.hpp>


TEST(DirectoryCreatorTest, can_be_created_without_arguments)
{
   Blast::DirectoryCreator directory_creator;
}


TEST(DirectoryCreatorTest, create__returns_true_when_a_directory_is_present)
{
   std::vector<std::string> directories_that_should_exist = { "quintessence" };

   Blast::DirectoryCreator directory_creator(directories_that_should_exist);
   ASSERT_TRUE(directory_creator.create());
}


TEST(DirectoryCreatorTest, create__returns_false_when_attempting_to_creating_multiple_nested_directories)
{
   std::vector<std::string> directories_that_should_exist = { "directory_that_does_not_exist/and_has_a_nested_directory/" };
   Blast::DirectoryCreator directory_creator(directories_that_should_exist);
   ASSERT_FALSE(directory_creator.create());
}


