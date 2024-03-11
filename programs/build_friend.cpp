#include <allegro5/allegro.h>

#include <iostream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


static void append_to_file_callback(std::string input)
{
}


int main(int argc, char** argv)
{
   std::string command = "ls";

   Blast::ShellCommandExecutorWithCallback executor(command, [](std::string content){
      std::cout << content;
      //append_to_file_callback(input
   });

   std::cout << "================= command start ===================" << std::endl;
   executor.execute();
   std::cout << "================= command end ===================" << std::endl;

   return 0;
}
