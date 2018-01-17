

#include <Blast/ShellCommandExecutor.hpp>

#include <iostream>


int main(int, char**)
{
   std::string command = "echo \"hello shell command!\"";
   ShellCommandExecutor shell_command_executor(command);

   std::string result = shell_command_executor.execute();

   std::cout << "Command: " << command << std::endl;
   std::cout << "Returned output: " << result << std::endl;

   return 0;
}


