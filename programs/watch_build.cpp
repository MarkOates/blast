#include <NcursesArt/GithubRepoStatusFetcher.hpp>
#include <Blast/String/Trimmer.hpp>
#include <Blast/Build/Celebrator.hpp>
#include <Blast/DeveloperSystem.hpp>

#include <filesystem>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <sstream>
#include <allegro5/allegro.h>


//std::string project_name = "/Users/markoates/Repos/";


bool project_folder_exists(std::string project_name)
{
   std::string folder_path = project_name;
   bool exists = (std::filesystem::exists(folder_path) && std::filesystem::is_directory(folder_path));
   return exists;
}


std::string timestamp_now()
{
   std::stringstream result;
   auto end = std::chrono::system_clock::now();
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);
   result << std::ctime(&end_time);
   return Blast::String::Trimmer(result.str()).trim();
}



//std::string builds_folder = "/Users/markoates/builds/";
//std::string projects_directory = "/Users/markoates/Repos/";



std::string fashion_build_command(std::string builds_folder, std::string project_name, std::string command, std::string snake_cased, int build_step_count_i)
{
   std::string build_num = "081a7bcf";
   //std::string command = "make clean";
   //std::string snake_cased = "make_clean";

   std::stringstream build_step_count_ss;
   build_step_count_ss << std::setw(3) << std::setfill('0') << build_step_count_i;

   std::string build_step_count = build_step_count_ss.str();

   std::string stdout_output_filename = builds_folder + build_num + "-" + build_step_count + "_" + snake_cased + "_output_stdout.txt";
   std::string stderr_output_filename = builds_folder + build_num + "-" + build_step_count + "_" + snake_cased + "_output_stderr.txt";

   std::stringstream full_command_with_captures;
   // (cd ~/Repos/"$project_name" && make clean) > make_clean_output_stdout.txt 2> make_clean_output_stderr.txt
   full_command_with_captures << "(cd ~/Repos/" << project_name << " && " << command << ") > " << stdout_output_filename << " 2> " << stderr_output_filename;

   return full_command_with_captures.str();
}


//(cd ~/Repos/"$project_name" && make clean && make fast && make tests && make bin/run_all_tests && make programs -j7 && make examples -j7) > output.txt 2>&1
//exit_code=$?
//echo "Exit code: $exit_code"


int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i=1; i<argc; i++) args.push_back(argv[i]);
   if (args.size() <= 1) throw std::runtime_error("You must pass a project name");


   Blast::DeveloperSystem developer_system;
   std::string builds_folder = developer_system.infer_builds_directory();
   std::string projects_directory = developer_system.infer_projects_directory();


   Blast::Build::Celebrator celebrator;


   std::vector<std::string> project_names_to_check;
   for (int i=0; i<args.size(); i++)
   {
      std::string project_name = args[i];

      std::string projects_full_path = projects_directory + project_name;
      if (!project_folder_exists(projects_full_path))
      {
         throw std::runtime_error("The project folder \"" + projects_full_path + "\" does not exist.");
      }

      project_names_to_check.push_back(project_name);
   }


   int polling_frequency_sec = 5;
   bool abort = false;
   int project_num = 0;

   while (!abort)
   {
      std::string project_name = args[project_num];

      NcursesArt::GithubRepoStatusFetcher fetcher(project_name, projects_directory);
      std::cout << "Polling (" << project_name << ")...";
      fetcher.poll_status();
      bool show_message = false;

      if (fetcher.is_the_repo_in_sync_with_remote())
      {
         std::cout << "...polling finished | In sync | Polled at: " << timestamp_now() << std::endl;
      }
      else // (!fetcher.is_the_repo_in_sync_with_remote())
      {
         std::cout << "...polling finished - Out of sync." << std::endl;
         // The local repo is not in sync
         std::cout << "++ Doing actions to sync remote" << std::endl;
         std::cout << "++ Checking if pull is OK" << std::endl;
         std::string pull_precheck_result = Blast::String::Trimmer(fetcher.execute_command(fetcher.get_precheck_pull_has_no_conflicts_command())).trim();
         if (!pull_precheck_result.empty())
         {
            // Cannot pull
            std::cout << "!! Cannot pull" << std::endl;
         }
         else
         {
            std::cout << "++ Pulling" << std::endl;
            std::string pull_result = Blast::String::Trimmer(fetcher.execute_command(fetcher.get_pull_command())).trim();
            std::cout << "++ Assuming pull worked fine, running a \"make clean && make\"" << std::endl;

            int build_step_count = 0;

            std::vector<std::string> commands = {
               fashion_build_command(builds_folder, project_name, "make clean", "make_clean", ++build_step_count)
            };

            if (project_name == "blast")
            {
               commands.push_back(
                  fashion_build_command(builds_folder, project_name, "make programs -j8", "blast_first_make_programs", ++build_step_count)
               );
            }

            std::vector<std::string> universal_commands = {
               fashion_build_command(builds_folder, project_name, "make quintessences -j8", "make_quintessences", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make deps -j8", "make_deps", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make objects -j8", "make_objects", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make test_objects -j8", "make_test_objects", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make library_for_tests", "make_library_for_tests", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make tests -j8", "make_tests", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make all_tests -j8", "make_all_tests", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make bin/run_all_tests", "make_bin_run_all_tests", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make library", "make_library", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make programs -j8", "make_programs", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make examples -j8", "make_examples", ++build_step_count),
               fashion_build_command(builds_folder, project_name, "make demos -j8", "make_demos", ++build_step_count),
            };

            commands.insert(commands.end(), universal_commands.begin(), universal_commands.end());

            for (auto &command : commands)
            {
               std::cout << "Running \"" << command << "\"" << std::endl;
               std::string make_shell_command = command;
               std::string make_shell_result = fetcher.execute_command(make_shell_command); // TODO: Capture an error
            }
         }

         show_message = true;
      }

      std::this_thread::sleep_for(std::chrono::seconds(polling_frequency_sec));

      if (show_message) std::cout << celebrator.generate_synced_banner() << std::endl;

      project_num++;
      if (project_num >= project_names_to_check.size()) project_num = 0;
   }

   return 0;
}

