
#include <gtest/gtest.h>

#include <Blast/Project/SymlinkChecker.hpp>

static const std::string FIXTURE_PATH = "/Users/markoates/Repos/blast/bin/fixtures/FixtureProject2/";

TEST(Blast_Project_SymlinkCheckerTest, can_be_created_without_blowing_up)
{
   Blast::Project::SymlinkChecker symlink_checker;
}

TEST(Blast_Project_SymlinkCheckerTest, the_expected_fixture_files_are_in_place)
{
   // todo
}

TEST(Blast_Project_SymlinkCheckerTest, is_symlink__returns_true_the_file_is_a_symlink)
{
   std::string symlink_file = FIXTURE_PATH + "quintessence/ComponentWithExternalSymlink.q.yml";
   Blast::Project::SymlinkChecker symlink_checker(symlink_file);

   ASSERT_EQ(true, symlink_checker.is_symlink());
}

TEST(Blast_Project_SymlinkCheckerTest, read_symlink_target__returns_the_target_of_the_symlink)
{
   std::string symlink_file = FIXTURE_PATH + "quintessence/ComponentWithExternalSymlink.q.yml";
   Blast::Project::SymlinkChecker symlink_checker(symlink_file);
   std::string expected_symlink_target = "/Users/markoates/Repos/blast/bin/fixtures/test_project/quintessence/ComponentWithExternalSymlink.q.yml";
   std::string actual_symlink_target = symlink_checker.read_symlink_target();

   ASSERT_EQ(expected_symlink_target, actual_symlink_target);
}

