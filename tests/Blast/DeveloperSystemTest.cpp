
#include <gtest/gtest.h>

#include <Blast/DeveloperSystem.hpp>


TEST(Blast_DeveloperSystemTest, can_be_created_without_blowing_up)
{
   Blast::DeveloperSystem developer_system;
}


TEST(Blast_DeveloperSystemTest, infer_base_directory__will_return_the_expected_directory)
{
   Blast::DeveloperSystem developer_system;
#ifdef _WIN32
   std::string expected_directory = "/msys64/home/Mark/";
   EXPECT_EQ(expected_directory, developer_system.infer_base_directory());
#elif __APPLE__ || __MACH__
   std::string expected_directory = "/Users/markoates/";
   EXPECT_EQ(expected_directory, developer_system.infer_base_directory());
#else
   throw std::runtime_error("There is no test data for this platform");
#endif
}


TEST(Blast_DeveloperSystemTest, infer_project_directory__will_return_the_expected_directory)
{
   Blast::DeveloperSystem developer_system;
#ifdef _WIN32
   std::string expected_directory = "/msys64/home/Mark/Repos/";
   EXPECT_EQ(expected_directory, developer_system.infer_project_directory());
#elif __APPLE__ || __MACH__
   std::string expected_directory = "/Users/markoates/Repos/";
   EXPECT_EQ(expected_directory, developer_system.infer_project_directory());
#else
   throw std::runtime_error("There is no test data for this platform");
#endif
}


TEST(Blast_DeveloperSystemTest, infer_builds_directory__will_return_the_expected_directory)
{
   Blast::DeveloperSystem developer_system;
#ifdef _WIN32
   std::string expected_directory = "/msys64/home/Mark/Builds/";
   EXPECT_EQ(expected_directory, developer_system.infer_builds_directory());
#elif __APPLE__ || __MACH__
   std::string expected_directory = "/Users/markoates/Builds/";
   EXPECT_EQ(expected_directory, developer_system.infer_builds_directory());
#else
   throw std::runtime_error("There is no test data for this platform");
#endif
}


