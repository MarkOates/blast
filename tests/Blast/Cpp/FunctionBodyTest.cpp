
#include <gtest/gtest.h>

#include <Blast/Cpp/FunctionBody.hpp>


TEST(Blast_Cpp_FunctionBodyTest, can_be_created_without_blowing_up)
{
   Blast::Cpp::FunctionBody function_body;
}


TEST(Blast_Cpp_FunctionBodyTest, DEFAULT_BODY_CONTENT__has_the_expected_value)
{
   std::string expected_content = "return;";
   std::string actual_content = Blast::Cpp::FunctionBody::DEFAULT_BODY_CONTENT;
   EXPECT_EQ(expected_content, actual_content);
}


