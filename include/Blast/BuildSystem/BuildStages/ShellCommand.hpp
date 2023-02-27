#pragma once


#include <Blast/BuildSystem/BuildStages/Base.hpp>
#include <string>


namespace Blast
{
   namespace BuildSystem
   {
      namespace BuildStages
      {
         class ShellCommand : public Blast::BuildSystem::BuildStages::Base
         {
         public:
            static constexpr char* TYPE = (char*)"ShellCommand";

         private:
            std::string shell_command;
            std::string shell_command_result;
            bool executed;

         protected:


         public:
            ShellCommand(std::string shell_command="echo \"hello, shell command.\"");
            virtual ~ShellCommand();

            std::string get_shell_command() const;
            std::string get_shell_command_result() const;
            virtual bool execute() override;
         };
      }
   }
}



