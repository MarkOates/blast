

#include <gtest/gtest.h>

#include <Blast/DirectoryCreator.hpp>


TEST(DirectoryCreatorTest, can_be_created_without_arguments)
{
   Blast::DirectoryCreator directory_creator;
}


TEST(DirectoryCreatorTest, exists_returns_true_when_a_directory_is_present)
{
   std::string directory_that_should_exist = "quintessence";
   Blast::DirectoryCreator directory_creator(directory_that_should_exist);
   ASSERT_TRUE(directory_creator.create());
}


TEST(DirectoryCreatorTest, exists_returns_false_when_attempting_to_creating_multiple_nested_directories)
{
   Blast::DirectoryCreator directory_creator("directory_that_does_not_exist/and_has_a_nested_directory/");
   ASSERT_FALSE(directory_creator.create());
}


