
#include <gtest/gtest.h>

#include <Blast/TemplatedFile.hpp>

TEST(Blast_TemplatedFileTest, can_be_created_without_blowing_up)
{
   Blast::TemplatedFile templated_file;
}

TEST(Blast_TemplatedFileTest, generate_content__when_object_is_created_with_default_arguments__returns_the_expected_filled_content)
{
   Blast::TemplatedFile templated_file;
   std::string expected_string = "Hello, World!";
   EXPECT_EQ(expected_string, templated_file.generate_content());
}

TEST(Blast_TemplatedFileTest, generate_content__returns_the_expected_filled_content)
{
   std::string TEMPLATE_CONTENT = R"END(#include <gtest/gtest.h>

#include <[[COMPONENT_HEADER_INCLUDE_FILE_PATH]]>

TEST([[COMPONENT_TEST_DESCRIPTION_NAME]], can_be_created_without_blowing_up)
{
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
}

TEST([[COMPONENT_TEST_DESCRIPTION_NAME]], run__returns_the_expected_response)
{
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, [[COMPONENT_BASENAME_SNAKE_CASE]].run());
})END";

   std::vector<std::pair<std::string, std::string>> insertion_variables = {
      { "[[COMPONENT_HEADER_INCLUDE_FILE_PATH]]", "Blast/ComponentName.hpp" },
      { "[[COMPONENT_TEST_DESCRIPTION_NAME]]", "Blast_ComponentNameTest" },
      { "[[COMPONENT_CLASS_NAME]]", "Blast::ComponentName" },
      { "[[COMPONENT_BASENAME_SNAKE_CASE]]", "component_name" },
   };

   Blast::TemplatedFile templated_file(TEMPLATE_CONTENT, insertion_variables);

   std::string expected_string = R"END(#include <gtest/gtest.h>

#include <Blast/ComponentName.hpp>

TEST(Blast_ComponentNameTest, can_be_created_without_blowing_up)
{
   Blast::ComponentName component_name;
}

TEST(Blast_ComponentNameTest, run__returns_the_expected_response)
{
   Blast::ComponentName component_name;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, component_name.run());
})END";

   EXPECT_EQ(expected_string, templated_file.generate_content());
}

