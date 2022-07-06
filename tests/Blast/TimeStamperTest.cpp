
#include <gtest/gtest.h>

#include <Blast/TimeStamper.hpp>


TEST(Blast_TimeStamperTest, can_be_created_without_blowing_up)
{
   Blast::TimeStamper time_stamper;
}


TEST(Blast_TimeStamperTest, DISABLED__generate_now_timesamp_utc__returns_the_expected_response)
{
   Blast::TimeStamper time_stamper;
   std::string expected_string = "220706212224UTC";
   EXPECT_EQ(expected_string, time_stamper.generate_now_timestamp_utc());
}


