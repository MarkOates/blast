

#include <gtest/gtest.h>

#include <Blast/Quintessence/ComponentGenerator.hpp>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


TEST(Blast_Quintessence_ComponentGenerator, can_be_created_without_blowing_up)
{
   ComponentGenerator generator;
}


TEST(Blast_Quintessence_ComponentGenerator, get_quintessence_foldername__returns_the_expected_folder_name)
{
   std::string expected_folder_name = "quintessence/Foo/Bar";
   ComponentGenerator generator("Foo/Bar/Baz");

   ASSERT_EQ(expected_folder_name, generator.get_quintessence_foldername());
}


TEST(Blast_Quintessence_ComponentGenerator, get_test_foldername__returns_the_expected_folder_name)
{
   std::string expected_folder_name = "tests/Baz/Bar";
   ComponentGenerator generator("Baz/Bar/Foo");

   ASSERT_EQ(expected_folder_name, generator.get_test_foldername());
}


TEST(Blast_Quintessence_ComponentGenerator, get_component_tail_snakecase__returns_the_expected_string)
{
   std::string expected_folder_name = "bar_basil_bonk";
   ComponentGenerator generator("Baz/Bar/BarBasilBonk");

   ASSERT_EQ(expected_folder_name, generator.get_component_tail_snakecase());
}


