
#include <gtest/gtest.h>

#include <Blast/Project/Component.hpp>

TEST(Blast_Project_ComponentTest, can_be_created_without_blowing_up)
{
   Blast::Project::Component component;
}

TEST(Blast_Project_ComponentTest, run__returns_the_expected_response)
{
   Blast::Project::Component component;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, component.run());
}
