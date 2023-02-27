#pragma once


#include <Blast/BuildSystem/BuildStageFactory.hpp>
#include <Blast/BuildSystem/Builds/Base.hpp>
#include <string>


namespace Blast
{
   namespace BuildSystem
   {
      class BuildFactory
      {
      private:
         Blast::BuildSystem::BuildStageFactory build_stage_factory;

      protected:


      public:
         BuildFactory();
         ~BuildFactory();

         Blast::BuildSystem::Builds::Base* create_placeholder_build();
         Blast::BuildSystem::Builds::Base* create_shell_command_build(std::string shell_command="echo \"Having a good day?\"");
      };
   }
}



