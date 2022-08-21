
#include <gtest/gtest.h>

#include <Blast/Project/ProjectSymlinkFixer.hpp>

#include <Blast/Project/SymlinkChecker.hpp>


#include <filesystem>

#define TEMP_SANDBOX_FOLDER ("tmp/test_sandbox")
#define LIKELY_SYMLINK_TEST_FILE "/Users/markoates/Repos/blast/bin/fixtures/FixtureProject2/quintessence/ComponentWithExternalSymlink.q.yml";



#include <fstream>
void write_file(std::string filename, std::string contents)
{
   std::ofstream myfile;
   myfile.open(filename);
   myfile << contents;
   myfile.close();
}



TEST(Blast_Project_ProjectSymlinkFixerTest, can_be_created_without_blowing_up)
{
   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
}



TEST(Blast_Project_ProjectSymlinkFixerTest, project_folder__has_getter_and_is_set_with_the_expected_default_value)
{
   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
   std::string expected_default_directory = ".";
   ASSERT_EQ(expected_default_directory, project_symlink_fixer.get_project_folder());
}



TEST(Blast_Project_ProjectSymlinkFixerTest,
   likely_an_intended_symlink__returns_true_if_the_file_is_actually_a_symlink)
{
   std::string filename_of_file_that_is_symlink = LIKELY_SYMLINK_TEST_FILE;
   ASSERT_EQ(true, std::filesystem::exists(filename_of_file_that_is_symlink));
   Blast::Project::SymlinkChecker checker(filename_of_file_that_is_symlink);
   ASSERT_EQ(true, checker.is_symlink());

   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
   ASSERT_EQ(true, project_symlink_fixer.likely_an_intended_symlink(filename_of_file_that_is_symlink));
}



TEST(DISABLED_Blast_Project_ProjectSymlinkFixerTest,
   likely_an_intended_symlink__returns_true_if_the_file_is_not_a_symlink_but_likely_intended_to_be_a_symlink__test1)
{
   std::filesystem::create_directories(TEMP_SANDBOX_FOLDER);

   std::string filename = "./" + std::string(TEMP_SANDBOX_FOLDER) + "/" + "almost_a_symlink__test1_file";
   std::string file_contents = "../something/Something";
   ::write_file(filename, file_contents);
   ASSERT_EQ(true, std::filesystem::exists(filename));

   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
   EXPECT_EQ(true, project_symlink_fixer.likely_an_intended_symlink(filename));

   std::filesystem::remove_all(TEMP_SANDBOX_FOLDER);
}



TEST(DISABLED_Blast_Project_ProjectSymlinkFixerTest,
   likely_an_intended_symlink__returns_true_if_the_file_is_not_a_symlink_but_likely_intended_to_be_a_symlink__test2)
{
   std::filesystem::create_directories(TEMP_SANDBOX_FOLDER);

   std::string filename = "./" + std::string(TEMP_SANDBOX_FOLDER) + "/" + "almost_a_symlink__test2_file";
   std::string file_contents = "/Users/markoates/Repos/foobar";
   ::write_file(filename, file_contents);
   ASSERT_EQ(true, std::filesystem::exists(filename));

   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
   EXPECT_EQ(true, project_symlink_fixer.likely_an_intended_symlink(filename));

   std::filesystem::remove_all(TEMP_SANDBOX_FOLDER);
}



TEST(Blast_Project_ProjectSymlinkFixerTest,
   likely_an_intended_symlink__returns_false_if_the_file_is_unlikely_to_be_a_symlink)
{
   std::filesystem::create_directories(TEMP_SANDBOX_FOLDER);

   std::string filename = "./" + std::string(TEMP_SANDBOX_FOLDER) + "/" + "almost_a_symlink";
   std::string file_contents = "#include <allegro5/allegro.h>\nint main(int argc, char **argv)\n{ return 0 }";
   ::write_file(filename, file_contents);
   ASSERT_EQ(true, std::filesystem::exists(filename));

   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
   EXPECT_EQ(false, project_symlink_fixer.likely_an_intended_symlink(filename));

   std::filesystem::remove_all(TEMP_SANDBOX_FOLDER);
}



TEST(Blast_Project_ProjectSymlinkFixerTest, run__returns_the_expected_response)
{
   Blast::Project::ProjectSymlinkFixer project_symlink_fixer;
   //std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, project_symlink_fixer.run());
}


