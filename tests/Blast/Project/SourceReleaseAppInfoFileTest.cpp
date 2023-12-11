
#include <gtest/gtest.h>

#include <Blast/Project/SourceReleaseAppInfoFile.hpp>


TEST(Blast_Project_SourceReleaseAppInfoFileTest, can_be_created_without_blowing_up)
{
   Blast::Project::SourceReleaseAppInfoFile source_release_app_info_file;
}


TEST(Blast_Project_SourceReleaseAppInfoFileTest, DEFAULT_APP_ICON_FILENAME__has_the_expected_value)
{
   EXPECT_STREQ(
      "data/icons/allegro-flare-generic-icon-1024.png",
      Blast::Project::SourceReleaseAppInfoFile::DEFAULT_APP_ICON_FILENAME
   );
}


TEST(Blast_Project_SourceReleaseAppInfoFileTest, app_icon_filename__is_set_to_the_default_value)
{
   //Blast::Project::SourceReleaseAppInfoFile source_release_app_info_file;
   //EXPECT_STREQ(
      //Blast::Project::SourceReleaseAppInfoFile::DEFAULT_APP_ICON_FILENAME,
      //source_release_app_info_file.get_app_icon_filename()
   //);
}


TEST(Blast_Project_SourceReleaseAppInfoFileTest,
   app_icon_filename_is_default__will_return_true_when_the_app_icon_is_set_to_the_default_value)
{
   Blast::Project::SourceReleaseAppInfoFile source_release_app_info_file;
   EXPECT_EQ(true, source_release_app_info_file.app_icon_filename_is_default());
}


TEST(Blast_Project_SourceReleaseAppInfoFileTest,
   app_icon_filename_is_default__will_return_false_when_the_app_icon_is_custom)
{
   Blast::Project::SourceReleaseAppInfoFile source_release_app_info_file;
   source_release_app_info_file.set_app_icon_filename("data/icons/golf-icon-01.png");
   EXPECT_EQ(false, source_release_app_info_file.app_icon_filename_is_default());
}


TEST(Blast_Project_SourceReleaseAppInfoFileTest, load_contents__loads_the_expected_content_into_the_object)
{
   Blast::Project::SourceReleaseAppInfoFile source_release_app_info_file;
   std::string file_contents = "app_icon_filename=data/icons/golf-icon-01.png";

   source_release_app_info_file.load_contents(file_contents);

   EXPECT_EQ("data/icons/golf-icon-01.png", source_release_app_info_file.get_app_icon_filename());
}


