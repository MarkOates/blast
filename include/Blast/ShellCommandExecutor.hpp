#pragma once


#include <string>


class ShellCommandExecutor
{
private:
   std::string command;

public:
   ShellCommandExecutor(std::string command);
   ~ShellCommandExecutor();

   std::string execute();
};


