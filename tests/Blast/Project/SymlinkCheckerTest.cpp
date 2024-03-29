
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(stmt, etype, whatstring) ASSERT_THROW( \
        try { \
            stmt; \
        } catch (const etype& ex) { \
            ASSERT_EQ(std::string(ex.what()), whatstring); \
            throw; \
        } \
    , etype)

#include <Blast/Project/SymlinkChecker.hpp>

#include <filesystem>
static const std::string RELATIVE_FIXTURE_PATH = "tests/fixtures/FixtureProject2/";
static std::string FIXTURE_PATH()
{
   return std::filesystem::absolute(RELATIVE_FIXTURE_PATH).string();
}

TEST(Blast_Project_SymlinkCheckerTest, can_be_created_without_blowing_up)
{
   Blast::Project::SymlinkChecker symlink_checker;
}

TEST(DISABLED_Blast_Project_SymlinkCheckerTest, the_expected_fixture_files_are_in_place)
{
   // todo
}

TEST(Blast_Project_SymlinkCheckerTest, is_symlink__returns_true_the_file_is_a_symlink)
{
   std::string symlink_file = FIXTURE_PATH() + "quintessence/ComponentWithExternalSymlink.q.yml";
   Blast::Project::SymlinkChecker symlink_checker(symlink_file);

   ASSERT_EQ(true, symlink_checker.is_symlink());
}

TEST(Blast_Project_SymlinkCheckerTest, is_symlink__if_symlink_does_not_exist__returns_false)
{
   std::string symlink_file = FIXTURE_PATH() + "quintessence/AComponentThatDoesNotExist.q.yml";
   Blast::Project::SymlinkChecker symlink_checker(symlink_file);
   ASSERT_EQ(false, symlink_checker.is_symlink());
}

TEST(Blast_Project_SymlinkCheckerTest, is_symlink__works_on_relative_fileanmes)
{
   std::string symlink_filename = "./tests/fixtures/FixtureProject2/quintessence/ComponentWithExternalSymlink.q.yml";
   Blast::Project::SymlinkChecker symlink_checker(symlink_filename);

   ASSERT_EQ(true, symlink_checker.is_symlink());
}

TEST(Blast_Project_SymlinkCheckerTest, read_symlink_target__returns_the_target_of_the_symlink)
{
   std::string symlink_file = FIXTURE_PATH() + "quintessence/ComponentWithExternalSymlink.q.yml";
   Blast::Project::SymlinkChecker symlink_checker(symlink_file);
   std::string expected_symlink_target = "../../test_project/quintessence/ComponentWithExternalSymlink.q.yml";
   std::string actual_symlink_target = symlink_checker.read_symlink_target();

   ASSERT_EQ(expected_symlink_target, actual_symlink_target);
}

