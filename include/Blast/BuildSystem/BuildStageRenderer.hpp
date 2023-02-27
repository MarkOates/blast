#pragma once


#include <Blast/BuildSystem/BuildStages/Base.hpp>
#include <string>


namespace Blast
{
   namespace BuildSystem
   {
      class BuildStageRenderer
      {
      private:
         Blast::BuildSystem::BuildStages::Base* build_stage;

      protected:


      public:
         BuildStageRenderer(Blast::BuildSystem::BuildStages::Base* build_stage=nullptr);
         ~BuildStageRenderer();

         void set_build_stage(Blast::BuildSystem::BuildStages::Base* build_stage);
         Blast::BuildSystem::BuildStages::Base* get_build_stage() const;
         std::string build_text_report();
      };
   }
}



