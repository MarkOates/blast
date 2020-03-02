#include <allegro5/allegro.h> // for compatibility with union/Makefile

#include <Blast/ShellCommandExecutorWithCallback.hpp>

int main(int argc, char **argv)
{
   std::string command = "(cd /Users/markoates/Repos/hexagon && ls)";
   Blast::ShellCommandExecutorWithCallback shell_command_executor(
         command,
         Blast::ShellCommandExecutorWithCallback::simple_cout_callback
      );

   shell_command_executor.execute();

   return 0;
}

