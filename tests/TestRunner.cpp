#include <allegro5/allegro.h> // only needed in this ase so tests wil compile
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
