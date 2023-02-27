
#include <gtest/gtest.h>

#include <Blast/BuildSystem/BuildStageRenderers/Base.hpp>


class BuildStageRenderersBaseTestClass : public Blast::BuildSystem::BuildStageRenderers::Base
{
public:
   BuildStageRenderersBaseTestClass()
      : Blast::BuildSystem::BuildStageRenderers::Base("BuildStageRenderersBaseTestClass")
   {}
};


TEST(Blast_BuildSystem_BuildStageRenderers_BaseTest, can_be_created_without_blowing_up)
{
   Blast::BuildSystem::BuildStageRenderers::Base base;
}


TEST(Blast_BuildSystem_BuildStageRenderers_BaseTest, has_the_expected_type)
{
   Blast::BuildSystem::BuildStageRenderers::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(Blast_BuildSystem_BuildStageRenderers_BaseTest, derived_classes_will_have_the_expected_type)
{
   BuildStageRenderersBaseTestClass test_class;
   EXPECT_EQ("BuildStageRenderersBaseTestClass", test_class.get_type());
}


