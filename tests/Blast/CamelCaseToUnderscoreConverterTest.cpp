
#include <gtest/gtest.h>

#include <Blast/CamelCaseUnderscoreConverter.hpp>


TEST(Blast_CamelCaseUnderscoreConverterTest, convert_to_underscores__returns_the_expected_string)
{
   Blast::CamelCaseUnderscoreConverter converter("ThisIsTheComponentName");
   std::string expected_string = "this_is_the_component_name";
   EXPECT_EQ(expected_string, converter.convert_to_underscores());
}


