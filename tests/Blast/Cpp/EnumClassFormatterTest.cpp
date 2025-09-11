
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


TEST(Blast_Cpp_EnumClassFormatterTest,
   build_definition__with_a_uint64_t_and_65_bitwise_flags__formats_correctly)
{
   Blast::Cpp::EnumClass enum_class;
   enum_class.set_name("Flags64");
   enum_class.set_type("uint64_t");
   enum_class.set_is_class(true);
   enum_class.set_enumerators_are_bitwise(true);

   std::vector<std::string> enumerators;
   for (int i=0; i<=64; i++)
   {
      enumerators.push_back("FLAG_" + std::to_string(i));
   }
   enum_class.set_enumerators(enumerators);

   Blast::Cpp::EnumClassFormatter enum_class_formatter(enum_class);
   std::string expected_string =
R"END(enum class Flags64 : uint64_t
{
   FLAG_0 = 0x0000,
   FLAG_1 = 0x0001,
   FLAG_2 = 0x0002,
   FLAG_3 = 0x0004,
   FLAG_4 = 0x0008,
   FLAG_5 = 0x0010,
   FLAG_6 = 0x0020,
   FLAG_7 = 0x0040,
   FLAG_8 = 0x0080,
   FLAG_9 = 0x0100,
   FLAG_10 = 0x0200,
   FLAG_11 = 0x0400,
   FLAG_12 = 0x0800,
   FLAG_13 = 0x1000,
   FLAG_14 = 0x2000,
   FLAG_15 = 0x4000,
   FLAG_16 = 0x8000,
   FLAG_17 = 0x10000,
   FLAG_18 = 0x20000,
   FLAG_19 = 0x40000,
   FLAG_20 = 0x80000,
   FLAG_21 = 0x100000,
   FLAG_22 = 0x200000,
   FLAG_23 = 0x400000,
   FLAG_24 = 0x800000,
   FLAG_25 = 0x1000000,
   FLAG_26 = 0x2000000,
   FLAG_27 = 0x4000000,
   FLAG_28 = 0x8000000,
   FLAG_29 = 0x10000000,
   FLAG_30 = 0x20000000,
   FLAG_31 = 0x40000000,
   FLAG_32 = 0x80000000,
   FLAG_33 = 0x100000000,
   FLAG_34 = 0x200000000,
   FLAG_35 = 0x400000000,
   FLAG_36 = 0x800000000,
   FLAG_37 = 0x1000000000,
   FLAG_38 = 0x2000000000,
   FLAG_39 = 0x4000000000,
   FLAG_40 = 0x8000000000,
   FLAG_41 = 0x10000000000,
   FLAG_42 = 0x20000000000,
   FLAG_43 = 0x40000000000,
   FLAG_44 = 0x80000000000,
   FLAG_45 = 0x100000000000,
   FLAG_46 = 0x200000000000,
   FLAG_47 = 0x400000000000,
   FLAG_48 = 0x800000000000,
   FLAG_49 = 0x1000000000000,
   FLAG_50 = 0x2000000000000,
   FLAG_51 = 0x4000000000000,
   FLAG_52 = 0x8000000000000,
   FLAG_53 = 0x10000000000000,
   FLAG_54 = 0x20000000000000,
   FLAG_55 = 0x40000000000000,
   FLAG_56 = 0x80000000000000,
   FLAG_57 = 0x100000000000000,
   FLAG_58 = 0x200000000000000,
   FLAG_59 = 0x400000000000000,
   FLAG_60 = 0x800000000000000,
   FLAG_61 = 0x1000000000000000,
   FLAG_62 = 0x2000000000000000,
   FLAG_63 = 0x4000000000000000,
   FLAG_64 = 0x8000000000000000,
};
)END";
   EXPECT_EQ(expected_string, enum_class_formatter.build_enum_definition());
}

