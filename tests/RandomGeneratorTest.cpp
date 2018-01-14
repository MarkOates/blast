

#include <gtest/gtest.h>

#include <Blast/RandomGenerator.hpp>

#include <cmath>


TEST(RandomGeneratorTest, get_seed__gets_the_current_seed)
{
   RandomGenerator number_generator = RandomGenerator(123);

   ASSERT_EQ(123, number_generator.get_seed());
}


TEST(RandomGeneratorTest, set_seed__sets_the_current_seed)
{
   RandomGenerator number_generator = RandomGenerator(123);
   number_generator.set_seed(456);

   ASSERT_EQ(456, number_generator.get_seed());
}


TEST(RandomGeneratorTest, get_random_int__only_returns_integers_within_the_bounds_inclusive)
{
   RandomGenerator number_generator = RandomGenerator(123);
   const int min_random_num = 1;
   const int max_random_num = 3;

   for (int i=0; i<1000; i++)
   {
      int val = number_generator.get_random_int(min_random_num, max_random_num);

      ASSERT_TRUE(val <= max_random_num);
      ASSERT_TRUE(val >= min_random_num);
   }
}


TEST(RandomGeneratorTest, get_random_float__only_returns_floats_within_the_bounds_inclusive)
{
   RandomGenerator number_generator = RandomGenerator(123);
   const float min_random_num = 1.0;
   const float max_random_num = 3.0;

   for (int i=0; i<1000; i++)
   {
      float val = number_generator.get_random_float(min_random_num, max_random_num);

      ASSERT_TRUE(val <= max_random_num);
      ASSERT_TRUE(val >= min_random_num);
   }
}


TEST(RandomGeneratorTest, get_random_double__only_returns_doubles_within_the_bounds_inclusive)
{
   RandomGenerator number_generator = RandomGenerator(123);
   const double min_random_num = 1.0;
   const double max_random_num = 3.0;

   for (int i=0; i<1000; i++)
   {
      double val = number_generator.get_random_double(min_random_num, max_random_num);

      ASSERT_TRUE(val <= max_random_num);
      ASSERT_TRUE(val >= min_random_num);
   }
}


TEST(RandomGeneratorTest, get_random_int__returns_an_expected_sequence_of_random_numbers_given_a_seed)
{
   RandomGenerator number_generator = RandomGenerator(123456);
   const int min_random_num = 0;
   const int max_random_num = 10;
   std::vector<int> expected_numbers = {1, 10, 2, 1, 8};

   for (int i=0; i<expected_numbers.size(); i++)
   {
      int val = number_generator.get_random_int(min_random_num, max_random_num);

      ASSERT_EQ(expected_numbers[i], val);
   }
}


TEST(RandomGeneratorTest, get_one_in_chance__returns_true_with_the_passed_probability)
{
   RandomGenerator number_generator(123);

   int tries = 10000;

   for (unsigned chance=1; chance<10; chance++)
   {
      int chances_met = 0;

      for (unsigned i=0; i<tries; i++)
      {
         if (number_generator.get_one_in_chance(chance)) chances_met++;
      }

      float probability_met = (float)chances_met / tries;
      float expected_probability = (float)1 / chance;
      float expected_testing_margin_of_error = 0.01;

      ASSERT_TRUE(abs(probability_met - expected_probability) <= expected_testing_margin_of_error);
   }
}


TEST(RandomGeneratorTest, get_one_in_chance__with_a_chance_lt_or_eq_0_always_returns_false)
{
   RandomGenerator number_generator(123);

   for (unsigned i=0; i<10; i++) ASSERT_FALSE(number_generator.get_one_in_chance(0));
   for (unsigned i=0; i<10; i++) ASSERT_FALSE(number_generator.get_one_in_chance(-3));
   for (unsigned i=0; i<10; i++) ASSERT_FALSE(number_generator.get_one_in_chance(-999));
}


