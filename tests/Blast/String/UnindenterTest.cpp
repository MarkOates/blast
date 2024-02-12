
#include <gtest/gtest.h>

#include <Blast/String/Unindenter.hpp>


TEST(Blast_String_UnindenterTest, can_be_created_without_blowing_up)
{
   Blast::String::Unindenter unindenter;
}


TEST(Blast_String_UnindenterTest, remove_spaces_at_beginning__will_remove_spaces)
{
std::string source = R"END(
   Foo
   Bar
      Baz
         Boz
   Biz
)END";

   Blast::String::Unindenter unindenter(source);
   std::string actual = unindenter.remove_spaces_at_beginning(2);

std::string expected = R"END(
 Foo
 Bar
    Baz
       Boz
 Biz
)END";

   EXPECT_EQ(expected, actual);
}


