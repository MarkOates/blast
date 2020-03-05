
#include <gtest/gtest.h>

#include <Blast/Project/ComponentLister.hpp>

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
   std::vector<std::string> expected_sorted_components = {
      "ComponentB",
      "Nested/ComponentC",
      "NotAppearingOutsideTest/ComponentX",
      "QuintessenceOnlyComponent",
      "ComponentWithExternalSymlink",
   };

   Blast::Project::ComponentLister lister("bin/fixtures/test_project/");
   std::vector<std::string> actual_sorted_components = lister.components_sorted_by_most_recent();

   ASSERT_EQ(expected_sorted_components, actual_sorted_components);
}


