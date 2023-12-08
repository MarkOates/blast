
#include <gtest/gtest.h>

#include <Blast/Project/SourceReleaseAppInfoFile.hpp>


TEST(Blast_Project_SourceReleaseAppInfoFileTest, can_be_created_without_blowing_up)
{
   Blast::Project::SourceReleaseAppInfoFile source_release_app_info_file;
}


TEST(Blast_Project_SourceReleaseAppInfoFileTest, load_contents__loads_the_expected_content_into_the_object)
{
   Blast::Project::SourceReleaseAppInfoFile source_release_app_info_file;
   std::string file_contents = "app_icon_filename=bin/data/icons/golf-icon-01.png";

   source_release_app_info_file.load_contents(file_contents);

   EXPECT_EQ("bin/data/icons/golf-icon-01.png", source_release_app_info_file.get_app_icon_filename());
}


