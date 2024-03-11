#include <allegro5/allegro.h>

#include <fstream>
#include <iostream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


#include <Blast/BuildSystem/Builds/Base.hpp>
#include <Blast/BuildSystem/BuildStages/Base.hpp>


namespace BuildWorkers
{
   namespace Stages
   {
      class SignalToHostOfStartingTask : public Blast::BuildSystem::BuildStages::Base
      {
         virtual bool execute() override
         {
            // TODO: Improve sanitizing of postdata string
            std::string postdata_command_line_arg_string = "status=starting";
            std::string url_to_signal_to = "https://webhook.site/2edc817a-ced8-422a-9f24-0de0b37598db";
            std::string command = "curl -d \"" + postdata_command_line_arg_string + "\" -X POST " + url_to_signal_to;
            Blast::ShellCommandExecutorWithCallback curl_signal_command(command);
            curl_signal_command.execute();
            return true;
         }
      };

      class ExecuteTask : public Blast::BuildSystem::BuildStages::Base
      {
         virtual bool execute() override
         {
            std::string log_filename = "tmp/build_log_from_build_friend_callback.log";
            std::string command = "ls";
            std::ofstream outfile;
            outfile.open(log_filename);

            if (!outfile.is_open())
            {
               std::cerr << "Error opening file: " << log_filename << std::endl;
               return 1;
            }

            Blast::ShellCommandExecutorWithCallback executor(command, [&outfile](std::string content){
               std::cout << content;
               outfile << content;
            });

            std::cout << "======================== starting execution (log file at \"" << log_filename << "\" ============================" << std::endl;
            executor.execute();
            outfile.close();
            std::cout << "======================== ending execution (log file at \"" << log_filename << "\" ============================" << std::endl;

            return true;
         }
      };

      class SignalToHostOfCompletedTask : public Blast::BuildSystem::BuildStages::Base
      {
         virtual bool execute() override
         {
            // TODO: Improve sanitizing of postdata string
            std::string postdata_command_line_arg_string = "status=completed";
            std::string url_to_signal_to = "https://webhook.site/2edc817a-ced8-422a-9f24-0de0b37598db";
            std::string command = "curl -d \"" + postdata_command_line_arg_string + "\" -X POST " + url_to_signal_to;
            Blast::ShellCommandExecutorWithCallback curl_signal_command(command);
            curl_signal_command.execute();
            return true;
         }
      };
   } // namespace Stage
} // namespace BuildWorkers




// TODO: Stages
// - signal to parent accepting task
// - execute command
//   - upload output log to location (possibly through gcloud)
//   - if success, signal success
//   - if failure, signal failure
// - signal completion of task with status


int main(int argc, char** argv)
{
   Blast::BuildSystem::Builds::Base build;

   build.set_build_stages({
      new BuildWorkers::Stages::SignalToHostOfStartingTask(),
      new BuildWorkers::Stages::ExecuteTask(),
      new BuildWorkers::Stages::SignalToHostOfCompletedTask(),
   });

   build.run();

   return 0;
}
