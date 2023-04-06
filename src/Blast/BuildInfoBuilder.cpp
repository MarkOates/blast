

#include <Blast/BuildInfoBuilder.hpp>

#include <NcursesArt/GithubRepoStatusFetcher.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Blast
{


BuildInfoBuilder::BuildInfoBuilder()
{
}


BuildInfoBuilder::~BuildInfoBuilder()
{
}


Blast::BuildInfo BuildInfoBuilder::build()
{
   if (!(project_git_repo_active()))
   {
      std::stringstream error_message;
      error_message << "[BuildInfoBuilder::build]: error: guard \"project_git_repo_active()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BuildInfoBuilder::build: error: guard \"project_git_repo_active()\" not met");
   }
   if (!(allegro_folder_exists()))
   {
      std::stringstream error_message;
      error_message << "[BuildInfoBuilder::build]: error: guard \"allegro_folder_exists()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BuildInfoBuilder::build: error: guard \"allegro_folder_exists()\" not met");
   }
   if (!(allegro_git_repo_active()))
   {
      std::stringstream error_message;
      error_message << "[BuildInfoBuilder::build]: error: guard \"allegro_git_repo_active()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BuildInfoBuilder::build: error: guard \"allegro_git_repo_active()\" not met");
   }
   if (!(allegro_flare_folder_exists()))
   {
      std::stringstream error_message;
      error_message << "[BuildInfoBuilder::build]: error: guard \"allegro_flare_folder_exists()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BuildInfoBuilder::build: error: guard \"allegro_flare_folder_exists()\" not met");
   }
   if (!(allegro_flare_git_repo_active()))
   {
      std::stringstream error_message;
      error_message << "[BuildInfoBuilder::build]: error: guard \"allegro_flare_git_repo_active()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BuildInfoBuilder::build: error: guard \"allegro_flare_git_repo_active()\" not met");
   }
   Blast::BuildInfo result;

   // Set allegro data
   result.set_allegro_version_git_hash(get_allegro_version_git_hash());
   result.set_allegro_version_git_branch(get_allegro_version_git_branch());
   result.set_allegro_version_git_num_commits(get_allegro_version_git_num_commits());
   result.set_allegro_version_git_latest_commit_date_and_time(get_allegro_version_git_latest_commit_date_and_time());

   return result;
}

std::string BuildInfoBuilder::get_allegro_version_git_hash()
{
   NcursesArt::GithubRepoStatusFetcher fetcher("allegro5");
   std::string result = fetcher.get_current_hash();
   return result;
}

std::string BuildInfoBuilder::get_allegro_version_git_branch()
{
   NcursesArt::GithubRepoStatusFetcher fetcher("allegro5");
   std::string result = fetcher.get_current_branch_name();
   return result;
}

int BuildInfoBuilder::get_allegro_version_git_num_commits()
{
   NcursesArt::GithubRepoStatusFetcher fetcher("allegro5");
   int result = fetcher.get_current_branch_num_commits();
   return result;
}

std::string BuildInfoBuilder::get_allegro_version_git_latest_commit_date_and_time()
{
   NcursesArt::GithubRepoStatusFetcher fetcher("allegro5");
   std::string result = fetcher.get_latest_commit_date_and_time();
   return result;
}

bool BuildInfoBuilder::project_git_repo_active()
{
   // TODO: this function
   return true;
}

bool BuildInfoBuilder::allegro_folder_exists()
{
   // TODO: this function
   return true;
}

bool BuildInfoBuilder::allegro_git_repo_active()
{
   // TODO: this function
   return true;
}

bool BuildInfoBuilder::allegro_flare_folder_exists()
{
   // TODO: this function
   return true;
}

bool BuildInfoBuilder::allegro_flare_git_repo_active()
{
   // TODO: this function
   return true;
}


} // namespace Blast


