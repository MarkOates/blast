
#include <gtest/gtest.h>

#include <Blast/BuildSystem/ReportRenderers/Base.hpp>


class ReportRenderersBaseTestClass : public Blast::BuildSystem::ReportRenderers::Base
{
public:
   ReportRenderersBaseTestClass()
      : Blast::BuildSystem::ReportRenderers::Base("ReportRenderersBaseTestClass")
   {}
};


TEST(Blast_BuildSystem_ReportRenderers_BaseTest, can_be_created_without_blowing_up)
{
   Blast::BuildSystem::ReportRenderers::Base base;
}


TEST(Blast_BuildSystem_ReportRenderers_BaseTest, has_the_expected_type)
{
   Blast::BuildSystem::ReportRenderers::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(Blast_BuildSystem_ReportRenderers_BaseTest, derived_classes_will_have_the_expected_type)
{
   ReportRenderersBaseTestClass test_class;
   EXPECT_EQ("ReportRenderersBaseTestClass", test_class.get_type());
}


