
#include <gtest/gtest.h>

#include <Blast/FileCreator.hpp>

TEST(Blast_FileCreatorTest, can_be_created_without_blowing_up)
{
   Blast::FileCreator file_creator;
}

TEST(Blast_FileCreatorTest, create_if_not_exists__when_the_file_does_not_exist__creates_it)
{
   std::string filename = "a_test_filename.txt";
   std::string file_content = "the content of the test file";
   Blast::FileCreator file_creator(filename, file_content);

   //EXPECT_EQ(expected_string, file_creator.create_if_not_exists());
}

TEST(Blast_FileCreatorTest, create_if_not_exists__when_the_file_does_exist__does_nothing)
{
   // check existed file contents are unchanged
}

TEST(Blast_FileCreatorTest, create_or_overwrite__when_the_file_does_not_exist__creates_the_file)
{
   // TODO
}

TEST(Blast_FileCreatorTest, create_or_overwrite__when_the_file_does_exist__discards_the_file_contents_and_overwrites_it)
{
   // TODO
}

