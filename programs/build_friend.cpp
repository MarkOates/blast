#include <allegro5/allegro.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


#include <Blast/BuildSystem/Builds/Base.hpp>
#include <Blast/BuildSystem/BuildStages/Base.hpp>


namespace BuildWorkers
{
   namespace Stages
   {
       static void curl_signal_to_host_of_status_change(
             std::string status,
             std::chrono::high_resolution_clock::time_point time_of_status_change,
             int status_change_order_num,
             void *user_data
          )
       {
          // TODO: Improve sanitizing of postdata string
          // TODO: Add "gmt_time" to POST data
          // TODO: Format "gmt_time" to a nice format
          // CRITICAL: Improve sanitizing of postdata string

          std::stringstream postdata_command_line_arg_string;
          postdata_command_line_arg_string << "status=" << status << "&gmt_time=0&status_change_order_num=" << status_change_order_num;
          std::string url_to_signal_to = "https://webhook.site/2edc817a-ced8-422a-9f24-0de0b37598db";
          std::string command = "curl -d \"" + postdata_command_line_arg_string.str() + "\" -X POST " + url_to_signal_to;
          Blast::ShellCommandExecutorWithCallback curl_signal_command(command);
          curl_signal_command.execute();
       }

      class ExecuteTaskAndLogToFile : public Blast::BuildSystem::BuildStages::Base
      {
      private:
         std::string command;
         std::string log_filename;

      public:
         ExecuteTaskAndLogToFile(std::string command, std::string log_filename)
            : command(command)
            , log_filename(log_filename) //"tmp/build_log_from_build_friend_callback.log")
         {}

         virtual bool execute() override
         {
            //std::string command = "ls";
            std::ofstream outfile;
            outfile.open(log_filename);

            if (!outfile.is_open())
            {
               std::cerr << "Error opening file: " << log_filename << std::endl;
               return false;
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

      class UploadLogFileToGCloud : public Blast::BuildSystem::BuildStages::Base
      {
      private:
         std::string log_filename;

      public:
         UploadLogFileToGCloud(std::string log_filename)
            : log_filename(log_filename) //"tmp/build_log_from_build_friend_callback.log")
         {}

         virtual bool execute() override
         {
            // TODO: Improve sanitizing of postdata string
            // CRITICAL: Improve sanitizing of log_filename string

            std::stringstream command;
            if (!std::filesystem::exists(log_filename))
            {
               std::cout << "The expected generated log file \"" << log_filename << "\" does not exist.";
               return false;
            }
            command << "gcloud storage cp " << log_filename << " gs://clubcatt-build-status-and-logs-bucket/";

            Blast::ShellCommandExecutorWithCallback curl_signal_command(command.str());
            curl_signal_command.execute();

            return true;
         }
      };
   } // namespace Stage
} // namespace BuildWorkers



int main(int argc, char** argv)
{
   Blast::BuildSystem::Builds::Base build;

   // TODO: Allow using differnet commands from the pilot computer
   std::string command = "ls";
   // TODO: Make this a temporary filename (locally) and do not pass in in here when creating the build stages
   std::string log_filename = "./tmp/build_log_from_build_friend_callback-12345.log";

   build.set_build_stages({
      new BuildWorkers::Stages::ExecuteTaskAndLogToFile(command, log_filename),
      new BuildWorkers::Stages::UploadLogFileToGCloud(log_filename),
   });

   build.set_on_status_change_callback(BuildWorkers::Stages::curl_signal_to_host_of_status_change);
   build.run();

   return 0;
}


