
#include <gtest/gtest.h>

#include <Blast/Project/ComponentRelativeLister.hpp>

TEST(Blast_Project_ComponentRelativeListerTest, can_be_created_without_blowing_up)
{
   Blast::Project::ComponentRelativeLister component_relative_lister;
}

TEST(Blast_Project_ComponentRelativeListerTest, list_component_relatives__returns_the_expected_response)
{
   Blast::Project::ComponentRelativeLister component_relative_lister;
   std::vector<std::string> expected_component_relative_names;
   std::vector<std::string> actual_component_relative_names =
      component_relative_lister.list_component_relative_names();
   ASSERT_EQ(expected_component_relative_names, actual_component_relative_names);
}
