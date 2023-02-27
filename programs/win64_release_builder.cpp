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
   std::string execution_name = argv[0];
   for (int i=1; i<argc; i++) args.push_back(argv[i]);


   std::string name_of_source_release = "";

   if (args.size() == 1)
   {
      name_of_source_release = args[0];
   }
   else
   {
      std::cout << "You did it!" << std::endl;
      std::cout << "Please see instructions. You will need to pass a release name as the first argument." << std::endl;
      std::cout << std::endl;
      std::cout << execution_name << " KrampusReturns-SourceRelease-230101031610UTC" << std::endl;
      std::cout << std::endl;
      std::cout << std::endl;
      return 1;
   }


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
