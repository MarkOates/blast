
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::UnorderedElementsAreArray;
using ::testing::Contains;

#include <Blast/Project/ComponentLister.hpp>

#include <Blast/Project/Component.hpp>

static std::string TEST_PROJECT_ROOT_DIRECTORY = "tests/fixtures/test_project/";
static std::string TEST_PROJECT_WITH_SYMLINK_ROOT_DIRECTORY = "tests/fixtures/FixtureProject2/";

TEST(Blast__Project__ComponentLister, can_be_created_without_arguments)
{
   Blast::Project::ComponentLister lister;
}

TEST(Blast__Project__ComponentLister, components__will_return_the_components_in_a_project)
{
   std::vector<std::string> expected_components = {
      "ComponentB",
      "ComponentWithExternalSymlink",
      "ComponentWithExternalSymlinkThatIsOnlySymlink",
      "Nested/ComponentC",
      "Nested/ComponentC2",
      "Nested/ComponentC3",
      "Nested/ComponentC4",
      "Nested/DoubleNested/ComponentD",
      "NotAppearingOutsideTest/ComponentX",
      "QuintessenceOnlyComponent",
   };

  Blast::Project::ComponentLister lister(TEST_PROJECT_ROOT_DIRECTORY);
  std::vector<std::string> actual_components = lister.components();

  ASSERT_EQ(expected_components, actual_components);
}

TEST(Blast__Project__ComponentLister, components__will_include_components_that_exist_purely_with_symlinked_fragments)
{
   std::string expected_purely_symlink_component = "ComponentWithExternalSymlinkThatIsOnlySymlink";

  Blast::Project::ComponentLister lister(TEST_PROJECT_WITH_SYMLINK_ROOT_DIRECTORY);
  std::vector<std::string> actual_components = lister.components();

  ASSERT_THAT(actual_components, Contains(expected_purely_symlink_component));
}

TEST(Blast__Project__ComponentLister,
  components_sorted_by_most_recent__will_return_the_components_sorted_by_most_recent)
{
   std::string project_directory = TEST_PROJECT_ROOT_DIRECTORY;
   std::vector<std::string> expected_contained_elements = {
      "ComponentB",
      "Nested/ComponentC",
      "Nested/ComponentC2",
      "Nested/ComponentC3",
      "Nested/ComponentC4",
      "Nested/DoubleNested/ComponentD",
      "NotAppearingOutsideTest/ComponentX",
      "QuintessenceOnlyComponent",
      "ComponentWithExternalSymlink",
      "ComponentWithExternalSymlinkThatIsOnlySymlink",
   };

   Blast::Project::ComponentLister lister(project_directory);
   std::vector<std::string> actual_elements = lister.components_sorted_by_most_recent();

   ASSERT_THAT(actual_elements, UnorderedElementsAreArray(expected_contained_elements));

   Blast::Project::Component first_component = Blast::Project::Component(actual_elements[0], project_directory);
   std::time_t previous_element_write_time = first_component.last_write_time();

   for (auto &element : actual_elements)
   {
      Blast::Project::Component component = Blast::Project::Component(element, project_directory);
      std::time_t write_time = component.last_write_time();
      EXPECT_LE(write_time, previous_element_write_time);
      previous_element_write_time = write_time;
   }
}


