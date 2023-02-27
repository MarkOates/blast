
#include <gtest/gtest.h>

#include <Blast/BuildSystem/BuildStageFactory.hpp>


TEST(Blast_BuildSystem_BuildStageFactoryTest, can_be_created_without_blowing_up)
{
   Blast::BuildSystem::BuildStageFactory build_stage_factory;
}


