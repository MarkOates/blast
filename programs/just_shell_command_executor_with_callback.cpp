#include <allegro5/allegro.h>
#include <Blast/ShellCommandExecutorWithCallback.hpp>

#include <sstream>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
   std::stringstream command;

   command << "pwd" << std::endl;

   std::cout << "============== command begin ===============" << std::endl;
   std::cout << command.str() << std::endl;
   std::cout << "============== command end ===============" << std::endl;

   Blast::ShellCommandExecutorWithCallback executor(command.str());

   std::cout << "============== execution begin ===============" << std::endl;
   executor.execute();
   std::cout << "============== execution end ===============" << std::endl;

   return 0;
}

