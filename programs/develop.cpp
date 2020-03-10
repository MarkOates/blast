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

std::string __replace(std::string str, std::string from, std::string to)
{
   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
   return str;
}

int main(int argc, char **argv)
{
   //  "--tag focus"
   std::string RUBY_DEV_COMMAND_RERUN = "COMPONENT_NAME=[[COMPONENT_NAME]]; rerun -c \"bin/rails db:environment:set RAILS_ENV=test; bundle exec rspec spec/${COMPONENT_NAME}_spec.rb\"; unset COMPONENT_NAME";
   std::string RUBY_DEV_COMMAND = "COMPONENT_NAME=[[COMPONENT_NAME]]; bin/rails db:environment:set RAILS_ENV=test; bundle exec rspec spec/${COMPONENT_NAME}_spec.rb; unset COMPONENT_NAME";

   std::string user_input;
   while(true)
   {
      std::cout << "Ruby/Rspec mode" << std::endl;
      std::cout << "Type the name of the component: ";
      getline(std::cin, user_input);
      std::cout << std::endl;

      if (user_input == "exit") break;

      std::string user_command = RUBY_DEV_COMMAND_RERUN;
      user_command = __replace(user_command, "[[COMPONENT_NAME]]", user_input);

      std::vector<std::string> command_tokens;
      command_tokens = {
         "(",
            "cd /Users/markoates/dev_repos/partners",
            "&&",
            "(",
               user_command,
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

