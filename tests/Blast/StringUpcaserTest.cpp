
#include <gtest/gtest.h>

#include <Blast/StringUpcaser.hpp>

TEST(Blast_StringUpcaserTest, can_be_created_without_blowing_up)
{
   Blast::StringUpcaser string_upcaser;
}

TEST(Blast_StringUpcaserTest, upcase__returns_the_string_converted_to_upcase)
{
   std::string text_to_upcase = "hello world!";
   Blast::StringUpcaser string_upcaser(text_to_upcase);

   std::string expected_upcased_string = "HELLO WORLD!";
   std::string actual_upcased_string = string_upcaser.upcase();

   EXPECT_EQ(expected_upcased_string, actual_upcased_string);
}
