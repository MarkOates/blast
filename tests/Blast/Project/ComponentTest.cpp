
#include <gtest/gtest.h>

#include <Blast/Project/Component.hpp>


#include <filesystem>
static std::string ABSOLUTE_PATH(std::string relative_path) { return std::filesystem::absolute(relative_path).string(); }
static const std::string RELATIVE_FIXTURE_PATH = "tests/fixtures/FixtureProject2/";


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
   std::string expected_full_path_test_binary_filename =
      "/Users/markoates/Repos/hexagon/bin/tests/Hexagon/FoobarComponentTest";
   ASSERT_EQ(expected_full_path_test_binary_filename, component.generate_full_path_test_binary_filename());
}


TEST(Blast_Project_ComponentTest, list_existing_component_files__returns_a_list_of_all_existing_component_files)
{
   Blast::Project::Component component("Blast/Project/Component");
   std::vector<std::string> expected_list = {
      "quintessence/Blast/Project/Component.q.yml",
      "src/Blast/Project/Component.cpp",
      "include/Blast/Project/Component.hpp",
      "tests/Blast/Project/ComponentTest.cpp",
      "docs/Blast/Project/Component.md",
   };
   ASSERT_EQ(expected_list, component.list_existing_component_files());
}


TEST(Blast_Project_ComponentTest,
   list_exiting_component_files__with_a_project_root_returns_a_list_of_all_existing_component_files)
{
   std::string project_root = "../hexagon/";
   Blast::Project::Component component("Blast/Project/Component", project_root);
   std::vector<std::string> expected_list = {
      "../hexagon/quintessence/Blast/Project/Component.q.yml",
      "../hexagon/src/Blast/Project/Component.cpp",
      "../hexagon/include/Blast/Project/Component.hpp",
   };
   ASSERT_EQ(expected_list, component.list_existing_component_files());
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


TEST(Blast_Project_ComponentTest,
   has_only_source_and_header__returns_true_when_the_source_and_header_files_are_present_and_a_quintessence_file_does_not_exist)
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
   std::string fixture_project_path = ABSOLUTE_PATH(RELATIVE_FIXTURE_PATH);
   Blast::Project::Component component("ComponentWithoutTestFile", fixture_project_path);
   EXPECT_EQ(true, component.exists());
   ASSERT_EQ(false, component.has_test());
}


TEST(Blast_Project_ComponentTest, has_documentation__returns_true_when_a_documentation_file_is_present)
{
   std::string fixture_project_path = ABSOLUTE_PATH(RELATIVE_FIXTURE_PATH);
   Blast::Project::Component component("Foobar/ComponentWithDocumentationFile", fixture_project_path);
   ASSERT_EQ(true, component.has_documentation());
}


TEST(Blast_Project_ComponentTest, has_documentation__returns_false_when_a_documentation_file_does_not_exist)
{
   std::string fixture_project_path = ABSOLUTE_PATH(RELATIVE_FIXTURE_PATH);
   Blast::Project::Component component("ComponentWithoutDocumentationFile", fixture_project_path);
   EXPECT_EQ(true, component.exists());
   ASSERT_EQ(false, component.has_documentation());
}


TEST(Blast_Project_ComponentTest, read_symlinks__returns_a_list_of_component_files_that_are_symlinks_and_their_targets)
{
   Blast::Project::Component component("ComponentWithExternalSymlink", RELATIVE_FIXTURE_PATH);
   std::string expected_symlink_target = "../../test_project/quintessence/ComponentWithExternalSymlink.q.yml";

   std::vector<std::pair<std::string, std::string>> expected = {
      {
         "tests/fixtures/FixtureProject2/quintessence/ComponentWithExternalSymlink.q.yml",
         "../../test_project/quintessence/ComponentWithExternalSymlink.q.yml",
      }
   };
   std::vector<std::pair<std::string, std::string>> actual = component.read_symlinks();

   ASSERT_EQ(expected, actual);
}


TEST(Blast_Project_ComponentTest, last_write_time__returns_the_most_recent_write_time_among_all_of_the_component_files)
{
   Blast::Project::Component component("Blast/StringSplitter");
   std::time_t actual_last_write_time = component.last_write_time();
   ASSERT_GT(actual_last_write_time, 0);

   // sanity test
   std::time_t a_sane_last_write_time = 1580169020;
   ASSERT_GT(actual_last_write_time, a_sane_last_write_time);
}


TEST(Blast_Project_ComponentTest, last_write_time__returns_0_when_the_component_does_not_exist)
{
   Blast::Project::Component component("Blast/Component/That/Does/Not/Exist");
   ASSERT_FALSE(component.exists());
   std::time_t actual_write_time = component.last_write_time();
   ASSERT_EQ(0, actual_write_time);
}


TEST(Blast_Project_ComponentTest,
   check_fragment_file_last_write_time__will_return_the_last_write_time_of_the_fragment_file)
{
}


TEST(Blast_Project_ComponentTest,
   check_fragment_file_last_write_time__returns_0_when_a_file_does_not_exist_for_that_fragment)
{
   Blast::Project::Component component("Blast/Component/That/Does/Not/Exist");
   ASSERT_FALSE(component.exists());
   std::time_t actual_write_time = component.check_fragment_file_last_write_time();
   ASSERT_EQ(0, actual_write_time);
}


