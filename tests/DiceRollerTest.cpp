

#include <gtest/gtest.h>

#include <Blast/DiceRoller.hpp>

#include <cmath>


TEST(DiceRollerTest, can_be_created)
{
   DiceRoller dice_roller;
}


TEST(DiceRollerTest, when_created_without_arguments_has_the_expected_values)
{
   DiceRoller dice_roller;

   ASSERT_EQ(1, dice_roller.get_num_die());
   ASSERT_EQ(6, dice_roller.get_num_sides_on_die());
}


TEST(DiceRollerTest, can_get_and_set_the_number_die)
{
   DiceRoller dice_roller;

   dice_roller.set_num_die(13);
   ASSERT_EQ(13, dice_roller.get_num_die());

   dice_roller.set_num_die(7);
   ASSERT_EQ(7, dice_roller.get_num_die());
}


TEST(DiceRollerTest, can_get_and_set_the_number_sides_on_the_dice)
{
   DiceRoller dice_roller;

   dice_roller.set_num_sides_on_die(13);
   ASSERT_EQ(13, dice_roller.get_num_sides_on_die());

   dice_roller.set_num_sides_on_die(7);
   ASSERT_EQ(7, dice_roller.get_num_sides_on_die());
}


TEST(DiceRollerTest, roll__returns_total_values_rolled_dice_within_the_expected_range)
{
   for (unsigned num_dice=1; num_dice<=3; num_dice++)
   {
      DiceRoller dice_roller(10, num_dice, 123);

      for (unsigned i=0; i<10; i++)
      {
         int rolled_number = dice_roller.roll();
         ASSERT_TRUE(rolled_number >= 1);
         ASSERT_TRUE(rolled_number <= (10 * num_dice));
      }
   }
}


TEST(DiceRollerTest, roll__returns_the_rolled_value_a_die_with_equal_probability)
{
   const int SIDES_OF_DIE = 5;
   int buckets[SIDES_OF_DIE] = { 0 };
   int num_rolls = 10000;

   DiceRoller dice_roller(SIDES_OF_DIE, 1, 123);

   for (unsigned i=0; i<num_rolls; i++)
   {
      int rolled_number = dice_roller.roll();
      buckets[rolled_number-1]++;
   }

   float expected_testing_margin_error = 0.01;
   float expected_probability_each_roll = 1.0 / SIDES_OF_DIE;

   for (unsigned bucket=0; bucket < SIDES_OF_DIE; bucket++)
   {
      float probability_met_for_roll = (float)buckets[bucket] / num_rolls;
      ASSERT_TRUE(abs(probability_met_for_roll - expected_probability_each_roll) <= expected_testing_margin_error);
   }
}


TEST(DiceRollerTest, roll__returns_a_total_count_all_rolled_dice_with_the_expected_probability)
{
   const int SIDES_OF_DIE = 4;
   const int NUMBER_OF_DIE = 3;
   int buckets[SIDES_OF_DIE * NUMBER_OF_DIE] = { 0 };
   int num_rolls = 10000;

   DiceRoller dice_roller(SIDES_OF_DIE, NUMBER_OF_DIE, 123); // 3 4-sided die

   for (unsigned i=0; i<num_rolls; i++)
   {
      int rolled_number = dice_roller.roll();
      buckets[rolled_number-1]++;
   }

   float expected_probabilities[12] = { 0.0, 0.0, 0.015, 0.046, 0.093, 0.156, 0.187, 0.187, 0.156, 0.093, 0.046, 0.015 };
   float expected_testing_margin_error = 0.01;

   for (unsigned i=0; i < (NUMBER_OF_DIE * SIDES_OF_DIE); i++)
   {
      float probability_met_for_roll = (float)buckets[i] / num_rolls;
      ASSERT_TRUE(abs(probability_met_for_roll - expected_probabilities[i]) <= expected_testing_margin_error);
   }
}


