
#include <gtest/gtest.h>

#include <Blast/FileCreator.hpp>

#include <Blast/Testing/TemporaryFilenameCreator.hpp>
#include <filesystem>


#include <fstream>
#include <sstream>
static std::string file_get_contents(std::string filename)
{
   std::ifstream file(filename);
   std::string result;

   // Check if the file is open
   if (file.is_open())
   {
      // Read the contents of the file line by line
      std::string line;
      std::string read_buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

      // Close the file when done
      file.close();

      result = read_buffer;
    }
    else
    {
       // If the file couldn't be opened, print an error message
       throw std::runtime_error(
          "[file_get_contents(in Blast/FileCreator test)]: error: "
          "could not open file \"" + filename + "\" for reading."
       );
    }

    return result;
}


TEST(Blast_FileCreatorTest, can_be_created_without_blowing_up)
{
   Blast::FileCreator file_creator;
}


TEST(Blast_FileCreatorTest, DISABLED__create_if_not_exists__when_the_file_does_not_exist__creates_it)
{
   std::string filename = "a_test_filename.txt";
   std::string file_content = "the content of the test file";
   Blast::FileCreator file_creator(filename, file_content);

   //EXPECT_EQ(expected_string, file_creator.create_if_not_exists());
}


TEST(Blast_FileCreatorTest, DISABLED__create_if_not_exists__when_the_file_does_exist__does_nothing)
{
   // check existed file contents are unchanged
}


TEST(Blast_FileCreatorTest, create_or_overwrite__when_the_file_does_not_exist__creates_the_file)
{
   Blast::Testing::TemporaryFilenameCreator temporary_filename_creator;
   std::string temporary_filename = temporary_filename_creator.create_filename_within_guaranteed_unique_directory();
   std::string file_contents_to_write = "foobar";


   ASSERT_EQ(false, std::filesystem::exists(temporary_filename));
   Blast::FileCreator file_creator(temporary_filename, file_contents_to_write);

   file_creator.create_or_overwrite();

   EXPECT_EQ(true, std::filesystem::exists(temporary_filename));
   std::string actual_file_contents = file_get_contents(temporary_filename);
   EXPECT_EQ(actual_file_contents, file_contents_to_write);
}


TEST(Blast_FileCreatorTest,
   DISABLED__create_or_overwrite__when_the_file_does_exist__discards_the_file_contents_and_overwrites_it)
{
   // TODO
}


