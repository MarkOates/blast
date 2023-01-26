

#include <gtest/gtest.h>

#include <Blast/ProjectComponentBasenameExtractor.hpp>

#include <cmath>


TEST(ProjectComponentBasenameExtractorTest, can_be_created)
{
   Blast::ProjectComponentBasenameExtractor project_component_basename_extractor;
}


TEST(ProjectComponentBasenameExtractorTest, when_created_is_initialized_with_the_expected_default_values)
{
   Blast::ProjectComponentBasenameExtractor project_component_basename_extractor;
   ASSERT_EQ("", project_component_basename_extractor.get_filename());
}


TEST(ProjectComponentBasenameExtractorTest, can_get_and_set_the_filename)
{
   Blast::ProjectComponentBasenameExtractor project_component_basename_extractor;
   project_component_basename_extractor.set_filename("src/models/Foobar.cpp");
   ASSERT_EQ("src/models/Foobar.cpp", project_component_basename_extractor.get_filename());
}


TEST(ProjectComponentBasenameExtractorTest, get_project_file_type__identifies_the_project_component_type_of_the_filename)
{
   std::vector<std::pair<Blast::ProjectComponentFileTypes::project_file_type_t, std::string>> test_data = {
      { Blast::ProjectComponentFileTypes::SOURCE_FILE, "src/models/Foobar.cpp" },
      { Blast::ProjectComponentFileTypes::HEADER_FILE, "include/models/Foobar.hpp" },
      { Blast::ProjectComponentFileTypes::TEST_SOURCE_FILE, "tests/models/FoobarTest.cpp" },
      { Blast::ProjectComponentFileTypes::EXAMPLE_SOURCE_FILE, "examples/models/FoobarExample.cpp" },
      { Blast::ProjectComponentFileTypes::OBJECT_FILE, "obj/models/Foobar.o" },
      { Blast::ProjectComponentFileTypes::TEST_EXECUTABLE_FILE, "bin/tests/models/FoobarTest" },
      { Blast::ProjectComponentFileTypes::EXAMPLE_EXECUTABLE_FILE, "bin/examples/models/FoobarExample" },
      { Blast::ProjectComponentFileTypes::NOT_IDENTIFIABLE, "not_project_file.txt" },
   };

   for (auto test_data : test_data)
   {
      Blast::ProjectComponentBasenameExtractor project_component_basename_extractor(test_data.second);
      ASSERT_EQ(test_data.first, project_component_basename_extractor.get_project_file_type());
   }
}


TEST(ProjectComponentBasenameExtractorTest, get_component_basename__returns_the_basename_extracted_from_the_filename)
{
   std::vector<std::pair<std::string, std::string>> test_data = {
      { "models/Foobar", "src/models/Foobar.cpp" },
      { "models/Foobar", "include/models/Foobar.hpp" },
      { "models/Foobar", "tests/models/FoobarTest.cpp" },
      { "models/Foobar", "examples/models/FoobarExample.cpp" },
      { "models/Foobar", "obj/models/Foobar.o" },
      { "models/Foobar", "bin/tests/models/FoobarTest" },
      { "models/Foobar", "bin/examples/models/FoobarExample" },
      // also works with snakecase convention
      { "models/foobar", "tests/models/foobar_test.cpp" },
      { "models/foobar", "examples/models/foobar_example.cpp" },
      { "models/foobar", "obj/models/foobar.o" },
      { "models/foobar", "bin/tests/models/foobar_test" },
      { "models/foobar", "bin/examples/models/foobar_example" },
   };

   for (auto test_data : test_data)
   {
      Blast::ProjectComponentBasenameExtractor project_component_basename_extractor(test_data.second);
      ASSERT_EQ(test_data.first, project_component_basename_extractor.get_component_basename());
   }
}


TEST(ProjectComponentBasenameExtractorTest, get_component_basename__returns_an_empty_string_when_basename_cannot_be_extracted)
{
   Blast::ProjectComponentBasenameExtractor project_component_basename_extractor("not_a_project_componet_file.txt");
   ASSERT_EQ("", project_component_basename_extractor.get_component_basename());
}


