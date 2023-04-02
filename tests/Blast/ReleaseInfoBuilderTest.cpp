
#include <gtest/gtest.h>

#include <Blast/ReleaseInfoBuilder.hpp>


TEST(Blast_ReleaseInfoBuilderTest, can_be_created_without_blowing_up)
{
   Blast::ReleaseInfoBuilder release_info_builder;
}


TEST(Blast_ReleaseInfoBuilderTest, build__when_a_project_folder_does_not_exist__raises_an_exception)
{
   Blast::ReleaseInfoBuilder release_info_builder;
}


