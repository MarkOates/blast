
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Blast/Cpp/EnumClass.hpp>

#include <Blast/Testing/ErrorAssertions.hpp>


TEST(Blast_Cpp_EnumClassTest, can_be_created_without_blowing_up)
{
   Blast::Cpp::EnumClass enum_class;
}


TEST(Blast_Cpp_EnumClassTest, build_to_string_method__will_return_a_cpp_function_with_the_expected_content)
{
   std::vector<std::string> elements = { "FOO", "BAR", "BAZ" };
   Blast::Cpp::EnumClass enum_class("FooBar", elements);
   Blast::Cpp::Function method = enum_class.build_to_string_method();

   EXPECT_EQ("std::string", method.get_type());
   EXPECT_EQ(enum_class.get_elements(), elements);
}


TEST(Blast_Cpp_EnumClassTest, name_of_to_string_method__is_set_to_the_default)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ(Blast::Cpp::EnumClass::DEFAULT_NAME_OF_TO_STRING_METHOD, enum_class.get_name_of_to_string_method());
}


TEST(Blast_Cpp_EnumClassTest, name_of_to_string_method__has_the_expected_default_value)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ("to_string", Blast::Cpp::EnumClass::DEFAULT_NAME_OF_TO_STRING_METHOD);
}


TEST(Blast_Cpp_EnumClassTest, set_element__will_set_the_elements)
{
   Blast::Cpp::EnumClass enum_class;
   std::vector<std::string> elements = { "FOO", "BAR", "BAZ" };
   enum_class.set_elements(elements);
   EXPECT_EQ(enum_class.get_elements(), elements);
}


TEST(Blast_Cpp_EnumClassTest, set_element__with_a_list_that_does_not_contain_unique_elements__will_throw_an_error)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_THROW_GUARD_ERROR(
      enum_class.set_elements({ "FOO", "FOO" }),
      "EnumClass::set_elements",
      "validate_elements_are_unique(elements)"
   );
}


TEST(Blast_Cpp_EnumClassTest, scope__is_set_to_the_default_value_by_default)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ(Blast::Cpp::EnumClass::DEFAULT_SCOPE, enum_class.get_scope());
}


TEST(Blast_Cpp_EnumClassTest, is_private__returns_true_if_the_class_is_private)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ(true, enum_class.is_private());
}


TEST(Blast_Cpp_EnumClassTest, is_protected__returns_true_if_the_class_is_protected)
{
   Blast::Cpp::EnumClass enum_class;
   enum_class.set_scope("protected");
   EXPECT_EQ(true, enum_class.is_protected());
}


TEST(Blast_Cpp_EnumClassTest, is_public__returns_true_if_the_class_is_public)
{
   Blast::Cpp::EnumClass enum_class;
   enum_class.set_scope("public");
   EXPECT_EQ(true, enum_class.is_public());
}


