
#include <gtest/gtest.h>

#include <Blast/Project/Component.hpp>

TEST(Blast_Project_ComponentTest, can_be_created_without_blowing_up)
{
   Blast::Project::Component component;
}

TEST(Blast_Project_ComponentTest, run__has_the_expected_defaults)
{
   Blast::Project::Component component;
   std::string expected_component_name = "Unnamed/Component";
   ASSERT_EQ(expected_component_name, component.get_name());
}
