
#include <gtest/gtest.h>

#include <Blast/FileLastWriteTime.hpp>

TEST(Blast_FileLastWriteTimeTest, can_be_created_without_blowing_up)
{
   Blast::FileLastWriteTime file_last_write_time;
}

TEST(Blast_FileLastWriteTimeTest, last_write_time__with_a_filename_that_does_not_exist__raises_an_exception)
{
   std::string filename = "file_that_does_not_exist.txt";
   Blast::FileLastWriteTime file_last_write_time(filename);
   ASSERT_ANY_THROW(file_last_write_time.last_write_time()); // TODO specify the exception that is being caught
}

TEST(Blast_FileLastWriteTimeTest, last_write_time__returns_the_last_write_time_of_the_file)
{
   std::string filename = "tests/fixtures/file_that_should_not_change_modified_time.txt";
   Blast::FileLastWriteTime file_last_write_time(filename);
   std::time_t actual_write_time = file_last_write_time.last_write_time();
   ASSERT_GT(actual_write_time, 0);

   // sanity test
   std::time_t a_sane_last_write_time = 1583205122;
   ASSERT_GE(actual_write_time, a_sane_last_write_time);
}

