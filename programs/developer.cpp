#include <allegro5/allegro.h> // for compatibility with union/Makefile

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
   execute_command("(cd /Users/markoates/Repos/hexagon && ls)");

   return 0;
}

