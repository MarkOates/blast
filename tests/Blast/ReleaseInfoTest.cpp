
#include <gtest/gtest.h>

#include <Blast/ReleaseInfo.hpp>


TEST(Blast_ReleaseInfoTest, can_be_created_without_blowing_up)
{
   Blast::ReleaseInfo release_info;
}


TEST(Blast_ReleaseInfoTest, build_project_version_string__will_return_a_nicely_formatted_string_of_the_verion)
{
   Blast::ReleaseInfo release_info;
   std::vector<std::pair<std::tuple<int, int, int, std::set<std::string>, std::set<std::string>>, std::string>>
         test_datas = {
      { { 7,  12,  0,          {},         {}, },                "7.12.0" },
      { { 12,  0,  1, { "alpha" },         {}, },                "12.0.1-alpha" },
      { { 12,  0,  1, { "wip", "alpha" },  {}, },                "12.0.1-alpha-wip" },
      { { 12,  0,  1, { "wip", "alpha" },  { "resize_fix" }, },  "12.0.1-alpha-wip+resize_fix" },
   };

   for (auto &test_data : test_datas)
   {
      release_info.set_project_version(
         std::get<0>(test_data.first),
         std::get<1>(test_data.first),
         std::get<2>(test_data.first),
         std::get<3>(test_data.first),
         std::get<4>(test_data.first)
      );

      std::string expected_version_string = test_data.second;
      std::string actual_version_string = release_info.build_project_version_string();

      EXPECT_EQ(expected_version_string, actual_version_string);
   }

   //release_info.set_project_version(7, 12, 0);
   //std::string expected_version_string = "7.12.0";
   //std::string actual_version_string = release_info.build_project_version_string();
   //EXPECT_EQ(expected_version_string, actual_version_string);
}


