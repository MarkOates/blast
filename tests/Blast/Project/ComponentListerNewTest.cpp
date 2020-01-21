
#include <gtest/gtest.h>

#include <Blast/Project/ComponentListerNew.hpp>

TEST(Blast_Project_ComponentListerNewTest, can_be_created_without_blowing_up)
{
   Blast::Project::ComponentListerNew component_lister;
}

TEST(Blast_Project_ComponentListerNewTest, components__returns_the_expected_values)
{
   Blast::Project::ComponentListerNew component_lister;
   std::vector<std::string> expected = {};
   EXPECT_EQ(expected, component_lister.components());
}

