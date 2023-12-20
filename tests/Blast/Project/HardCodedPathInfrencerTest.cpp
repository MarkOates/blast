
#include <gtest/gtest.h>

#include <Blast/Project/HardCodedPathInfrencer.hpp>


TEST(Blast_Project_HardCodedPathInfrencerTest, can_be_created_without_blowing_up)
{
   Blast::Project::HardCodedPathInfrencer hard_coded_path_infrencer;
}


//TEST(Blast_Project_HardCodedPathInfrencerTest, run__returns_the_expected_response)
//{
   //Blast::Project::HardCodedPathInfrencer hard_coded_path_infrencer;
   //std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, hard_coded_path_infrencer.run());
//}


