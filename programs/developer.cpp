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
   std::string RUBY_DEV_COMMAND = "COMPONENT_NAME=models/review; rerun -c \"bin/rails db:environment:set RAILS_ENV=test; bundle exec rspec spec/${COMPONENT_NAME}_spec.rb\"; unset COMPONENT_NAME";

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
            "cd /Users/markoates/dev_repos/partners",
            "&&",
            RUBY_DEV_COMMAND,
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

