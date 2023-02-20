
#include <gtest/gtest.h>

#include <Blast/Cpp/EnumClassFormatter.hpp>


TEST(Blast_Cpp_EnumClassFormatterTest, can_be_created_without_blowing_up)
{
   Blast::Cpp::EnumClassFormatter enum_class_formatter;
}


TEST(Blast_Cpp_EnumClassFormatterTest, build_definition__returns_the_expected_response)
{
   Blast::Cpp::EnumClass enum_class("Foo", { "BIZ", "BAZ", "BUZ" });
   Blast::Cpp::EnumClassFormatter enum_class_formatter(enum_class);
   std::string expected_string =
R"END(enum class Foo
{
   BIZ = 0,
   BAZ,
   BUZ,
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


