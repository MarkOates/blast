

#include <gtest/gtest.h>

#include <Blast/FileSystemChangeNotifier.hpp>

#include <fstream>


int callbacks = 0;


void(* increment_callback_count)(std::string) = [](std::string path) mutable {
   ASSERT_EQ("./bin/tests", path);
   callbacks++;
};


TEST(DISABLED_FileSystemChangeNotifierTest, can_be_created)
{
   FileSystemChangeNotifier file_system_change_notifier;
}


TEST(FileSystemChangeNotifierTest, calls_the_callback_function_when_a_folder_content_is_modified)
{
   callbacks = 0;

   std::string test_path = "./bin/tests";
   std::string test_filename = "test_filename.txt";

   FileSystemChangeNotifier file_system_change_notifier({ test_path }, increment_callback_count);

   std::stringstream output_filename;
   output_filename << test_path << '/' << test_filename;

   std::ofstream output_file(output_filename.str());
   output_file << "Hello world!";
   output_file.close();

   ASSERT_EQ(1, callbacks);
}


