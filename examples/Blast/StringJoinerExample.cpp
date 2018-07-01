

#include <Blast/StringJoiner.hpp>

#include <iostream>
#include <vector>


int main(int, char**)
{
   std::vector<std::string> names = { "Tommy", "Sally", "Harold", "Frankie", "Elisa" };
   Blast::StringJoiner string_joiner(names, ", ");

   std::cout << "The following idems will be joined: " << std::endl;
   for (auto &name : names) std::cout << "  - " << name << std::endl;

   std::cout << "Joined: \"" << string_joiner.join() << "\"" << std::endl;

   return 0;
}


