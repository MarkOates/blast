
#include <gtest/gtest.h>

#include <Blast/Testing/TemporaryFilenameCreator.hpp>


TEST(Blast_Testing_TemporaryFilenameCreatorTest, can_be_created_without_blowing_up)
{
   Blast::Testing::TemporaryFilenameCreator temporary_filename_creator;
}


TEST(Blast_Testing_TemporaryFilenameCreatorTest, create__on_successive_runs__will_return_different_results)
{
   Blast::Testing::TemporaryFilenameCreator temporary_filename_creator;
   std::string actual_first_value = temporary_filename_creator.create();
   std::string actual_second_value = temporary_filename_creator.create();
   EXPECT_NE(actual_first_value, actual_second_value);
}


