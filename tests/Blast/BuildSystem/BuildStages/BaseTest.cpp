
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
   std::chrono::high_resolution_clock::time_point expected_time_point;
   std::chrono::high_resolution_clock::time_point actual_time_point = base.get_started_at();
   EXPECT_EQ(expected_time_point, actual_time_point);
}


TEST(Blast_BuildSystem_BuildStages_BaseTest, set_started_at__will_set_the_started_at_value)
{
   Blast::BuildSystem::BuildStages::Base base;
   std::chrono::high_resolution_clock::time_point time_point = std::chrono::high_resolution_clock::now();
   base.set_started_at(time_point);
   std::chrono::high_resolution_clock::time_point actual_started_at = base.get_started_at();
   EXPECT_EQ(time_point, actual_started_at);
}


TEST(Blast_BuildSystem_BuildStages_BaseTest, get_ended_at__will_return_the_default_value)
{
   Blast::BuildSystem::BuildStages::Base base;
   std::chrono::high_resolution_clock::time_point expected_time_point;
   std::chrono::high_resolution_clock::time_point actual_time_point = base.get_ended_at();
   EXPECT_EQ(expected_time_point, actual_time_point);
}


TEST(Blast_BuildSystem_BuildStages_BaseTest, set_ended_at__will_set_the_ended_at_value)
{
   Blast::BuildSystem::BuildStages::Base base;
   std::chrono::high_resolution_clock::time_point time_point = std::chrono::high_resolution_clock::now();
   base.set_ended_at(time_point);
   std::chrono::high_resolution_clock::time_point actual_ended_at = base.get_ended_at();
   EXPECT_EQ(time_point, actual_ended_at);
}


TEST(Blast_BuildSystem_BuildStages_BaseTest, derived_classes_will_have_the_expected_type)
{
   BuildStagesBaseTestClass test_class;
   EXPECT_EQ("BuildStagesBaseTestClass", test_class.get_type());
}


TEST(Blast_BuildSystem_BuildStages_BaseTest,
   DISABLED__started_at__is_of_the_type_high_resolution_clock)
{
   // NOTE: This test is needed to ensure flakey tests to not occur, and that very short, small duration builds
   // (on the order of milliseconds) still have their durations recorded
   // TODO: This test, currently "started_at" is private
   // TODO: This test for "ended_at"
   // TODO: This test in the other BuildSystem/Builds/Base tests
   // NOTE: Test is implmented like this:
   //ASSERT_TRUE(
      //(
         //std::is_same<
            //decltype(Blast::BuildSystem::BuildStages::Base::started_at),
            //std::chrono::high_resolution_clock::time_point
         //>::value
      //)
   //);
}


TEST(Blast_BuildSystem_BuildStages_BaseTest,
   DISABLED__ended_at__is_of_the_type_high_resolution_clock)
{
   // TODO: See test above
}


