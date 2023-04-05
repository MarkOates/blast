#include <allegro5/allegro.h> // for compatibility with union/Makefile

#include <iostream>
#include <sstream>

#include <Blast/BuildSystem/BuildFactory.hpp>
#include <Blast/BuildSystem/ReportRenderer.hpp>
#include <Blast/BuildSystem/BuildStages/Base.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>




std::string BUILD_WIN64_SCRIPT_FULL_PATH;
std::string BUILD_WIN64_SCRIPT_TARGET_IDENTIFIER;



class ValidateBuildWin64ReleaseScript : public Blast::BuildSystem::BuildStages::Base
{
public:
   static constexpr char* TYPE = (char*)"ValidateBuildWin64ReleaseScript";
   std::string full_path_to_script;

   ValidateBuildWin64ReleaseScript()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_path_to_script(BUILD_WIN64_SCRIPT_FULL_PATH)
   {}

   virtual bool execute() override
   {
      // TODO: execute the shell command
      if (Blast::FileExistenceChecker(full_path_to_script).exists()) return true;
      return false;
   }
};




class ExecuteBuildWin64ReleaseScript : public Blast::BuildSystem::BuildStages::Base
{
private:
   std::string get_result_of_shell_execution()
   {
      std::stringstream shell_command;
      shell_command << full_path_to_script << " " << script_arg;
      Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      return shell_command_executor.execute();
   }

public:
   static constexpr char* TYPE = (char*)"ExecuteBuildWin64ReleaseScript";
   std::string full_path_to_script;
   std::string script_arg;

   ExecuteBuildWin64ReleaseScript()
      : Blast::BuildSystem::BuildStages::Base(TYPE)
      , full_path_to_script(BUILD_WIN64_SCRIPT_FULL_PATH)
      , script_arg(BUILD_WIN64_SCRIPT_TARGET_IDENTIFIER)
   {}

   virtual bool execute() override
   {
      //std::string match_expression = "\nThe first form lists the names of all xattrs on the given"; // a line from the help file
      std::string output_string = get_result_of_shell_execution();
      //if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      return true;
   }
};




int main(int argc, char **argv)
{
   // TODO: Warn the builder if allegro repo is not master
   // TODO: Warn the builder if allegro has dirty worktree files
   // TODO: Warn the builder if allegro hash does not match the version used to create the release

   // TODO: Warn the builder if allegro_flare repo is not master
   // TODO: Warn the builder if allegro_flare has dirty worktree files
   // TODO: Warn the builder if allegro_flare hash does not match the version used to create the release

   std::cout << "For now, this program is not in use.  Please call the script directly "
                "at blast/scripts/build_win64_release.sh" << std::endl;
   return 1;


   std::vector<std::string> args;
   std::string execution_name = argv[0];
   for (int i=1; i<argc; i++) args.push_back(argv[i]);


   std::string name_of_source_release = "";
   std::string version_number_string = "";

   if (args.size() == 1)
   {
      name_of_source_release = args[0];
      version_number_string = args[1];
      // TODO: validate version number string format
      // TODO: validate version number string maches version of source (could remove argument as a result)
   }
   else
   {
      std::cout << "You did it!" << std::endl;
      std::cout << "Please see instructions. You will need to pass a release name as the first argument." << std::endl;
      std::cout << std::endl;
      std::cout << execution_name << " KrampusReturns-0.1.2-SourceRelease 0.1.2" << std::endl;
      std::cout << std::endl;
      return 1;
   }


   BUILD_WIN64_SCRIPT_FULL_PATH = "/msys64/home/Mark/Repos/blast/scripts/build_win64_release.sh";
   BUILD_WIN64_SCRIPT_TARGET_IDENTIFIER = name_of_source_release;



   Blast::BuildSystem::BuildStageFactory build_stage_factory;
   Blast::BuildSystem::Builds::Base *build = new Blast::BuildSystem::Builds::Base;
   build->set_build_stages({
      new ValidateBuildWin64ReleaseScript(),
      new ExecuteBuildWin64ReleaseScript(),
   });
   build->run();
   //parallel_build->run_all_in_parallel();


   Blast::BuildSystem::ReportRenderer report_renderer(build);
   std::cout << report_renderer.build_text_report() << std::endl;

   return 0;
}
