
#include <gtest/gtest.h>

#include <Blast/Project/CodeUsageScanner.hpp>


TEST(Blast_Project_CodeUsageScannerTest, can_be_created_without_blowing_up)
{
   Blast::Project::CodeUsageScanner code_usage_scanner;
}


TEST(Blast_Project_CodeUsageScannerTest, DISABLED__build_scan_shell_command__returns_the_expected_command)
{
   Blast::Project::CodeUsageScanner code_usage_scanner;
   //code_usage_scanner.set_search_token("foo");
   std::string expected_command = "(cd /Users/markoates/Repos/SomePlatformer && git grep --untracked --break \"foo\" \":(exclude)./documentation/*\" \":(exclude)./include/lib/*\" \":(exclude)./project_files/*\" \":(exclude)./tmp/*\" \":(exclude)./scripts/*\" \":(exclude)./tests/*\" )";
   EXPECT_EQ(expected_command, code_usage_scanner.build_scan_shell_command("foo"));
}


TEST(Blast_Project_CodeUsageScannerTest, build_report__will_output_a_report_of_found_tokens)
{
   Blast::Project::CodeUsageScanner code_usage_scanner("/Users/markoates/Repos/JourneyOfTheCat");
   //code_usage_scanner.set_search_token("foo");
   //std::string expected_command = "(cd /Users/markoates/Repos/SomePlatformer && git grep --untracked --break \"foo\" \":(exclude)./documentation/*\" \":(exclude)./include/lib/*\" \":(exclude)./project_files/*\" \":(exclude)./tmp/*\" \":(exclude)./scripts/*\" \":(exclude)./tests/*\" )";
   std::string expected_report = "asdfofa";
   bool all_clear;
   std::string actual_report;
   std::tie(all_clear, actual_report) = code_usage_scanner.build_report();

   //EXPECT_EQ(true, all_clear);
   //EXPECT_EQ(expected_report, actual_report);
}


TEST(Blast_Project_CodeUsageScannerTest, token_exists_in_file__will_return_true_if_token_is_found_in_file)
{
   Blast::Project::CodeUsageScanner code_usage_scanner("/Users/markoates/Repos/JourneyOfTheCat");
   bool token_exists_in_file = code_usage_scanner.token_exists_in_file(
      "src/JourneyOfTheCat/Entities/Ghost.cpp",
      "#include <cmath>"
   );
   EXPECT_EQ(true, token_exists_in_file);
}




// TODO: Update and uncomment this test
/*
TEST(Blast_Project_CodeUsageScannerTest,
   check_for_prefixed_assets__when_paths_are_detected__will_return_false_with_information_strings_when_assets_\
are_present)
{
   Blast::Project::CodeUsageScanner code_usage_scanner;
   code_usage_scanner.set_project_directory("/Users/markoates/Repos/SomePlatformer");
   std::pair<bool, std::vector<std::string>> expected_result = { false, { "foo" } }; // TODO: Use actual info
   std::pair<bool, std::vector<std::string>> actual_result = code_usage_scanner.check_for_prefixed_assets();
   EXPECT_EQ(expected_result.first, actual_result.first);
   // TODO: Use this full assertion
   //EXPECT_EQ(expected_result, actual_result);
}

// TODO: Finish these 2 tests
TEST(Blast_Project_CodeUsageScannerTest,
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


TEST(Blast_Project_CodeUsageScannerTest, extract_code_studio_data__will_return_code_studio_token_data)
{
   Blast::Project::CodeUsageScanner code_usage_scanner;
   code_usage_scanner.set_project_directory("/Users/markoates/Repos/FolderThatDoesNotExist");
   //code_usage_scanner

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
      Blast::Project::CodeUsageScanner::extract_code_studio_data(&input_lines);

   EXPECT_EQ(expected_extracted_data, actual_extracted_data);
}


/*
TEST(Blast_Project_CodeUsageScannerTest, build_comma_separated_unique_code_identifier_list__will_do_that)
{
   Blast::Project::CodeUsageScanner code_usage_scanner;
   code_usage_scanner.set_project_directory("/Users/markoates/Repos/FolderThatDoesNotExist");

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

   std::vector<std::pair<std::string, std::string>> code_studio_data =
      code_usage_scanner.extract_code_studio_data(&input_lines);

   //std::string expected_result_string = R"("ansimuz/warped-explosions-pack-8/explosion-g" "ansimuz/gothicvania-cemetery/tree-3" "ansimuz/gothicvania-cemetery/tree-3" "ansimuz/gothicvania-cemetery/tree-2" "ansimuz/gothicvania-cemetery/tree-1" "ansimuz/gothicvania-cemetery/stone-1" "ansimuz/gothicvania-cemetery/stone-2" "ansimuz/gothicvania-cemetery/stone-3")";
   std::string expected_result_string = "\"ansimuz/gothicvania-cemetery/stone-1\" \"ansimuz/gothicvania-cemetery"
      "/stone-2\" \"ansimuz/gothicvania-cemetery/stone-3\" \"ansimuz/gothicvania-cemetery/tree-1\" \"ansimuz/"
      "gothicvania-cemetery/tree-2\" \"ansimuz/gothicvania-cemetery/tree-3\" \"ansimuz/warped-explosions-pack-8/"
      "explosion-g\"";

   std::string actual_result_string =
      code_usage_scanner.build_comma_separated_unique_code_identifier_list(&code_studio_data);

   EXPECT_EQ(expected_result_string, actual_result_string);
}
*/


