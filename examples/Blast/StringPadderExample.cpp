

#include <Blast/StringPadder.hpp>

#include <iostream>
#include <vector>


int main(int, char**)
{
   std::vector<std::string> names = { "This is the text", "Text", "Some more text that is quite long." };

   std::cout << "Text with padding:" << std::endl;
   for (auto &name : names)
   {
      std::cout << " - \"" << Blast::StringPadder(name, 20, '#').pad() << "\"" << std::endl;
   }

   return 0;
}


