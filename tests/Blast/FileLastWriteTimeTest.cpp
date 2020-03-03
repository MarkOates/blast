
#include <gtest/gtest.h>

#include <Blast/FileLastWriteTime.hpp>

TEST(Blast_FileLastWriteTimeTest, can_be_created_without_blowing_up)
{
   Blast::FileLastWriteTime file_last_write_time;
}

TEST(DISABLED_Blast_FileLastWriteTimeTest, last_write_time__with_a_filename_that_does_not_exist__raises_an_exception)
{
   std::string filename = "file_that_does_not_exist.txt";
   Blast::FileLastWriteTime file_last_write_time(filename);
   file_last_write_time.last_write_time();
}

TEST(Blast_FileLastWriteTimeTest, last_write_time__returns_the_last_write_time_of_the_file)
{
   std::string filename = "tests/fixtures/file_that_should_not_change_modified_time.txt";
   Blast::FileLastWriteTime file_last_write_time(filename);
   std::time_t expected_write_time = 1583205122;
   std::time_t actual_write_time = file_last_write_time.last_write_time();
   EXPECT_EQ(expected_write_time, actual_write_time);
}

