
#include <gtest/gtest.h>

#include <ncurses_art/Backends/Base.hpp>


class BackendsBaseTestClass : public ncurses_art::Backends::Base
{
public:
   BackendsBaseTestClass()
      : ncurses_art::Backends::Base("BackendsBaseTestClass")
   {}
};


TEST(ncurses_art_Backends_BaseTest, can_be_created_without_blowing_up)
{
   ncurses_art::Backends::Base base;
}


TEST(ncurses_art_Backends_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_EQ("Backends/Base", base.get_type());
}


TEST(ncurses_art_Backends_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   ncurses_art::Backends::Base base;
   EXPECT_EQ(ncurses_art::Backends::Base::TYPE, base.get_type());
}


TEST(ncurses_art_Backends_BaseTest, derived_classes_will_have_the_expected_type)
{
   BackendsBaseTestClass test_class;
   EXPECT_EQ("BackendsBaseTestClass", test_class.get_type());
}


