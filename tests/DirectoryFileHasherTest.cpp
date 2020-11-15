
#include <gtest/gtest.h>

#include <DirectoryFileHasher.hpp>

TEST(DirectoryFileHasherTest, can_be_created_without_blowing_up)
{
   DirectoryFileHasher directory_file_hasher;
}

TEST(DirectoryFileHasherTest, run__returns_the_expected_response)
{
   DirectoryFileHasher directory_file_hasher;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, directory_file_hasher.run());
}
