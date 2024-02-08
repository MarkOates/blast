
#include <gtest/gtest.h>

#include <Blast/Testing/TemporaryFilenameCreator.hpp>
#include <filesystem>


TEST(Blast_Testing_TemporaryFilenameCreatorTest, can_be_created_without_blowing_up)
{
   Blast::Testing::TemporaryFilenameCreator temporary_filename_creator;
}


TEST(Blast_Testing_TemporaryFilenameCreatorTest, create_filename__on_successive_runs__will_return_unique_results)
{
   Blast::Testing::TemporaryFilenameCreator temporary_filename_creator;
   std::string actual_first_value = temporary_filename_creator.create_filename();
   std::string actual_second_value = temporary_filename_creator.create_filename();
   EXPECT_NE(actual_first_value, actual_second_value);
}


TEST(Blast_Testing_TemporaryFilenameCreatorTest,
   create_filename_within_guaranteed_unique_directory__on_successive_runs__will_return_unique_results)
{
   Blast::Testing::TemporaryFilenameCreator temporary_filename_creator;
   std::string actual_first_value = temporary_filename_creator.create_filename_within_guaranteed_unique_directory();
   std::string actual_second_value = temporary_filename_creator.create_filename_within_guaranteed_unique_directory();
   EXPECT_NE(actual_first_value, actual_second_value);
}


TEST(Blast_Testing_TemporaryFilenameCreatorTest,
   create_filename_within_guaranteed_unique_directory__will_create_a_filename_that_does_not_exist)
{
   Blast::Testing::TemporaryFilenameCreator temporary_filename_creator;
   std::string created_filename = temporary_filename_creator.create_filename_within_guaranteed_unique_directory();
   EXPECT_EQ(false, std::filesystem::exists(created_filename));
}


TEST(Blast_Testing_TemporaryFilenameCreatorTest,
   create_filename_within_guaranteed_unique_directory__will_create_a_filename_in_a_directory_that_does_exist)
{
   Blast::Testing::TemporaryFilenameCreator temporary_filename_creator;
   std::string created_filename = temporary_filename_creator.create_filename_within_guaranteed_unique_directory();
   std::string directory = std::filesystem::path(created_filename).parent_path().string();
   EXPECT_EQ(true, std::filesystem::exists(directory));
}


TEST(Blast_Testing_TemporaryFilenameCreatorTest,
   create_filename_within_guaranteed_unique_directory__will_create_a_filename_in_a_directory_that_is_empty)
{
   Blast::Testing::TemporaryFilenameCreator temporary_filename_creator;
   std::string created_filename = temporary_filename_creator.create_filename_within_guaranteed_unique_directory();
   std::string directory = std::filesystem::path(created_filename).parent_path().string();
   EXPECT_EQ(true, std::filesystem::is_empty(directory));
}


