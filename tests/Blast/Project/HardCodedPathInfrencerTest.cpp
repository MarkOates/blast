
#include <gtest/gtest.h>

#include <Blast/Project/HardCodedPathInfrencer.hpp>


TEST(Blast_Project_HardCodedPathInfrencerTest, can_be_created_without_blowing_up)
{
   Blast::Project::HardCodedPathInfrencer hard_coded_path_infrencer;
}


TEST(Blast_Project_HardCodedPathInfrencerTest, DISABLED__run__returns_the_expected_response)
{
   Blast::Project::HardCodedPathInfrencer hard_coded_path_infrencer;
   hard_coded_path_infrencer.set_project_directory("/Users/markoates/Repos/Pipeline");
   std::pair<bool, std::vector<std::string>> expected_result = { false, { "foo" } };
   std::pair<bool, std::vector<std::string>> actual_result = hard_coded_path_infrencer.check_for_hard_coded_paths();
   EXPECT_EQ(expected_result, actual_result);
}


TEST(Blast_Project_HardCodedPathInfrencerTest,
   DISABLED__check_for_hard_coded_paths__when_there_are_none__will_return_true)
{
   // TODO: Thi stest
   Blast::Project::HardCodedPathInfrencer hard_coded_path_infrencer;
   hard_coded_path_infrencer.set_project_directory(
      "/Users/markoates/Repos/blast/tests/fixtures/FixtureProject2"
   );
   std::pair<bool, std::vector<std::string>> expected_result = { true, { "foo" } };
   std::pair<bool, std::vector<std::string>> actual_result = hard_coded_path_infrencer.check_for_hard_coded_paths();
   EXPECT_EQ(expected_result, actual_result);
}


TEST(Blast_Project_HardCodedPathInfrencerTest,
   DISABLED__check_for_hard_coded_paths__on_a_folder_that_does_not_exist__throws_an_error)
{
   // TODO: This test
   Blast::Project::HardCodedPathInfrencer hard_coded_path_infrencer;
   hard_coded_path_infrencer.set_project_directory("/Users/markoates/Repos/FolderThatDoesNotExist");
}


