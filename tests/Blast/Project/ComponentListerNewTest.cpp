
#include <gtest/gtest.h>

#include <Blast/Project/ComponentListerNew.hpp>

TEST(Blast_Project_ComponentListerNewTest, can_be_created_without_blowing_up)
{
   Blast::Project::ComponentListerNew component_lister;
}

TEST(Blast_Project_ComponentListerNewTest, components__returns_the_expected_values_when_no_arguments_are_given)
{
   Blast::Project::ComponentListerNew component_lister;
   std::vector<std::string> expected = {};
   EXPECT_EQ(expected, component_lister.components());
}

TEST(Blast_Project_ComponentListerNewTest, components__returns_the_expected_values)
{
   std::vector<std::string> expected_components = {
      "ComponentB",
      //"ComponentWithExternalSymlink",
      "Nested/ComponentC",
      "NotAppearingOutsideTest/ComponentX",
      "QuintessenceOnlyComponent",
   };

   Blast::Project::ComponentListerNew lister("bin/fixtures/test_project/");
   std::vector<std::string> actual_components = lister.components();

   ASSERT_EQ(expected_components, actual_components);
}

