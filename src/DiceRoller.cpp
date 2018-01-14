

#include <Blast/DiceRoller.hpp>


DiceRoller::DiceRoller(int num_sides_on_die, int num_die, unsigned int seed)
   : num_sides_on_die(num_sides_on_die)
   , num_die(num_die)
   , random_generator(seed)
{
}


DiceRoller::~DiceRoller()
{
}


void DiceRoller::set_num_sides_on_die(int num_sides_on_die)
{
   if (num_die <= 0) throw std::invalid_argument("DiceRoller::roll_dice() cannot <= 0 die.");
   this->num_sides_on_die = num_sides_on_die;
}


void DiceRoller::set_num_die(int num_die)
{
   if (num_die <= 0) throw std::invalid_argument("DiceRoller::roll_dice() cannot roll die with <= 0 sides.");
   this->num_die = num_die;
}


int DiceRoller::get_num_sides_on_die()
{
   return num_sides_on_die;
}


int DiceRoller::get_num_die()
{
   return num_die;
}


int DiceRoller::roll()
{
   int result = 0;
   for (int i = 0; i < num_die; i++)
      result += random_generator.get_random_int(1, num_sides_on_die);
   return result;
}


