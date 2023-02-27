#include <allegro5/allegro.h> // for compatibility with union/Makefile

#include <iostream>

#include <Blast/BuildSystem/BuildFactory.hpp>
#include <Blast/BuildSystem/ReportRenderer.hpp>
#include <Blast/BuildSystem/BuildStages/Base.hpp>
#include <Blast/FileExistenceChecker.hpp>


class ValidateBuildWin64ReleaseScript : public Blast::BuildSystem::BuildStages::Base
{
public:
   static constexpr char* TYPE = (char*)"ValidateBuildWin64ReleaseScript";
   std::string full_path_to_script;

   ValidateBuildWin64ReleaseScript()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_path_to_script("/msys64/home/Mark/Repos/blast/scripts/build_win64_release.sh")
   {}

   virtual bool execute() override
   {
      // TODO: execute the shell command
      if (Blast::FileExistenceChecker(full_path_to_script).exists()) return true;
      return false;
   }
};




int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=0; i<argc; i++) args.push_back(argv[i]);


   Blast::BuildSystem::BuildStageFactory build_stage_factory;
   Blast::BuildSystem::Builds::Base *build = new Blast::BuildSystem::Builds::Base;
   build->set_build_stages({
      new ValidateBuildWin64ReleaseScript(),
   });
   build->run();
   //parallel_build->run_all_in_parallel();


   Blast::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;

   return 0;
}
