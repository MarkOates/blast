

#include <Blast/RandomGenerator.hpp>

#include <iostream>


int main(int, char**)
{
   RandomGenerator random_generator;

   std::cout << "Generating random int (0-10)..." << std::endl;
   for (unsigned i=0; i<5; i++)
      std::cout << random_generator.get_random_int(0, 10) << std::endl;

   std::cout << "Generating random floats (0-10)..." << std::endl;
   for (unsigned i=0; i<5; i++)
      std::cout << random_generator.get_random_float(0, 10) << std::endl;

   std::cout << "Generating random doubles (0-10)..." << std::endl;
   for (unsigned i=0; i<5; i++)
      std::cout << random_generator.get_random_double(0, 10) << std::endl;

   return 0;
}


