
#include <gtest/gtest.h>

#include <Blast/ReleaseInfoCppFileGenerator.hpp>
static std::string TEST_FIXTURES_FOLDER = "/Users/markoates/Repos/blast/tests/fixtures/";


#include <fstream>
static std::string file_get_contents(std::string filename, bool raise_on_missing_file=true)
{
   std::ifstream file(filename.c_str());
   std::string input = "";
   if (!file)
   {
      if (raise_on_missing_file)
      {
         std::stringstream error_message;
         error_message << "Attempting to open file \"" << filename << "\" but it was not found." << std::endl;
         throw std::runtime_error(error_message.str());
      }
      else
      {
         return "";
      }
   }
   char ch;
   while (file.get(ch)) input.append(1, ch);
   if (!file.eof()) return ""; // strange error
   file.close();
   return input;
}


static Blast::ReleaseInfo build_test_release_info()
{
   Blast::ReleaseInfo result;
   result.set_project_version(7, 12, 0, { "wip", "alpha" });
   return result;
}


TEST(Blast_ReleaseInfoCppFileGeneratorTest, can_be_created_without_blowing_up)
{
   Blast::ReleaseInfoCppFileGenerator version_info_cpp_file_generator;
}


TEST(Blast_ReleaseInfoCppFileGeneratorTest, header_file_content__will_return_the_expected_generated_content)
{
   std::string VERSION_INFO_EXPECTED_HPP = TEST_FIXTURES_FOLDER + "ReleaseInfo_hpp_file_content.txt";

   Blast::ReleaseInfoCppFileGenerator version_info_cpp_file_generator;
   version_info_cpp_file_generator.initialize();

   std::string expected_generated_content = file_get_contents(VERSION_INFO_EXPECTED_HPP);
   std::string actual_generated_content = version_info_cpp_file_generator.header_file_content();

   EXPECT_EQ(expected_generated_content, actual_generated_content);
}


TEST(Blast_ReleaseInfoCppFileGeneratorTest, source_file_content__will_return_the_expected_generated_content)
{
   std::string VERSION_INFO_EXPECTED_HPP = TEST_FIXTURES_FOLDER + "ReleaseInfo_cpp_file_content.txt";

   Blast::ReleaseInfoCppFileGenerator version_info_cpp_file_generator;
   version_info_cpp_file_generator.set_release_info(build_test_release_info());
   version_info_cpp_file_generator.initialize();

   std::string expected_generated_content = file_get_contents(VERSION_INFO_EXPECTED_HPP);
   std::string actual_generated_content = version_info_cpp_file_generator.source_file_content();

   EXPECT_EQ(expected_generated_content, actual_generated_content);
}


