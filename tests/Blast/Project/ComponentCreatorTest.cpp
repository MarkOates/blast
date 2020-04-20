
#include <gtest/gtest.h>

#include <Blast/Project/ComponentCreator.hpp>

TEST(Blast_Project_ComponentCreatorTest, can_be_created_without_blowing_up)
{
   Blast::Project::ComponentCreator component_creator;
}

TEST(Blast_Project_ComponentCreatorTest, get_quintessence_file_default_content__returns_the_expected_string)
{
std::string const expected_string = R"END(functions:
  - name: run
    type: std::string
    body: return "Hello World!";
)END";
   Blast::Project::ComponentCreator component_creator;
   EXPECT_EQ(expected_string, component_creator.get_quintessence_file_default_content());
}

TEST(Blast_Project_ComponentCreatorTest, generate__returns_the_expected_response)
{
   Blast::Project::ComponentCreator component_creator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, component_creator.generate());
}
