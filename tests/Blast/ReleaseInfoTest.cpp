
#include <gtest/gtest.h>

#include <Blast/ReleaseInfo.hpp>


TEST(Blast_ReleaseInfoTest, can_be_created_without_blowing_up)
{
   Blast::ReleaseInfo release_info;
}


TEST(Blast_ReleaseInfoTest, build_project_version_string__will_return_a_nicely_formatted_string_of_the_verion)
{
   Blast::ReleaseInfo release_info;
   release_info.set_project_version(7, 12, 0);
   std::string expected_version_string = "7.12.0";
   std::string actual_version_string = release_info.build_project_version_string();
   EXPECT_EQ(expected_version_string, actual_version_string);
}


