
#include <gtest/gtest.h>

#include <Blast/TemplatedFile.hpp>

TEST(Blast_TemplatedFileTest, can_be_created_without_blowing_up)
{
   Blast::TemplatedFile templated_file;
}

TEST(Blast_TemplatedFileTest, generate_content__returns_the_expected_filled_content)
{
   Blast::TemplatedFile templated_file;
   std::string expected_string = "Hello, World!";
   EXPECT_EQ(expected_string, templated_file.generate_content());
}
