

#include <Blast/RailsInflector.hpp>

#include <iostream>
#include <vector>


int main(int argc, char *argv[])
{
   std::vector<std::string> words = {
      "tree",
      "duck",
      "family",
      "mouse",
      "mice",
      "hamster",
      "goose",
      "geese",
      "horde",
      "data",
   };

   std::cout << "Pluralizing:" << std::endl;

   for (auto &word : words)
   {
      Blast::RailsInflector rails_inflector(word, Blast::RailsInflector::PLURALIZE);
      std::cout << "   " << word << ": " << rails_inflector.inflect() << std::endl;
   }

   std::cout << "Singularizing:" << std::endl;

   for (auto &word : words)
   {
      Blast::RailsInflector rails_inflector(word, Blast::RailsInflector::SINGULARIZE);
      std::cout << "   " << word << ": " << rails_inflector.inflect() << std::endl;
   }

   return 0;
}


