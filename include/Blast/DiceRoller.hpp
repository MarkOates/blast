#pragma once


#include <Blast/RandomGenerator.hpp>


class DiceRoller
{
private:
   int num_sides_on_die;
   int num_die;

public:
   RandomGenerator random_generator;
   DiceRoller(int num_sides_on_die=6, int num_die=1, unsigned int seed=(unsigned int)time(0));
   ~DiceRoller();

   void set_num_sides_on_die(int num_sides_on_die);
   void set_num_die(int num_die);

   int get_num_sides_on_die();
   int get_num_die();

   int roll();
};


