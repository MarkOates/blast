
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


