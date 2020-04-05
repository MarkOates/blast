#pragma once


#include <string>


namespace Blast
{
   namespace Daemus
   {
      class ProgramRunner
      {
      private:

      public:
         ProgramRunner();
         ~ProgramRunner();


      void execute_command(std::string command="");
      void run();
      };
   }
}



