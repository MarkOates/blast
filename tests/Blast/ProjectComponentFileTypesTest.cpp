

#include <gtest/gtest.h>

#include <Blast/ProjectComponentFileTypes.hpp>

#include <cmath>


TEST(Blast_ProjectComponentFileTypesTest, get_project_file_type_str__retuns_the_corresponding_name_for_the_file_type)
{
   std::vector<std::pair<std::string, Blast::ProjectComponentFileTypes::project_file_type_t>> test_data = {
      { "quintessence file", Blast::ProjectComponentFileTypes::QUINTESSENCE_FILE },
      { "source file", Blast::ProjectComponentFileTypes::SOURCE_FILE },
      { "header file", Blast::ProjectComponentFileTypes::HEADER_FILE },
      { "test source file", Blast::ProjectComponentFileTypes::TEST_SOURCE_FILE },
      { "example source file", Blast::ProjectComponentFileTypes::EXAMPLE_SOURCE_FILE },
      { "object file", Blast::ProjectComponentFileTypes::OBJECT_FILE },
      { "test object file", Blast::ProjectComponentFileTypes::TEST_OBJECT_FILE},
      { "test executable file", Blast::ProjectComponentFileTypes::TEST_EXECUTABLE_FILE},
      { "example executable file", Blast::ProjectComponentFileTypes::EXAMPLE_EXECUTABLE_FILE },
      { "example object file", Blast::ProjectComponentFileTypes::EXAMPLE_OBJECT_FILE },
      { "example source file", Blast::ProjectComponentFileTypes::EXAMPLE_SOURCE_FILE },
      { "documentation file", Blast::ProjectComponentFileTypes::DOCUMENTATION_FILE },
      { "not identifiable", Blast::ProjectComponentFileTypes::NOT_IDENTIFIABLE },
   };

   for (auto test_data : test_data)
   {
      EXPECT_EQ(test_data.first, Blast::ProjectComponentFileTypes::get_project_file_type_str(test_data.second));
   }
}


TEST(Blast_ProjectComponentFileTypesTest, DISABLED__get_project_file_type_str__on_an_invlaid_type__will_throw_an_error)
{
   // TODO
}


