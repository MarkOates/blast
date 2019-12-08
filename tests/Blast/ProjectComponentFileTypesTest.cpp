

#include <gtest/gtest.h>

#include <Blast/ProjectComponentFileTypes.hpp>

#include <cmath>


TEST(Blast_ProjectComponentFileTypesTest, get_project_file_type_str__retuns_the_corresponding_name_for_the_file_type)
{
   std::vector<std::pair<std::string, Blast::ProjectComponentFileTypes::project_file_type_t>> test_data = {
      { "quintessence file", Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE },
      { "source file", Blast::ProjectComponentFileTypes::SOURCE_FILE },
      { "header file", Blast::ProjectComponentFileTypes::HEADER_FILE },
      { "test file", Blast::ProjectComponentFileTypes::TEST_FILE },
      { "example file", Blast::ProjectComponentFileTypes::EXAMPLE_FILE },
      { "object file", Blast::ProjectComponentFileTypes::OBJECT_FILE },
      { "test binary", Blast::ProjectComponentFileTypes::TEST_BINARY },
      { "example binary", Blast::ProjectComponentFileTypes::EXAMPLE_BINARY },
      { "not identifiable", Blast::ProjectComponentFileTypes::NOT_IDENTIFIABLE },
   };

   for (auto test_data : test_data)
      ASSERT_EQ(test_data.first, Blast::ProjectComponentFileTypes::get_project_file_type_str(test_data.second));
}


