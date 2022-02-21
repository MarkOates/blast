
#include <gtest/gtest.h>

#include <Blast/Project/ComponentDependencyLister.hpp>

TEST(Blast_Project_ComponentDependencyListerTest, can_be_created_without_blowing_up)
{
   Blast::Project::ComponentDependencyLister component_dependency_lister;
}

TEST(Blast_Project_ComponentDependencyListerTest, run__returns_the_expected_response)
{
   Blast::Project::ComponentDependencyLister component_dependency_lister;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, component_dependency_lister.run());
}
