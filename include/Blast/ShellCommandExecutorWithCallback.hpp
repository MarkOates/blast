#pragma once


#include <string>


namespace Blast
{
   class ShellCommandExecutorWithCallback
   {
   private:

   public:
      ShellCommandExecutorWithCallback();
      ~ShellCommandExecutorWithCallback();


   std::string run();
   };
}



