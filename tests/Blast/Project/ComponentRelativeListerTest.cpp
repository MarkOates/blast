
#include <gtest/gtest.h>

#include <Blast/Project/ComponentRelativeLister.hpp>

TEST(Blast_Project_ComponentRelativeListerTest, can_be_created_without_blowing_up)
{
   Blast::Project::ComponentRelativeLister component_relative_lister;
}

TEST(Blast_Project_ComponentRelativeListerTest, run__returns_the_expected_response)
{
   Blast::Project::ComponentRelativeLister component_relative_lister;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, component_relative_lister.run());
}
