

#include <Blast/DiceRoller.hpp>

#include <iostream>


void roll_roller(Blast::DiceRoller &dice_roller, int num_times)
{
   std::cout << "Rolling "
      << dice_roller.get_num_die()
      << " "
      << dice_roller.get_num_sides_on_die()
      << "-sided dice "
      << num_times
      << " time(s)..."
      << std::endl;

   for (int i=0; i<num_times; i++)
   {
      std::cout << "  Roll " << (i+1) << ": " << dice_roller.roll() << std::endl;
   }
}


int main(int argc, char **argv)
{
   Blast::DiceRoller dice_roller;

   roll_roller(dice_roller, 5);

   dice_roller.set_num_die(3);

   roll_roller(dice_roller, 5);

   dice_roller.set_num_die(2);
   dice_roller.set_num_sides_on_die(5);

   roll_roller(dice_roller, 5);

   return 0;
}


