

#include <Blast/CppPoolPatternGenerator.hpp>
#include <iostream>


int main(int, char**)
{
   CppPoolPatternGenerator cpp_pool_pattern_generator("Measure");

   std::cout << "########## HEADER FILE ##########" << std::endl;
   std::cout << cpp_pool_pattern_generator.generate_header_file_content();

   std::cout << "########## SOURCE FILE ##########" << std::endl;
   std::cout << cpp_pool_pattern_generator.generate_source_file_content();

   return 0;
}


