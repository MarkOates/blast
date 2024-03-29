
#include <gtest/gtest.h>

#include <Blast/Cpp/EnumClassFormatter.hpp>


TEST(Blast_Cpp_EnumClassFormatterTest, can_be_created_without_blowing_up)
{
   Blast::Cpp::EnumClassFormatter enum_class_formatter;
}


TEST(Blast_Cpp_EnumClassFormatterTest, build_definition__returns_the_expected_response)
{
   Blast::Cpp::EnumClass enum_class("Foo", { "BIZ", "BAZ", "BUZ" });
   enum_class.set_is_class("true");
   enum_class.set_start_from(42);
   Blast::Cpp::EnumClassFormatter enum_class_formatter(enum_class);
   std::string expected_string =
R"END(enum class Foo
{
   BIZ = 42,
   BAZ,
   BUZ,
};
)END";
   EXPECT_EQ(expected_string, enum_class_formatter.build_enum_definition());
}


TEST(Blast_Cpp_EnumClassFormatterTest, build_definition__when_enumerators_are_bitwise__returns_the_expected_response)
{
   Blast::Cpp::EnumClass enum_class("Foo", { "BIZ", "BAZ", "BUZ", "BOZ", "BOX", "BOTZ" });
   enum_class.set_is_class("true");
   enum_class.set_enumerators_are_bitwise(true);
   Blast::Cpp::EnumClassFormatter enum_class_formatter(enum_class);
   std::string expected_string =
R"END(enum class Foo
{
   BIZ = 0x0000,
   BAZ = 0x0001,
   BUZ = 0x0002,
   BOZ = 0x0004,
   BOX = 0x0008,
   BOTZ = 0x0010,
};
)END";
   EXPECT_EQ(expected_string, enum_class_formatter.build_enum_definition());
}


TEST(Blast_Cpp_EnumClassFormatterTest,
   build_definition__when_enumerators_are_bitwise__and_a_start_from__returns_the_expected_response)
{
   Blast::Cpp::EnumClass enum_class("Foo", { "BIZ", "BAZ", "BUZ" });
   enum_class.set_is_class("true");
   enum_class.set_enumerators_are_bitwise(true);
   enum_class.set_start_from(0x0040);
   Blast::Cpp::EnumClassFormatter enum_class_formatter(enum_class);
   std::string expected_string =
R"END(enum class Foo
{
   BIZ = 0x0040,
   BAZ = 0x0080,
   BUZ = 0x0100,
};
)END";
   EXPECT_EQ(expected_string, enum_class_formatter.build_enum_definition());
}


TEST(Blast_Cpp_EnumClassFormatterTest, build_definition__when_there_is_no_class_name__is_formatted_as_expected)
{
   Blast::Cpp::EnumClass enum_class;
   enum_class.set_enumerators({ "BIZ", "BAZ", "BUZ" });
   enum_class.set_type("uint32_t");

   Blast::Cpp::EnumClassFormatter enum_class_formatter(enum_class);
   std::string expected_string =
R"END(enum : uint32_t
{
   BIZ = 0,
   BAZ,
   BUZ,
};
)END";
   EXPECT_EQ(expected_string, enum_class_formatter.build_enum_definition());
}


TEST(Blast_Cpp_EnumClassFormatterTest,
   output_nth_bit_as_hex_string__will_return_the_nth_bitfield_enumerator_in_a_string_format)
{
   std::vector<std::pair<int, std::string>> test_data = {
      { 0,  "0x0000" },
      { 1,  "0x0001" },
      { 2,  "0x0002" },
      { 3,  "0x0004" },
      { 4,  "0x0008" },
      { 5,  "0x0010" },
      { 6,  "0x0020" },
      { 7,  "0x0040" },
      { 8,  "0x0080" },
      { 9,  "0x0100" },
      { 10, "0x0200" },
      { 11, "0x0400" },
      { 12, "0x0800" },
   };

   for (auto &test_datum : test_data)
   {
      std::string expected = test_datum.second;
      std::string actual = Blast::Cpp::EnumClassFormatter::output_nth_bit_as_hex_string(test_datum.first);
      EXPECT_EQ(expected, actual);
   }
}


