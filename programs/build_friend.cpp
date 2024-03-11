#include <allegro5/allegro.h>

#include <fstream>
#include <iostream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


int main(int argc, char** argv)
{
   std::string log_filename = "tmp/build_log_from_build_friend_callback.log";
   std::string command = "ls";
   std::ofstream outfile;
   outfile.open(log_filename);

   if (!outfile.is_open())
   {
      std::cerr << "Error opening file: " << log_filename << std::endl;
      return 1;
   }

   Blast::ShellCommandExecutorWithCallback executor(command, [&outfile](std::string content){
      outfile << content;
   });

   executor.execute();

   outfile.close();

   return 0;
}
