#include <NcursesArt/GithubRepoStatusFetcher.hpp>
#include <Blast/String/Trimmer.hpp>

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
      }

      std::this_thread::sleep_for(std::chrono::seconds(polling_frequency_sec));
   }

   return 0;
}

