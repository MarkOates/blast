#include <allegro5/allegro.h> // for compatibility with union/Makefile

#include <iostream>
#include <sstream>

#include <Blast/ShellCommandExecutorWithCallback.hpp>

void execute_command(std::string command)
{
   Blast::ShellCommandExecutorWithCallback shell_command_executor(
         command,
         Blast::ShellCommandExecutorWithCallback::simple_cout_callback
      );

   shell_command_executor.execute();
}

int main(int argc, char **argv)
{
   std::string user_input;

   while(true)
   {
      std::cout << ">> ";
      std::cin >> user_input;

      if (user_input == "exit") break;

      std::stringstream command;
      command
         << "("
            << "cd /Users/markoates/Repos/hexagon"
            << "&&"
            << user_input
         << ")"
      ;

      execute_command(command.str());
   }

   return 0;
}

