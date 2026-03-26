#include <allegro5/allegro.h>
#include <Blast/ShellCommandExecutorWithCallback.hpp>

#include <sstream>
#include <fstream>
#include <iostream>


int main(int argc, char** argv)
{
   std::string filename = "/Users/markoates/Desktop/screenshots/resizes/shot2.png";
   std::string command = "magick \"" + filename + "\" -resize 1920x1080 -filter Lanczos -define filter:blur=0.75 \"/Users/markoates/Desktop/screenshot_output_1920x1080.png\"";

   //std::stringstream command;

   //command << "pwd" << std::endl;
   //command << "gcloud -v" << std::endl;

   // The following commands do not work in MSYS2 using the ShellCommandExecutorWithCallback:
   //command << "\"\\C\\Users\\Mark\\AppData\\Local\\Google\\Cloud SDK\\google-cloud-sdk\\bin\\gcloud\" -v";
   //command << "(cd \"/C/Users/Mark/AppData/Local/Google/Cloud SDK/google-cloud-sdk/bin\" && ./gcloud -v)";
   //command << "(cd \"\\C\\Users\\Mark\\AppData\\Local\\Google\\Cloud SDK\\google-cloud-sdk\\bin\" && ./gcloud -v)";

   std::cout << "============== command begin ===============" << std::endl;
   std::cout << command << std::endl;
   std::cout << "============== command end ===============" << std::endl;

   Blast::ShellCommandExecutorWithCallback executor(command);

   std::cout << "============== execution begin ===============" << std::endl;
   executor.execute();
   std::cout << "============== execution end ===============" << std::endl;

   return 0;
}

