
#include <gtest/gtest.h>

#include <Blast/Cpp/FunctionBody.hpp>


TEST(Blast_Cpp_FunctionBodyTest, can_be_created_without_blowing_up)
{
   Blast::Cpp::FunctionBody function_body;
}


TEST(Blast_Cpp_FunctionBodyTest, DEFAULT_BODY_CONTENT__has_the_expected_value)
{
   EXPECT_STREQ("return;", Blast::Cpp::FunctionBody::DEFAULT_BODY_CONTENT);
}


TEST(Blast_Cpp_FunctionBodyTest, content__has_the_expected_value_matching_DEFAULT_BODY_CONTENT)
{
   Blast::Cpp::FunctionBody function_body;
   EXPECT_EQ(Blast::Cpp::FunctionBody::DEFAULT_BODY_CONTENT, function_body.get_content());
}


