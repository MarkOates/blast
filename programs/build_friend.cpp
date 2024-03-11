#include <allegro5/allegro.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


#include <Blast/BuildSystem/Builds/Base.hpp>
#include <Blast/BuildSystem/BuildStages/Base.hpp>
#include <Blast/SystemInfo.hpp>


class UserData
{
public:
   std::string hostname;
};


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
          std::string hostname = "unknown-host";
          UserData *data = static_cast<UserData*>(user_data); // TODO: Find better name for "UserData", "user_data", and/or "data"
          if (data) hostname = data->hostname;

          // TODO: Improve sanitizing of postdata string
          // TODO: Add "gmt_time" to POST data
          // TODO: Format "gmt_time" to a nice format
          // CRITICAL: Improve sanitizing of postdata string

          std::stringstream postdata_command_line_arg_string;
          postdata_command_line_arg_string << "status=" << status
                                           << "&hostname=" << hostname
                                           << "&gmt_time=0"
                                           << "&status_change_order_num=" << status_change_order_num
                                           ;
          std::string url_to_signal_to = "https://webhook.site/7eee5842-afad-443a-bab9-4c4e385bb0a6";
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
         std::string gcloud_destination_bucket;

      public:
         UploadLogFileToGCloud(std::string log_filename, std::string gcloud_destination_bucket)
            : log_filename(log_filename) //"tmp/build_log_from_build_friend_callback.log")
            , gcloud_destination_bucket(gcloud_destination_bucket) //"tmp/build_log_from_build_friend_callback.log")
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

            // TODO: CRITICAL: Sanitize log_filename and gcloud_destination_bucket
            // "gcloud storage cp "./tmp/build_log_from_build_friend_callback-12345.log" "gs://clubcatt-build-status-and-logs-bucket/";
            command << "gcloud storage cp \"" << log_filename << "\" \"" << gcloud_destination_bucket << "\""; //gs://clubcatt-build-status-and-logs-bucket/";

            Blast::ShellCommandExecutorWithCallback curl_signal_command(command.str());
            curl_signal_command.execute();

            return true;
         }
      };
   } // namespace Stage
} // namespace BuildWorkers



class BuildWorker : public Blast::BuildSystem::Builds::Base
{
private:
   std::string system_identifier;
   std::string command;
   std::string log_filename;
   std::string gcloud_destination_bucket;
   UserData user_data;

public:
   BuildWorker(std::string system_identifier="unknown-system", std::string command="echo 'command-not-set'")
      : system_identifier(system_identifier)
      , command(command)
      , log_filename("./tmp/" + generate_build_id() + "__" + system_identifier + "__build_log_from_build_friend_callback.log")
      , gcloud_destination_bucket("gs://clubcatt-build-status-and-logs-bucket/")
   {
      user_data.hostname = system_identifier;

      // TODO: Generate a random log_file
      set_build_stages({
         // TODO: Add stage to validate gcloud presence
         // TODO: Add stage to validate gcloud's current project is set to the expected project
         new BuildWorkers::Stages::ExecuteTaskAndLogToFile(command, log_filename),
         new BuildWorkers::Stages::UploadLogFileToGCloud(log_filename, gcloud_destination_bucket),
      });

      set_on_status_change_callback(BuildWorkers::Stages::curl_signal_to_host_of_status_change);
      set_on_status_change_callback_user_data((void*)(&user_data));
   }

   static std::string generate_build_id()
   {
      return "waspy-woo-25211";
   }

   ~BuildWorker()
   {
      cleanup();
   }
};



int main(int argc, char** argv)
{
   // Fetch info about this current system
   // TODO: Use a more secret name
   Blast::SystemInfo system_info;
   std::string hostname = system_info.get_hostname();

   // Build the worker
   std::string command = "ls";
   //std::string command = "(cd ~/Repos/SomePlatformer && git pull && make clean && make)";
   BuildWorker worker(hostname, command);
   worker.run();

   return 0;
}


