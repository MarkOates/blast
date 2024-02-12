
#include <gtest/gtest.h>

#include <Blast/String/Unindenter.hpp>


TEST(Blast_String_UnindenterTest, can_be_created_without_blowing_up)
{
   Blast::String::Unindenter unindenter;
}


TEST(Blast_String_UnindenterTest, unindent__will_remove_spaces)
{
std::string source = R"END(
   Foo
   Bar
      Baz
         Boz
   Biz
)END";

   Blast::String::Unindenter unindenter(source);
   std::string actual = unindenter.unindent(2);

std::string expected = R"END(
 Foo
 Bar
    Baz
       Boz
 Biz
)END";

   EXPECT_EQ(expected, actual);
}


TEST(Blast_String_UnindenterTest, indent__will_add_spaces_to_the_front_of_each_line)
{
std::string source = R"END(
   Foo
   Bar
      Baz
         Boz
   Biz
)END";

   Blast::String::Unindenter unindenter(source);
   std::string actual = unindenter.indent(3);

std::string expected = R"END(
      Foo
      Bar
         Baz
            Boz
      Biz
)END";

   EXPECT_EQ(expected, actual);
}


