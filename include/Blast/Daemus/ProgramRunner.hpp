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


      std::string __replace(std::string str="", std::string from="", std::string to="");
      void execute_command(std::string command="");
      void run();
      };
   }
}



