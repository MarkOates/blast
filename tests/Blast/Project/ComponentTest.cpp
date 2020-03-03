
#include <gtest/gtest.h>

#include <Blast/Project/Component.hpp>

TEST(Blast_Project_ComponentTest, can_be_created_without_blowing_up)
{
   Blast::Project::Component component;
}

TEST(Blast_Project_ComponentTest, run__has_the_expected_defaults)
{
   Blast::Project::Component component;
   std::string expected_component_name = "Unnamed/Component";
   ASSERT_EQ(expected_component_name, component.get_name());
}

TEST(Blast_Project_ComponentTest, generate_full_path_test_binary_filename__returns_the_expected_string)
{
   std::string component_name = "Hexagon/FoobarComponent";
   std::string project_root = "/Users/markoates/Repos/hexagon/";
   Blast::Project::Component component(component_name, project_root);
   std::string expected_full_path_test_binary_filename = "/Users/markoates/Repos/hexagon/bin/tests/Hexagon/FoobarComponentTest";
   ASSERT_EQ(expected_full_path_test_binary_filename, component.generate_full_path_test_binary_filename());
}

TEST(Blast_Project_ComponentTest, exists__returns_true_if_any_component_files_are_present)
{
   // this may require a more robust test
   Blast::Project::Component component("Blast/Project/Component");
   ASSERT_EQ(true, component.exists());
}

TEST(Blast_Project_ComponentTest, exists__returns_false_if_no_component_files_are_present)
{
   Blast::Project::Component component("Blast/ComponentThatDoesNotExist");
   ASSERT_EQ(false, component.exists());
}

TEST(Blast_Project_ComponentTest, has_quintessence__returns_true_when_a_quintessence_file_is_present)
{
   Blast::Project::Component component("Blast/Project/Component");
   ASSERT_EQ(true, component.has_quintessence());
}

TEST(Blast_Project_ComponentTest, has_quintessence__returns_false_when_a_quintessence_file_is_not_present)
{
   Blast::Project::Component component("Blast/DiceRoller");
   ASSERT_EQ(false, component.has_quintessence());
}

TEST(Blast_Project_ComponentTest, has_only_source_and_header__returns_true_when_the_source_and_header_files_are_present_and_a_quintessence_file_does_not_exist)
{
   Blast::Project::Component component("Blast/DiceRoller");
   ASSERT_EQ(true, component.has_only_source_and_header());
}

TEST(Blast_Project_ComponentTest, has_only_source_and_header__returns_false_when_a_quintessence_file_is_present)
{
   Blast::Project::Component component("Blast/Projets/Component");
   ASSERT_EQ(false, component.has_only_source_and_header());
}

TEST(Blast_Project_ComponentTest, has_test__returns_true_when_a_file_exists)
{
   Blast::Project::Component component("Blast/TemplatedFile");
   ASSERT_EQ(true, component.has_test());
}

TEST(Blast_Project_ComponentTest, has_test__returns_false_when_a_test_file_does_not_exist)
{
   Blast::Project::Component component("Blast/StringSplitter");
   ASSERT_EQ(false, component.has_test());
}

TEST(Blast_Project_ComponentTest, last_write_time__returns_the_most_recent_write_time_among_all_of_the_component_files)
{
   Blast::Project::Component component("Blast/StringSplitter");
   component.last_write_time();
   ASSERT_EQ(false, component.has_test());
}

TEST(Blast_Project_ComponentTest, last_write_time__returns_0_when_the_component_does_not_exist)
{
   Blast::Project::Component component("Blast/Component/That/Does/Not/Exist");
   std::time_t actual_write_time = component.last_write_time();
   ASSERT_EQ(0, actual_write_time);
}

