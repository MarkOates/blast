#pragma once


#include <Blast/BuildSystem/BuildStages/ShellCommand.hpp>
#include <string>


namespace Blast
{
   namespace BuildSystem
   {
      class BuildStageFactory
      {
      private:

      protected:


      public:
         BuildStageFactory();
         ~BuildStageFactory();

         Blast::BuildSystem::BuildStages::ShellCommand* create_shell_command_build_stage(std::string shell_command="echo \"Hi friend\"");
      };
   }
}



