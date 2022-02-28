

#include <gtest/gtest.h>

#include <Blast/ProjectComponentFilenameGenerator.hpp>

#include <cmath>


TEST(ProjectComponentFilenameGeneratorTest, can_be_created)
{
   Blast::ProjectComponentFilenameGenerator project_component_filename_generator;
}


TEST(ProjectComponentFilenameGeneratorTest, when_created_is_initialized_with_the_expected_default_values)
{
   Blast::ProjectComponentFilenameGenerator project_component_filename_generator;

   ASSERT_EQ("", project_component_filename_generator.get_basename());
   ASSERT_EQ(false, project_component_filename_generator.get_use_underscores());
   ASSERT_EQ(Blast::ProjectComponentFileTypes::SOURCE_FILE, project_component_filename_generator.get_project_file_type());
}


TEST(ProjectComponentFilenameGeneratorTest, can_get_and_set_the_basename)
{
   Blast::ProjectComponentFilenameGenerator project_component_filename_generator;
   project_component_filename_generator.set_basename("models/Foobar");
   ASSERT_EQ("models/Foobar", project_component_filename_generator.get_basename());
}


TEST(ProjectComponentFilenameGeneratorTest, can_get_and_set_to_use_underscores)
{
   Blast::ProjectComponentFilenameGenerator project_component_filename_generator;

   project_component_filename_generator.set_use_underscores(true);
   ASSERT_EQ(true, project_component_filename_generator.get_use_underscores());
   project_component_filename_generator.set_use_underscores(false);
   ASSERT_EQ(false, project_component_filename_generator.get_use_underscores());
}


TEST(ProjectComponentFilenameGeneratorTest, can_get_and_set_the_project_file_type)
{
   Blast::ProjectComponentFilenameGenerator project_component_filename_generator;

   project_component_filename_generator.set_project_file_type(Blast::ProjectComponentFileTypes::TEST_FILE);
   ASSERT_EQ(Blast::ProjectComponentFileTypes::TEST_FILE, project_component_filename_generator.get_project_file_type());
   project_component_filename_generator.set_project_file_type(Blast::ProjectComponentFileTypes::SOURCE_FILE);
   Blast::ProjectComponentFileTypes::project_file_type_t expected_project_file_type =
      Blast::ProjectComponentFileTypes::SOURCE_FILE;
   Blast::ProjectComponentFileTypes::project_file_type_t actual_project_file_type =
      project_component_filename_generator.get_project_file_type();
   ASSERT_EQ(Blast::ProjectComponentFileTypes::SOURCE_FILE, actual_project_file_type);
}


TEST(ProjectComponentFilenameGeneratorTest,
   generate_filename__generates_the_expected_filename_in_the_correct_format_with_camelcase)
{
   std::string basename = "models/Foobar";

   std::vector<std::pair<Blast::ProjectComponentFileTypes::project_file_type_t, std::string>> test_data = {
      { Blast::ProjectComponentFileTypes::SOURCE_FILE, "src/models/Foobar.cpp" },
      { Blast::ProjectComponentFileTypes::HEADER_FILE, "include/models/Foobar.hpp" },
      { Blast::ProjectComponentFileTypes::TEST_FILE, "tests/models/FoobarTest.cpp" },
      { Blast::ProjectComponentFileTypes::EXAMPLE_FILE, "examples/models/FoobarExample.cpp" },
      { Blast::ProjectComponentFileTypes::OBJECT_FILE, "obj/models/Foobar.o" },
      { Blast::ProjectComponentFileTypes::TEST_BINARY, "bin/tests/models/FoobarTest" },
      { Blast::ProjectComponentFileTypes::EXAMPLE_BINARY, "bin/examples/models/FoobarExample" },
      { Blast::ProjectComponentFileTypes::DOCUMENTATION_FILE, "docs/models/Foobar.md" },
      { Blast::ProjectComponentFileTypes::NOT_IDENTIFIABLE, "" },
   };

   for (auto test_data : test_data)
   {
      Blast::ProjectComponentFilenameGenerator project_component_filename_generator(basename, test_data.first);
      ASSERT_EQ(test_data.second, project_component_filename_generator.generate_filename());
   }
}


TEST(ProjectComponentFilenameGeneratorTest,
   generate_filename__generates_the_expected_filename_in_the_correct_format_with_underscores)
{
   std::string basename = "models/foobar";

   std::vector<std::pair<Blast::ProjectComponentFileTypes::project_file_type_t, std::string>> test_data = {
      { Blast::ProjectComponentFileTypes::SOURCE_FILE, "src/models/foobar.cpp" },
      { Blast::ProjectComponentFileTypes::HEADER_FILE, "include/models/foobar.hpp" },
      { Blast::ProjectComponentFileTypes::TEST_FILE, "tests/models/foobar_test.cpp" },
      { Blast::ProjectComponentFileTypes::EXAMPLE_FILE, "examples/models/foobar_example.cpp" },
      { Blast::ProjectComponentFileTypes::OBJECT_FILE, "obj/models/foobar.o" },
      { Blast::ProjectComponentFileTypes::TEST_BINARY, "bin/tests/models/foobar_test" },
      { Blast::ProjectComponentFileTypes::EXAMPLE_BINARY, "bin/examples/models/foobar_example" },
      { Blast::ProjectComponentFileTypes::DOCUMENTATION_FILE, "docs/models/foobar.md" },
      { Blast::ProjectComponentFileTypes::NOT_IDENTIFIABLE, "" },
   };

   for (auto test_data : test_data)
   {
      Blast::ProjectComponentFilenameGenerator project_component_filename_generator(basename, test_data.first, true);
      ASSERT_EQ(test_data.second, project_component_filename_generator.generate_filename());
   }
}


