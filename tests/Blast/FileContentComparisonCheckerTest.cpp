

#include <gtest/gtest.h>

#include <Blast/FileContentComparisonChecker.hpp>


#define FIXTURE_FILENAME "bin/fixtures/test_file.txt"


TEST(Blast__FileContentComparisonCheckerTest, expected_test_file_exists)
{
   ASSERT_TRUE(std::filesystem::exists(FIXTURE_FILENAME));
}


TEST(Blast__FileContentComparisonCheckerTest, file_exists__returns_true_if_the_file_exists)
{
   std::string filename = FIXTURE_FILENAME;
   Blast::FileContentComparisonChecker project_component_filename_generator(filename);

   ASSERT_EQ(true, project_component_filename_generator.file_exists());
}


TEST(Blast__FileContentComparisonCheckerTest, file_exists__returns_false_if_the_file_exists)
{
   std::string filename = "file/that/does/not_exist.dne";
   Blast::FileContentComparisonChecker project_component_filename_generator(filename);

   ASSERT_EQ(false, project_component_filename_generator.file_exists());
}


TEST(Blast__FileContentComparisonCheckerTest, is_equal__returns_true_if_the_file_content_equals_the_expected_content)
{
   std::string filename = FIXTURE_FILENAME;
   std::string expected_file_content = "this is a test file\nwith some text content.\n";

   Blast::FileContentComparisonChecker project_component_filename_generator(filename, expected_file_content);

   ASSERT_EQ(true, project_component_filename_generator.is_equal());
}


TEST(Blast__FileContentComparisonCheckerTest, is_equal__returns_false_if_the_file_content_does_not_equal_the_expected_content)
{
   std::string filename = FIXTURE_FILENAME;
   std::string expected_file_content = "this is some content that is different from the actual content";

   Blast::FileContentComparisonChecker project_component_filename_generator(filename, expected_file_content);

   ASSERT_EQ(false, project_component_filename_generator.is_equal());
}


