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

   std::string folder = "/Users/markoates/dev_repos/partners";

   std::cout << "  Mode: Shopify Dev Mode" << std::endl;
   std::cout << "Folder: " << folder << std::endl;
   std::cout << "====================" << std::endl;
   std::cout << "Enter component name >> ";
   getline(std::cin, user_input);
   std::cout << std::endl;

   while(true)
   {
      std::string ruby_component_test_rerun_command = "COMPONENT_NAME=" + user_input + " && rerun -c \"bin/rails db:environment:set RAILS_ENV=test; bundle exec rspec spec/${COMPONENT_NAME}_spec.rb\"; unset COMPONENT_NAME";

      std::cout << "Running command: " << ruby_component_test_rerun_command << std::endl;

      if (user_input == "exit") break;

      std::vector<std::string> command_tokens;
      command_tokens = {
         "(",
            //"cd /Users/markoates/Repos/blast",
            "cd ",
              folder,
            "&&",
            "(",
               user_input,
            ")",
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

