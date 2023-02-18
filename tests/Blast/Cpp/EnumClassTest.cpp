
#include <gtest/gtest.h>

#include <Blast/Cpp/EnumClass.hpp>


TEST(Blast_Cpp_EnumClassTest, can_be_created_without_blowing_up)
{
   Blast::Cpp::EnumClass enum_class;
}


TEST(Blast_Cpp_EnumClassTest, build_to_string_method__will_return_a_cpp_function_with_the_expected_content)
{
   Blast::Cpp::EnumClass enum_class("FooBar", { "BIZZ", "BAZZ", "BUZZ" });
   Blast::Cpp::Function method = enum_class.build_to_string_method();

   EXPECT_EQ("std::string", method.get_type());
   // TODO: check remaining properties
}


