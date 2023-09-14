

#include <gtest/gtest.h>

#include <Blast/Quintessence/ComponentGenerator.hpp>

#include <Blast/Testing/ErrorAssertions.hpp>


TEST(Blast_Quintessence_ComponentGenerator, can_be_created_without_blowing_up)
{
   ComponentGenerator generator;
}


TEST(Blast_Quintessence_ComponentGenerator,
   get_component_name_first_fragment__returns_the_first_fragment_of_the_component_name)
{
   std::string expected_folder_name = "Foo";
   ComponentGenerator generator("Foo/Bar/Baz");

   ASSERT_EQ(expected_folder_name, generator.get_component_name_first_fragment());
}


TEST(Blast_Quintessence_ComponentGenerator,
   get_component_name_last_fragment__returns_the_last_fragment_of_the_component_name)
{
   std::string expected_folder_name = "Baz";
   ComponentGenerator generator("Foo/Bar/Baz");

   ASSERT_EQ(expected_folder_name, generator.get_component_name_last_fragment());
}


TEST(Blast_Quintessence_ComponentGenerator,
   get_component_name_up_to_last_fragment__returns_the_last_fragment_of_the_component_name)
{
   std::string expected_result = "Foo/Bar";
   ComponentGenerator generator("Foo/Bar/Baz");

   ASSERT_EQ(expected_result, generator.get_component_name_up_to_last_fragment());
}


TEST(Blast_Quintessence_ComponentGenerator,
   get_component_name_preceeding_fragment__returns_the_last_fragment_of_the_component_name)
{
   std::string expected_result = "Bar";
   ComponentGenerator generator("Foo/Bar/Baz");

   ASSERT_EQ(expected_result, generator.get_component_name_preceeding_fragment());
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


TEST(Blast_Quintessence_ComponentGenerator, get_header_foldername__returns_the_expected_folder_name)
{
   std::string expected_folder_name = "include/Baz/Bar";
   ComponentGenerator generator("Baz/Bar/Foo");

   ASSERT_EQ(expected_folder_name, generator.get_header_foldername());
}


TEST(Blast_Quintessence_ComponentGenerator, get_source_foldername__returns_the_expected_folder_name)
{
   std::string expected_folder_name = "src/Baz/Bar";
   ComponentGenerator generator("Baz/Bar/Foo");

   ASSERT_EQ(expected_folder_name, generator.get_source_foldername());
}


TEST(Blast_Quintessence_ComponentGenerator, get_component_tail_snakecase__returns_the_expected_string)
{
   std::string expected_snakecase_tail = "bar_basil_bonk";
   ComponentGenerator generator("Baz/Bar/BarBasilBonk");

   ASSERT_EQ(expected_snakecase_tail, generator.get_component_tail_snakecase());
}


TEST(Blast_Quintessence_ComponentGenerator, get_component_tail_all_caps_constant__returns_the_expected_string)
{
   // TODO: rename these variable names
   std::string expected_snakecase_tail = "BAR_BASIL_BONK";
   ComponentGenerator generator("Baz/Bar/BarBasilBonk");

   ASSERT_EQ(expected_snakecase_tail, generator.get_component_tail_all_caps_constant());
}


TEST(Blast_Quintessence_ComponentGenerator, get_class_name__returns_the_expected_string)
{
   std::string expected_snakecase_tail = "Baz::Bar::BarBasilBonk";
   ComponentGenerator generator("Baz/Bar/BarBasilBonk");

   ASSERT_EQ(expected_snakecase_tail, generator.get_class_name());
}


TEST(Blast_Quintessence_ComponentGenerator, get_class_name_up_to_last_fragment__returns_the_expected_string)
{
   std::string expected_snakecase_tail = "Baz::Bar";
   ComponentGenerator generator("Baz/Bar/BarBasilBonk");

   ASSERT_EQ(expected_snakecase_tail, generator.get_class_name_up_to_last_fragment());
}


TEST(Blast_Quintessence_ComponentGenerator,
   build_command_to_make_parent_directories_for__will_return_the_expected_command)
{
   std::string expected_command = "mkdir -p \"$(dirname 'foo/bar/baz.txt')\""
                                  //" && echo \"Directory created: $(dirname 'foo/bar/baz.txt')\""
                                  ;
   std::string actual_command = ComponentGenerator::build_command_to_make_parent_directories_for("foo/bar/baz.txt");

   EXPECT_EQ(expected_command, actual_command);
}


TEST(Blast_Quintessence_ComponentGenerator,
   infer_comparison_operand_class_name__will_return_the_name_of_the_comparison_operator)
{
   ComponentGenerator generator("Baz/Testing/Comparison/Baz/BarBasilBonk");
   std::string expected_comparison_operand_class_name = "Baz/BarBasilBonk";
   ASSERT_EQ(expected_comparison_operand_class_name, generator.infer_comparison_operand_class_name());
}


TEST(Blast_Quintessence_ComponentGenerator,
   infer_comparison_operand_class_name__with_an_invalid_class_name__will_throw_an_error)
{
   // DEBUG:
   ComponentGenerator generator("Baz/Testing/Baz/BarBasilBonk");
   std::string expected_comparison_operand_class_name = "Baz/BarBasilBonk";
   std::string expected_error_message = "[Blast::Quintessence::ComponentGenerator::infer_comparison_operand_class_name]"
      " error: The component name \"Baz/Testing/Baz/BarBasilBonk\" does not appear to be a valid comparison class "
      "(contains \"/Testing/Comparison/\"), and as such a comparison operand class name cannot be inferred.";
   EXPECT_THROW_WITH_MESSAGE(
      generator.infer_comparison_operand_class_name(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(Blast_Quintessence_ComponentGenerator,
   infer_json_loader_operand_component_name__will_return_the_expected_class_name)
{
   std::vector<std::pair<std::string, std::string>> test_data = {
      {
         "AllegroFlare/JSONLoaders/AllegroFlare/Vec3D",
         "AllegroFlare/Vec3D"
      },
   };

   for (auto &test_datum : test_data)
   {
      std::string class_name = test_datum.first;
      std::string expected_json_loader_operand_component_name = test_datum.second;
      ComponentGenerator generator(class_name);

      std::string actual_json_loader_operand_component_name = generator.infer_json_loader_operand_component_name();
      EXPECT_EQ(expected_json_loader_operand_component_name, actual_json_loader_operand_component_name);
   }
}


