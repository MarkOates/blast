

#include <gtest/gtest.h>

#include <Blast/StringPadder.hpp>


TEST(StringPadderTest, can_be_created)
{
   Blast::StringPadder string_padder;
}


TEST(StringPadderTest, pad__returns_the_string_padded_with_the_expected_outpu)
{
   std::string original_string = "Foobar";
   std::string expected_padded_string = "Foobar########";

   Blast::StringPadder string_padder(original_string, 14, '#');

   ASSERT_EQ(expected_padded_string, string_padder.pad());
}


TEST(StringPadderTest, pad__with_an_input_string_longer_than_the_length_of_the_padding_returns_the_original_string)
{
   std::string original_string = "This text is long and does a lot of long things.";

   Blast::StringPadder string_padder(original_string, 10, '#');

   ASSERT_EQ(original_string, string_padder.pad());
}


