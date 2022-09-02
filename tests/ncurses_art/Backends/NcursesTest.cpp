
#include <gtest/gtest.h>

#include <ncurses_art/Backends/Ncurses.hpp>


TEST(ncurses_art_Backends_NcursesTest, can_be_created_without_blowing_up)
{
   ncurses_art::Backends::Ncurses ncurses;
}


TEST(ncurses_art_Backends_NcursesTest, TYPE__has_the_expected_value)
{
   ncurses_art::Backends::Ncurses ncurses;
   EXPECT_EQ("Backends/Ncurses", ncurses.get_type());
}


TEST(ncurses_art_Backends_NcursesTest, type__has_the_expected_value_matching_TYPE)
{
   ncurses_art::Backends::Ncurses ncurses;
   EXPECT_EQ(ncurses_art::Backends::Ncurses::TYPE, ncurses.get_type());
}


