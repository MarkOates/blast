
#include <gtest/gtest.h>

#include <Blast/CamelCaseToUnderscoreConverter.hpp>


TEST(Blast_CamelCaseToUnderscoreConverterTest, convert_to_underscores__returns_the_expected_string)
{
   Blast::CamelCaseToUnderscoreConverter converter("ThisIsTheComponentName");
   std::string expected_string = "this_is_the_component_name";
   EXPECT_EQ(expected_string, converter.convert_to_underscores());
}


