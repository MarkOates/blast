
#include <Blast/QuintessenceLoader.hpp>
#include <iostream>

int main(int argc, char **argv)
{
   if (argc <= 1)
   {
      std::cout << "You must pass a quintessence filename (or a list of filenames) as an argument" << std::endl;
      return 1;
   }

   for (int i=1; i<argc; i++)
   {
      std::string quintessence_filename = argv[i];
      Blast::QuintessenceLoader quintessence_loader;
      quintessence_loader.load(quintessence_filename);
   }

   return 0;
}

