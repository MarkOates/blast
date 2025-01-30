
#include <gtest/gtest.h>

#include <Blast/Project/AssetUsageScanner.hpp>


TEST(Blast_Project_AssetUsageScannerTest, can_be_created_without_blowing_up)
{
   Blast::Project::AssetUsageScanner asset_usage_scanner;
}


// TODO: Uncomment these tests
TEST(Blast_Project_AssetUsageScannerTest, get_git_command__returns_the_expected_command)
{
   Blast::Project::AssetUsageScanner asset_usage_scanner;
   std::string expected_command = "(cd /Users/markoates/Repos/SomePlatformer && git grep --untracked --break \"asset_studio::\" \":(exclude)./documentation/*\" \":(exclude)./include/lib/*\" \":(exclude)./project_files/*\" \":(exclude)./tmp/*\" \":(exclude)./scripts/*\" \":(exclude)./tests/*\" )";
   EXPECT_EQ(expected_command, asset_usage_scanner.get_git_command());
}


// TODO: Update and uncomment this test
/*
TEST(Blast_Project_AssetUsageScannerTest,
   check_for_prefixed_assets__when_paths_are_detected__will_return_false_with_information_strings_when_assets_\
are_present)
{
   Blast::Project::AssetUsageScanner asset_usage_scanner;
   asset_usage_scanner.set_project_directory("/Users/markoates/Repos/SomePlatformer");
   std::pair<bool, std::vector<std::string>> expected_result = { false, { "foo" } }; // TODO: Use actual info
   std::pair<bool, std::vector<std::string>> actual_result = asset_usage_scanner.check_for_prefixed_assets();
   EXPECT_EQ(expected_result.first, actual_result.first);
   // TODO: Use this full assertion
   //EXPECT_EQ(expected_result, actual_result);
}

// TODO: Finish these 2 tests
TEST(Blast_Project_AssetUsageScannerTest,
   check_for_prefixed_assets__when_there_are_none__will_return_true_with_an_empty_strings)
{
   Blast::Project::HardCodedPathInfrencer hard_coded_path_infrencer;
   hard_coded_path_infrencer.set_project_directory(
      "/Users/markoates/Repos/blast/tests/fixtures/FixtureProject2"
   );
   std::pair<bool, std::vector<std::string>> expected_result = { true, { } }; // TODO: Have this be an empty set
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
*/


TEST(Blast_Project_AssetUsageScannerTest, extract_asset_studio_data__will_return_asset_studio_token_data)
{
   Blast::Project::AssetUsageScanner asset_usage_scanner;
   asset_usage_scanner.set_project_directory("/Users/markoates/Repos/FolderThatDoesNotExist");
   //asset_usage_scanner

   std::vector<std::string> input_lines = {
      R"(quintessence/AllegroFlare/Prototypes/Platforming2D/FXFactory.q.yml:         "asset_studio::ansimuz/warped-explosions-pack-8/explosion-g",)",
      R"(quintessence/JourneyOfTheCat/Gameplay/TMJObjectLoadCallback.q.yml:         //"asset_studio::ansimuz/gothicvania-cemetery/tree-3",)",
      R"(quintessence/JourneyOfTheCat/Gameplay/TMJObjectLoadCallback.q.yml:         { "tree-3", "asset_studio::ansimuz/gothicvania-cemetery/tree-3" },)",
      R"(quintessence/JourneyOfTheCat/Gameplay/TMJObjectLoadCallback.q.yml:         { "tree-2", "asset_studio::ansimuz/gothicvania-cemetery/tree-2" },)",
      R"(quintessence/JourneyOfTheCat/Gameplay/TMJObjectLoadCallback.q.yml:         { "tree-1", "asset_studio::ansimuz/gothicvania-cemetery/tree-1" },)",
      R"(quintessence/JourneyOfTheCat/Gameplay/TMJObjectLoadCallback.q.yml:         { "stone-1", "asset_studio::ansimuz/gothicvania-cemetery/stone-1" },)",
      R"(quintessence/JourneyOfTheCat/Gameplay/TMJObjectLoadCallback.q.yml:         { "stone-2", "asset_studio::ansimuz/gothicvania-cemetery/stone-2" },)",
      R"(quintessence/JourneyOfTheCat/Gameplay/TMJObjectLoadCallback.q.yml:         { "stone-3", "asset_studio::ansimuz/gothicvania-cemetery/stone-3" },)"
   };

   std::vector<std::pair<std::string, std::string>> expected_extracted_data = {
      { "asset_studio::ansimuz/warped-explosions-pack-8/explosion-g", "ansimuz/warped-explosions-pack-8/explosion-g" },
      { "asset_studio::ansimuz/gothicvania-cemetery/tree-3", "ansimuz/gothicvania-cemetery/tree-3" },
      { "asset_studio::ansimuz/gothicvania-cemetery/tree-3", "ansimuz/gothicvania-cemetery/tree-3" },
      { "asset_studio::ansimuz/gothicvania-cemetery/tree-2", "ansimuz/gothicvania-cemetery/tree-2" },
      { "asset_studio::ansimuz/gothicvania-cemetery/tree-1", "ansimuz/gothicvania-cemetery/tree-1" },
      { "asset_studio::ansimuz/gothicvania-cemetery/stone-1", "ansimuz/gothicvania-cemetery/stone-1" },
      { "asset_studio::ansimuz/gothicvania-cemetery/stone-2", "ansimuz/gothicvania-cemetery/stone-2" },
      { "asset_studio::ansimuz/gothicvania-cemetery/stone-3", "ansimuz/gothicvania-cemetery/stone-3" },
   };
   std::vector<std::pair<std::string, std::string>> actual_extracted_data =
      Blast::Project::AssetUsageScanner::extract_asset_studio_data(&input_lines);

   EXPECT_EQ(expected_extracted_data, actual_extracted_data);
}


