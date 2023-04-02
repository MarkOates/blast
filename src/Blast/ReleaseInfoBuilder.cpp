

#include <Blast/ReleaseInfoBuilder.hpp>

#include <Blast/DirectoryExistenceChecker.hpp>
#include <NcursesArt/GithubRepoStatusFetcher.hpp>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>


namespace Blast
{


ReleaseInfoBuilder::ReleaseInfoBuilder(std::string project_name, std::string projects_folder)
   : project_name(project_name)
   , projects_folder(projects_folder)
{
}


ReleaseInfoBuilder::~ReleaseInfoBuilder()
{
}


void ReleaseInfoBuilder::set_project_name(std::string project_name)
{
   this->project_name = project_name;
}


void ReleaseInfoBuilder::set_projects_folder(std::string projects_folder)
{
   this->projects_folder = projects_folder;
}


std::string ReleaseInfoBuilder::get_project_name() const
{
   return project_name;
}


std::string ReleaseInfoBuilder::get_projects_folder() const
{
   return projects_folder;
}


Blast::ReleaseInfo ReleaseInfoBuilder::build()
{
   if (!(project_name_is_valid()))
   {
      std::stringstream error_message;
      error_message << "[ReleaseInfoBuilder::build]: error: guard \"project_name_is_valid()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ReleaseInfoBuilder::build: error: guard \"project_name_is_valid()\" not met");
   }
   if (!(project_folder_exists()))
   {
      std::stringstream error_message;
      error_message << "[ReleaseInfoBuilder::build]: error: guard \"project_folder_exists()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ReleaseInfoBuilder::build: error: guard \"project_folder_exists()\" not met");
   }
   if (!(project_git_repo_active()))
   {
      std::stringstream error_message;
      error_message << "[ReleaseInfoBuilder::build]: error: guard \"project_git_repo_active()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ReleaseInfoBuilder::build: error: guard \"project_git_repo_active()\" not met");
   }
   if (!(allegro_folder_exists()))
   {
      std::stringstream error_message;
      error_message << "[ReleaseInfoBuilder::build]: error: guard \"allegro_folder_exists()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ReleaseInfoBuilder::build: error: guard \"allegro_folder_exists()\" not met");
   }
   if (!(allegro_git_repo_active()))
   {
      std::stringstream error_message;
      error_message << "[ReleaseInfoBuilder::build]: error: guard \"allegro_git_repo_active()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ReleaseInfoBuilder::build: error: guard \"allegro_git_repo_active()\" not met");
   }
   if (!(allegro_flare_folder_exists()))
   {
      std::stringstream error_message;
      error_message << "[ReleaseInfoBuilder::build]: error: guard \"allegro_flare_folder_exists()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ReleaseInfoBuilder::build: error: guard \"allegro_flare_folder_exists()\" not met");
   }
   if (!(allegro_flare_git_repo_active()))
   {
      std::stringstream error_message;
      error_message << "[ReleaseInfoBuilder::build]: error: guard \"allegro_flare_git_repo_active()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ReleaseInfoBuilder::build: error: guard \"allegro_flare_git_repo_active()\" not met");
   }
   Blast::ReleaseInfo result;

   // Set project data
   result.set_project_git_hash(get_project_git_hash());
   result.set_project_git_branch(get_project_git_branch());
   result.set_project_git_num_commits(get_project_git_num_commits());

   // Set allegro data
   result.set_allegro_version_git_hash(get_allegro_version_git_hash());
   result.set_allegro_version_git_branch(get_allegro_version_git_branch());
   result.set_allegro_version_git_num_commits(get_allegro_version_git_num_commits());

   // Set allegro_flare data
   result.set_allegro_flare_version_git_hash(get_allegro_flare_version_git_hash());
   result.set_allegro_flare_version_git_branch(get_allegro_flare_version_git_branch());
   result.set_allegro_flare_version_git_num_commits(get_allegro_flare_version_git_num_commits());

   return result;
}

std::string ReleaseInfoBuilder::get_project_git_hash()
{
   NcursesArt::GithubRepoStatusFetcher fetcher(project_name);
   std::string result = fetcher.get_current_hash();
   return result;
}

std::string ReleaseInfoBuilder::get_project_git_branch()
{
   NcursesArt::GithubRepoStatusFetcher fetcher(project_name);
   std::string result = fetcher.get_current_branch_name();
   return result;
}

int ReleaseInfoBuilder::get_project_git_num_commits()
{
   NcursesArt::GithubRepoStatusFetcher fetcher(project_name);
   int result = fetcher.get_current_branch_num_commits();
   return result;
}

std::string ReleaseInfoBuilder::get_allegro_version_git_hash()
{
   NcursesArt::GithubRepoStatusFetcher fetcher("allegro5");
   std::string result = fetcher.get_current_hash();
   return result;
}

std::string ReleaseInfoBuilder::get_allegro_version_git_branch()
{
   NcursesArt::GithubRepoStatusFetcher fetcher("allegro5");
   std::string result = fetcher.get_current_branch_name();
   return result;
}

int ReleaseInfoBuilder::get_allegro_version_git_num_commits()
{
   NcursesArt::GithubRepoStatusFetcher fetcher("allegro5");
   int result = fetcher.get_current_branch_num_commits();
   return result;
}

std::string ReleaseInfoBuilder::get_allegro_flare_version_git_hash()
{
   NcursesArt::GithubRepoStatusFetcher fetcher("allegro_flare");
   std::string result = fetcher.get_current_hash();
   return result;
}

int ReleaseInfoBuilder::get_allegro_flare_version_git_num_commits()
{
   NcursesArt::GithubRepoStatusFetcher fetcher("allegro_flare");
   int result = fetcher.get_current_branch_num_commits();
   return result;
}

std::string ReleaseInfoBuilder::get_allegro_flare_version_git_branch()
{
   NcursesArt::GithubRepoStatusFetcher fetcher("allegro_flare");
   std::string result = fetcher.get_current_branch_name();
   return result;
}

std::string ReleaseInfoBuilder::project_folder()
{
   return projects_folder + "/" + project_name;
}

bool ReleaseInfoBuilder::project_name_is_valid()
{
   // TODO: Test this case
   static const std::regex pattern("^[a-zA-Z_]+[a-zA-Z0-9_-]*$");
   return std::regex_match(project_name, pattern);
}

bool ReleaseInfoBuilder::project_folder_exists()
{
   return Blast::DirectoryExistenceChecker(project_folder()).exists();
}

bool ReleaseInfoBuilder::project_git_repo_active()
{
   // TODO: this function
   return true;
}

bool ReleaseInfoBuilder::allegro_folder_exists()
{
   // TODO: this function
   return true;
}

bool ReleaseInfoBuilder::allegro_git_repo_active()
{
   // TODO: this function
   return true;
}

bool ReleaseInfoBuilder::allegro_flare_folder_exists()
{
   // TODO: this function
   return true;
}

bool ReleaseInfoBuilder::allegro_flare_git_repo_active()
{
   // TODO: this function
   return true;
}


} // namespace Blast


