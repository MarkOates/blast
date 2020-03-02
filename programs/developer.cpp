#include <allegro5/allegro.h> // for compatibility with union/Makefile

#include <vector>
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
      getline(std::cin, user_input);
      std::cout << std::endl;

      if (user_input == "exit") break;

      std::vector<std::string> command_tokens;
      command_tokens = {
         "(",
            "cd /Users/markoates/Repos/blast",
            "&&",
            user_input,
         ")",
      };

      std::stringstream command;
      for (auto &command_token : command_tokens)
      {
         command << command_token << " ";
      }

      execute_command(command.str());
   }

   return 0;
}

