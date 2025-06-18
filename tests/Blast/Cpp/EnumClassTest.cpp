
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
   std::vector<std::string> enumerators = { "FOO", "BAR", "BAZ" };
   Blast::Cpp::EnumClass enum_class("FooBar", enumerators);
   Blast::Cpp::Function method = enum_class.build_to_string_method();
   std::string expected_body = R"END(if (value == FooBar::FOO) return "foo";
if (value == FooBar::BAR) return "bar";
if (value == FooBar::BAZ) return "baz";
return "error";
)END";

   EXPECT_EQ("std::string", method.get_type());
   EXPECT_EQ(expected_body, method.get_body());
   EXPECT_EQ(true, method.get_is_static());
   EXPECT_EQ(true, method.get_is_const());
}


TEST(Blast_Cpp_EnumClassTest, build_from_string_method__will_return_a_cpp_function_with_the_expected_content)
{
   std::vector<std::string> enumerators = { "FOO", "BAR", "BAZ" };
   Blast::Cpp::EnumClass enum_class("FooBar", enumerators);
   Blast::Cpp::Function method = enum_class.build_from_string_method();
   std::string expected_body = R"END(if (value == "foo") return FooBar::FOO;
if (value == "bar") return FooBar::BAR;
if (value == "baz") return FooBar::BAZ;
throw std::runtime_error("Blast/Cpp/EnumClass: ERROR: Could not find enum for " + value + ");
)END";

   EXPECT_EQ("std::string", method.get_type());
   EXPECT_EQ(expected_body, method.get_body());
   EXPECT_EQ(true, method.get_is_static());
   EXPECT_EQ(true, method.get_is_const());
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


TEST(Blast_Cpp_EnumClassTest, set_enumerators__will_set_the_enumerators)
{
   Blast::Cpp::EnumClass enum_class;
   std::vector<std::string> enumerators = { "FOO", "BAR", "BAZ" };
   enum_class.set_enumerators(enumerators);
   EXPECT_EQ(enum_class.get_enumerators(), enumerators);
}


TEST(Blast_Cpp_EnumClassTest, set_element__with_a_list_that_does_not_contain_unique_enumerators__will_throw_an_error)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_THROW_GUARD_ERROR(
      enum_class.set_enumerators({ "FOO", "FOO" }),
      "Blast::Cpp::EnumClass::set_enumerators",
      "validate_elements_are_unique(enumerators)"
   );
}


TEST(Blast_Cpp_EnumClassTest, name__is_set_to_the_default_value_by_default)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ(Blast::Cpp::EnumClass::DEFAULT_CLASS_NAME, enum_class.get_name());
}


TEST(Blast_Cpp_EnumClassTest, DEFAULT_CLASS_NAME__has_the_expected_value_of_being_blank)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ("", Blast::Cpp::EnumClass::DEFAULT_CLASS_NAME);
}


TEST(Blast_Cpp_EnumClassTest, has_name__returns_false_when_the_name_is_empty)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ(false, enum_class.has_name());
}


TEST(Blast_Cpp_EnumClassTest, has_name__returns_true_when_a_name_is_present)
{
   Blast::Cpp::EnumClass enum_class;
   enum_class.set_name("Foobar");
   EXPECT_EQ(true, enum_class.has_name());
}


TEST(Blast_Cpp_EnumClassTest, scope__is_set_to_DEFAULT_SCOPE_by_default)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ(Blast::Cpp::EnumClass::DEFAULT_SCOPE, enum_class.get_scope());
}


TEST(Blast_Cpp_EnumClassTest, DEFAULT_SCOPE__has_the_expected_default_value_of_private)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ("private", Blast::Cpp::EnumClass::DEFAULT_SCOPE);
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


TEST(Blast_Cpp_EnumClassTest, type__is_set_to_DEFAULT_TYPE_by_default)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ(Blast::Cpp::EnumClass::DEFAULT_TYPE, enum_class.get_type());
}


TEST(Blast_Cpp_EnumClassTest, set_type__will_set_the_type)
{
   Blast::Cpp::EnumClass enum_class;
   enum_class.set_type("uint32_t");
   EXPECT_EQ("uint32_t", enum_class.get_type());
}


TEST(Blast_Cpp_EnumClassTest, set_type__when_setting_an_invalid_type__will_throw_an_error_listing_valid_types)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_THROW_WITH_MESSAGE(
      enum_class.set_type("an-invalid-type"),
      std::runtime_error,
      "[Blast::Cpp::EnumClass::set_type]: error: The provided type \"an-invalid-type\" is invalid. Permitted types "
         "are [\"\", \"int\", \"int16_t\", \"int32_t\", \"uint16_t\", \"uint32_t\", ]"
   );
}


TEST(Blast_Cpp_EnumClassTest, DEFAULT_TYPE__has_the_expected_default_value_of_blank)
{
   Blast::Cpp::EnumClass enum_class;
   EXPECT_EQ("", Blast::Cpp::EnumClass::DEFAULT_TYPE);
}


TEST(Blast_Cpp_EnumClassTest, is_power_of_two__returns_true_if_the_value_is_a_power_of_two)
{
   std::vector<int> test_data = {
      { 0, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 },
   };

   for (auto &test_datum : test_data)
   {
      EXPECT_EQ(true, Blast::Cpp::EnumClass::is_power_of_two(test_datum));
   }
}


TEST(Blast_Cpp_EnumClassTest, is_power_of_two__returns_false_if_the_value_is_not_a_power_of_two)
{
   std::vector<int> test_data = {
      { -2, 3, 5, 6, 14, 17, 31, 33, 34 },
   };

   for (auto &test_datum : test_data)
   {
      EXPECT_EQ(false, Blast::Cpp::EnumClass::is_power_of_two(test_datum));
   }
}


TEST(Blast_Cpp_EnumClassTest, 
   validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise__when_bitwise_is_true_and_start_from_is_not_a_power\
of_two__will_throw_an_error)
{
   std::vector<int> test_data = {
      { 3, 5, 6, 14, 17, 31, 33, 34 },
   };

   for (auto &test_datum : test_data)
   {
      EXPECT_THROW_WITH_MESSAGE(
         Blast::Cpp::EnumClass::validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise(true, test_datum),
         std::runtime_error,
         "[Blast::Cpp::EnumClass::validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise]: error: "
            "\"enumerators_are_bitwise\" is set to true, and thus \"start_from\" must be a power of two but it is not."
      );
   }
}


/*
TEST(Blast_Cpp_EnumClassTest, build_to_string_method__will_return_a_function_definition_for_a_to_string_method)
{
   std::vector<std::string> enumerators = { "FOO", "BAR", "BAZ" };
   Blast::Cpp::EnumClass enum_class("FooBar", enumerators);
   Blast::Cpp::Function method = enum_class.build_to_string_method();

   //Blast::Cpp::EnumClass enum_class;
   //enum_class.set_name("Foo");
   Blast::Cpp::Function function = enum_class.build_to_string_method();

   EXPECT_EQ("to_string", function.get_name());
   //EXPECT_EQ("uint32_t", enum_class.get_type());
}
*/


