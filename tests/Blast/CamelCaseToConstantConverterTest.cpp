
#include <gtest/gtest.h>

#include <Blast/CamelCaseToConstantConverter.hpp>

TEST(Blast_CamelCaseToConstantConverterTest, can_be_created_without_blowing_up)
{
   Blast::CamelCaseToConstantConverter camel_case_to_constant;
}

TEST(Blast_CamelCaseToConstantConverterTest, convert_to_constant__returns_the_expected_string)
{
   Blast::CamelCaseToConstantConverter converter("ThisIsTheComponentName");
   std::string expected_string = "THIS_IS_THE_COMPONENT_NAME";
   EXPECT_EQ(expected_string, converter.convert_to_constant());
}
