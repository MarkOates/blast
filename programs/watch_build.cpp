#include <NcursesArt/GithubRepoStatusFetcher.hpp>
#include <Blast/String/Trimmer.hpp>
#include <Blast/Build/Celebrator.hpp>

#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <sstream>
#include <allegro5/allegro.h>


std::string project_name = "/Users/markoates/Repos/";


std::string timestamp_now()
{
   std::stringstream result;
   auto end = std::chrono::system_clock::now();
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);
   result << std::ctime(&end_time);
   return Blast::String::Trimmer(result.str()).trim();
}

int main(int argc, char **argv)
{
   Blast::Build::Celebrator celebrator;
   std::string project_name = "Golf";
   int polling_frequency_sec = 10;
   bool abort = false;

   while (!abort)
   {
      NcursesArt::GithubRepoStatusFetcher fetcher(project_name, "/Users/markoates/Repos/");
      std::cout << "Polling (" << project_name << ")..." << std::endl;
      fetcher.poll_status();
      std::cout << "...polling finished." << std::endl;
      std::cout << "Polled at: " << timestamp_now() << std::endl;
      std::cout << "  In sync: " << fetcher.is_the_repo_in_sync_with_remote() << std::endl;

      if (!fetcher.is_the_repo_in_sync_with_remote())
      {
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
            std::string make_shell_command = "(cd ~/Repos/" + project_name + " && make clean && make fast && make programs -j7 && make examples -j7)";
            std::string make_shell_result = fetcher.execute_command(make_shell_command);
            std::cout << celebrator.generate_synced_banner() << std::endl;
         }
      }

      std::this_thread::sleep_for(std::chrono::seconds(polling_frequency_sec));
   }

   return 0;
}

