
#include <gtest/gtest.h>

#include <Blast/BuildInfoCppFileGenerator.hpp>

#if defined(_WIN32) || defined(_WIN64)
   static std::string TEST_FIXTURES_FOLDER = "/msys64/home/Mark/Repos/blast/tests/fixtures/";
#else // assume MacOS for now
   static std::string TEST_FIXTURES_FOLDER = "/Users/markoates/Repos/blast/tests/fixtures/";
#endif


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


static Blast::BuildInfo build_test_build_info()
{
   Blast::BuildInfo result;
   result.set_allegro_version_git_hash("802dd8cad4be85dd0a57ed4368963ae954a9c88f");
   return result;
}


TEST(Blast_BuildInfoCppFileGeneratorTest, can_be_created_without_blowing_up)
{
   Blast::BuildInfoCppFileGenerator version_info_cpp_file_generator;
}


TEST(Blast_BuildInfoCppFileGeneratorTest, header_file_content__will_return_the_expected_generated_content)
{
   std::string VERSION_INFO_EXPECTED_HPP = TEST_FIXTURES_FOLDER + "BuildInfo_hpp_file_content.txt";

   Blast::BuildInfoCppFileGenerator version_info_cpp_file_generator;
   version_info_cpp_file_generator.initialize();

   std::string expected_generated_content = file_get_contents(VERSION_INFO_EXPECTED_HPP);
   std::string actual_generated_content = version_info_cpp_file_generator.header_file_content();

   EXPECT_EQ(expected_generated_content, actual_generated_content);
}


TEST(Blast_BuildInfoCppFileGeneratorTest, source_file_content__will_return_the_expected_generated_content)
{
   std::string VERSION_INFO_EXPECTED_HPP = TEST_FIXTURES_FOLDER + "BuildInfo_cpp_file_content.txt";

   Blast::BuildInfoCppFileGenerator version_info_cpp_file_generator;
   version_info_cpp_file_generator.set_build_info(build_test_build_info());
   version_info_cpp_file_generator.initialize();

   std::string expected_generated_content = file_get_contents(VERSION_INFO_EXPECTED_HPP);
   std::string actual_generated_content = version_info_cpp_file_generator.source_file_content();

   EXPECT_EQ(expected_generated_content, actual_generated_content);
}


