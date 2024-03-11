#include <allegro5/allegro.h>

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
   //std::string log_filename = "/C/Users/Mark/BuildTempFiles/foo.log";
   std::string log_filename = "/msys64/home/Mark/BuildTempFiles/foo.log";

   std::ofstream outfile;
   outfile.open(log_filename);

   if (!outfile.is_open())
   {
      std::cerr << "Error opening file: " << log_filename << std::endl;
      return 1;
   }

   return 0;
}

