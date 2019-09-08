#pragma once


#include <functional>
#include <string>


namespace Blast
{
   class ShellCommandExecutorWithCallback
   {
   private:
      std::string command;
      std::function<void(std::string)> callback;

   public:
      ShellCommandExecutorWithCallback();
      ~ShellCommandExecutorWithCallback();


   std::string execute();
   };
}



