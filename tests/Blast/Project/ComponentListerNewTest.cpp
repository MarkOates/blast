
#include <gtest/gtest.h>

#include <Blast/Project/ComponentListerNew.hpp>

TEST(Blast_Project_ComponentListerNewTest, can_be_created_without_blowing_up)
{
   Blast::Project::ComponentListerNew component_lister;
}

TEST(Blast_Project_ComponentListerNewTest, run__returns_the_expected_response)
{
   Blast::Project::ComponentListerNew component_lister;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, component_lister.run());
}
