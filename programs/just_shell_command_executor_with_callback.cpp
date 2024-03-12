#include <allegro5/allegro.h>
#include <Blast/ShellCommandExecutorWithCallback.hpp>

#include <sstream>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
   std::stringstream command;

   //command << "pwd" << std::endl;
   command << "gcloud -v" << std::endl;

   // The following commands do not work in MSYS2 using the ShellCommandExecutorWithCallback:
   //command << "\"\\C\\Users\\Mark\\AppData\\Local\\Google\\Cloud SDK\\google-cloud-sdk\\bin\\gcloud\" -v";
   //command << "(cd \"/C/Users/Mark/AppData/Local/Google/Cloud SDK/google-cloud-sdk/bin\" && ./gcloud -v)";
   //command << "(cd \"\\C\\Users\\Mark\\AppData\\Local\\Google\\Cloud SDK\\google-cloud-sdk\\bin\" && ./gcloud -v)";

   std::cout << "============== command begin ===============" << std::endl;
   std::cout << command.str() << std::endl;
   std::cout << "============== command end ===============" << std::endl;

   Blast::ShellCommandExecutorWithCallback executor(command.str());

   std::cout << "============== execution begin ===============" << std::endl;
   executor.execute();
   std::cout << "============== execution end ===============" << std::endl;

   return 0;
}

