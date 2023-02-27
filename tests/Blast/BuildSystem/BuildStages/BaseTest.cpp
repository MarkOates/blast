
#include <gtest/gtest.h>

#include <Blast/BuildSystem/BuildStages/Base.hpp>


class BuildStagesBaseTestClass : public Blast::BuildSystem::BuildStages::Base
{
public:
   BuildStagesBaseTestClass()
      : Blast::BuildSystem::BuildStages::Base("BuildStagesBaseTestClass")
   {}
};


TEST(Blast_BuildSystem_BuildStages_BaseTest, can_be_created_without_blowing_up)
{
   Blast::BuildSystem::BuildStages::Base base;
}


TEST(Blast_BuildSystem_BuildStages_BaseTest, has_the_expected_type)
{
   Blast::BuildSystem::BuildStages::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(Blast_BuildSystem_BuildStages_BaseTest, get_started_at__will_return_the_default_value)
{
   Blast::BuildSystem::BuildStages::Base base;
   std::chrono::system_clock::time_point expected_time_point;
   std::chrono::system_clock::time_point actual_time_point = base.get_started_at();
   EXPECT_EQ(expected_time_point, actual_time_point);
}


TEST(Blast_BuildSystem_BuildStages_BaseTest, set_started_at__will_set_the_started_at_value)
{
   Blast::BuildSystem::BuildStages::Base base;
   std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
   base.set_started_at(time_point);
   std::chrono::system_clock::time_point actual_started_at = base.get_started_at();
   EXPECT_EQ(time_point, actual_started_at);
}


TEST(Blast_BuildSystem_BuildStages_BaseTest, get_ended_at__will_return_the_default_value)
{
   Blast::BuildSystem::BuildStages::Base base;
   std::chrono::system_clock::time_point expected_time_point;
   std::chrono::system_clock::time_point actual_time_point = base.get_ended_at();
   EXPECT_EQ(expected_time_point, actual_time_point);
}


TEST(Blast_BuildSystem_BuildStages_BaseTest, set_ended_at__will_set_the_ended_at_value)
{
   Blast::BuildSystem::BuildStages::Base base;
   std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
   base.set_ended_at(time_point);
   std::chrono::system_clock::time_point actual_ended_at = base.get_ended_at();
   EXPECT_EQ(time_point, actual_ended_at);
}


TEST(Blast_BuildSystem_BuildStages_BaseTest, derived_classes_will_have_the_expected_type)
{
   BuildStagesBaseTestClass test_class;
   EXPECT_EQ("BuildStagesBaseTestClass", test_class.get_type());
}


