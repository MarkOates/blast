#pragma once


#include <Blast/BuildSystem/BuildStageRenderers/Base.hpp>
#include <Blast/BuildSystem/BuildStages/ShellCommand.hpp>
#include <string>


namespace Blast
{
   namespace BuildSystem
   {
      namespace BuildStageRenderers
      {
         class ShellCommand : public Blast::BuildSystem::BuildStageRenderers::Base
         {
         public:
            static constexpr char* TYPE = (char*)"ShellCommand";

         private:
            Blast::BuildSystem::BuildStages::ShellCommand* shell_command_build_stage;

         protected:


         public:
            ShellCommand(Blast::BuildSystem::BuildStages::ShellCommand* shell_command_build_stage=nullptr);
            virtual ~ShellCommand();

            void set_shell_command_build_stage(Blast::BuildSystem::BuildStages::ShellCommand* shell_command_build_stage);
            virtual std::string render_text() override;
         };
      }
   }
}



