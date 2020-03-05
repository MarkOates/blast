
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::UnorderedElementsAreArray;

#include <Blast/Project/ComponentLister.hpp>

#include <Blast/Project/Component.hpp>

TEST(Blast__Project__ComponentLister, can_be_created_without_arguments)
{
   Blast::Project::ComponentLister lister;
}

TEST(Blast__Project__ComponentLister, will_return_the_components_in_a_project)
{
   std::vector<std::string> expected_components = {
      "ComponentB",
      "ComponentWithExternalSymlink",
      "Nested/ComponentC",
      "NotAppearingOutsideTest/ComponentX",
      "QuintessenceOnlyComponent",
   };

  Blast::Project::ComponentLister lister("bin/fixtures/test_project/");
  std::vector<std::string> actual_components = lister.components();

  ASSERT_EQ(expected_components, actual_components);
}

TEST(Blast__Project__ComponentLister,
  components_sorted_by_most_recent__will_return_the_components_sorted_by_most_recent)
{
   std::vector<std::string> expected_contained_elements = {
      "ComponentB",
      "Nested/ComponentC",
      "NotAppearingOutsideTest/ComponentX",
      "QuintessenceOnlyComponent",
      "ComponentWithExternalSymlink",
   };

   Blast::Project::ComponentLister lister("bin/fixtures/test_project/");
   std::vector<std::string> actual_elements = lister.components_sorted_by_most_recent();

   ASSERT_THAT(actual_elements, UnorderedElementsAreArray(expected_contained_elements));

   std::time_t last_time = 0;

   for (auto &element : actual_elements)
   {
      Blast::Project::Component component = Blast::Project::Component(element, "bin/fixtures/test_project/");
      std::time_t write_time = component.last_write_time();
      EXPECT_GE(write_time, last_time);
      last_time = write_time;
   }
}


