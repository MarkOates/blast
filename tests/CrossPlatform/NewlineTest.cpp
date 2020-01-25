

#include <gtest/gtest.h>


TEST(CrossPlatform__NewlineTest, newlines_have_the_expected_format)
{
   std::stringstream output;
   output << "foo" << std::endl;

   ASSERT_EQ("foo\n", output.str());
}


