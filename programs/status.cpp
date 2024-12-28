#include <allegro5/allegro.h>
#include <map>

#include <NcursesArt/GithubRepoStatusFetcher.hpp>
#include <HostnameExtractor.hpp>

#include <iostream>
#include <iomanip> // for std::setw and std::setfill
#include <algorithm> // for std::find

#define PROPERTY_DELIMITER ": "

//cd ~/Repos/me
//git add programming_logs[>.log.txt




#define TERMINAL_COLOR_YELLOW "\033[1;33m"
#define TERMINAL_COLOR_RED "\033[1;31m"
#define TERMINAL_COLOR_GRAY "\033[1;37m"
#define TERMINAL_COLOR_DARK_GRAY "\033[1;30m"
#define TERMINAL_COLOR_GREEN "\033[1;32m"
#define TERMINAL_COLOR_BLUE "\033[1;34m"
#define TERMINAL_COLOR_LIGHT_BLUE "\033[1;94m"
#define TERMINAL_COLOR_RESET "\033[0m"




using NcursesArt::GithubRepoStatusFetcher;


class ProjectStatus
{
private:
   std::string repo_name;
   std::string repo_base_directory;

   bool exists_locally;
   bool in_sync;
   bool has_no_changed_files;
   bool has_no_untracked_files;
   bool has_no_staged_files;
   int num_local_branches;
   int num_remote_branches;

   GithubRepoStatusFetcher fetcher;

public:
   ProjectStatus(std::string repo_name, std::string repo_base_directory)
      : repo_name(repo_name)
      , repo_base_directory(repo_base_directory)
      , exists_locally(false)
      , in_sync(false)
      , has_no_changed_files(false)
      , has_no_untracked_files(false)
      , has_no_staged_files(false)
      , num_local_branches(-1)
      , num_remote_branches(-1)
      , fetcher(repo_name, repo_base_directory)
   {}

   std::string get_repo_base_directory()
   {
      return repo_base_directory;
   }

   std::string get_repo_name()
   {
      return repo_name;
   }

   bool get_exists_locally()
   {
      return exists_locally;
   }

   bool get_in_sync()
   {
      return in_sync;
   }

   bool get_has_no_changed_files()
   {
      return has_no_changed_files;
   }

   bool get_has_no_untracked_files()
   {
      return has_no_untracked_files;
   }

   int get_num_local_branches()
   {
      return num_local_branches;
   }

   int get_num_remote_branches()
   {
      return num_remote_branches;
   }

   int get_has_no_staged_files()
   {
      return has_no_staged_files;
   }

   void process()
   {
      exists_locally = fetcher.local_repo_exists();
      if (!exists_locally) return;

      in_sync = fetcher.is_the_repo_in_sync_with_remote();
      has_no_changed_files = !fetcher.has_file_changes();
      has_no_untracked_files = !fetcher.has_untracked_files();
      num_local_branches = fetcher.get_branch_count();
      has_no_staged_files = (fetcher.get_current_staged_files().size() == 0);
      num_remote_branches = fetcher.get_branch_count_at_remote();
   }
};


#include <sstream>
class ProgrammingLogsAutoSynchronizer
{
private:
   ProjectStatus project_status;

public:
   ProgrammingLogsAutoSynchronizer(std::string repo_base_directory)
      : project_status("me", repo_base_directory)
   {
   }

   void process()
   {
      std::cout << "Synchronizing programming logs" << std::endl;
      std::cout << "  - Pre-fetching \"me\" repo status" << std::endl;
      project_status.process();

      if (!project_status.get_in_sync())
      {
         if (
                  project_status.get_has_no_changed_files()
               && project_status.get_has_no_staged_files()
               && project_status.get_has_no_untracked_files()
            )
         {
            // Project is out of sync and clean
            // TODO: "git pull" here
         }
      }

      if (!project_status.get_in_sync())
      {
         std::stringstream command;
         command << TERMINAL_COLOR_BLUE << std::endl;
         command << "programs/status/ProgrammingLogsAutoSynchronizer: error: Me is not in sync. Consider the following command:" << std::endl;
         command << "======================" << std::endl;
         command << "cd " << project_status.get_repo_base_directory() << "me" << std::endl;
         command << "git reset" << std::endl;
         command << "git pull" << std::endl;
         command << "git add programming_logs/*.log.txt" << std::endl;
         command << "git commit -m \"+programming logs\"" << std::endl;
         command << "git push" << std::endl;
         command << "======================" << std::endl;
         command << TERMINAL_COLOR_RESET << std::endl;

         throw std::runtime_error(command.str());
      }
   }
};


#include <sstream>

std::map<std::string, std::pair<bool, ProjectStatus>> projects = {};

std::string diamond_it(std::string label, int number)
{
   std::stringstream result;
   bool check = number == 1;
   result << label;
   if (check) result << PROPERTY_DELIMITER << "🔹 ";
   else result << PROPERTY_DELIMITER << "🔸 ";
   result << number;

   return result.str();
}

std::string check_it(std::string label, bool check)
{
   std::stringstream result;
   result << label;
   if (check) result << PROPERTY_DELIMITER << "🔹 yes";
   else result << PROPERTY_DELIMITER << "🔸 no";
   return result.str();
}

std::string show_it(std::string label, std::string value)
{
   std::stringstream result;
   result << label << PROPERTY_DELIMITER << value;
   return result.str();
}


#include <StringVectorIntersection.hpp>


enum final_status_t
{
   NONE = 0,
   UNPROCESSED,
   CLEAN,
   NOT_PRESENT,
   UNSYNCED,
   SOME_CLUTTERED_FILES,
   EXTRA_LOCAL_BRANCHES,
   //EXTRA_REMOTE_BRANCHES,
};


final_status_t get_final_status(int num_local_branches, bool project_has_been_processed, bool exists_locally, bool in_sync, bool has_no_changed_files, bool has_no_untracked_files, bool has_no_staged_files)
{
   final_status_t status = CLEAN;

   if (project_has_been_processed == false) return UNPROCESSED;
   if (!exists_locally) { status = NOT_PRESENT; return status; };

   if (num_local_branches > 1) status = EXTRA_LOCAL_BRANCHES;
   if (!in_sync) status = UNSYNCED;
   if (!has_no_changed_files || !has_no_untracked_files || !has_no_staged_files) status = SOME_CLUTTERED_FILES;
   return status;
}


std::string get_hostname()
{
   return HostnameExtractor().get_computer_name();
}



std::string get_status_icon_and_text(final_status_t status, int num_local_branches, int num_remote_branches)
{
   std::string color_code;
   switch (status)
   {
   case NONE:
      return "⧄  none";
      break;
   case UNPROCESSED:
      return "▫️  unprocessed";
      break;
   case CLEAN:
      return TERMINAL_COLOR_LIGHT_BLUE "💎 clean" TERMINAL_COLOR_RESET;
      break;
   case NOT_PRESENT:
      return TERMINAL_COLOR_DARK_GRAY "☐ not present" TERMINAL_COLOR_RESET;
      break;
   case UNSYNCED:
      return TERMINAL_COLOR_RED "🔺 unsynced" TERMINAL_COLOR_RESET;
      break;
   case SOME_CLUTTERED_FILES:
      return TERMINAL_COLOR_YELLOW "🔸 some cluttered files" TERMINAL_COLOR_RESET;
      break;
   case EXTRA_LOCAL_BRANCHES:
      return std::string(TERMINAL_COLOR_BLUE "🔹 some extra local branches (") + std::to_string(num_local_branches) + ")" TERMINAL_COLOR_RESET;
      break;
   //case EXTRA_LOCAL_REMOTE_BRANCHES:
      //return std::string("🔹 some extra remote branches (") + std::to_string(num_remote_branches) + ")";
      //break;
   }

   return "🌌 status unknown";
}


bool have_all_projects_been_processed()
{
   for (auto &project : projects)
   {
      bool project_has_been_processed = project.second.first;
      if (!project_has_been_processed) return false;
   }
   return true;
}


int get_number_of_projects_processed()
{
   int projects_processed_count = 0;
   for (auto &project : projects)
   {
      bool project_has_been_processed = project.second.first;
      if (project_has_been_processed) projects_processed_count++;
   }
   return projects_processed_count;
}



std::string create_output_report()
{
   std::stringstream result_text;

   result_text << "[i] This tool does not check the status of *branches* within the repos" << std::endl << std::endl << std::endl;
   result_text << "[i] This tool does check if there are extra remote branches, but will not include it in the final evaluation." << std::endl << std::endl << std::endl;

   for (auto &project : projects)
   {
      ProjectStatus &project_status = project.second.second;
      bool exists_locally = project_status.get_exists_locally();
      bool in_sync = project_status.get_in_sync();
      bool has_no_changed_files = project_status.get_has_no_changed_files();
      bool has_no_untracked_files = project_status.get_has_no_untracked_files();
      bool has_no_staged_files = project_status.get_has_no_staged_files();
      int num_local_branches = project_status.get_num_local_branches();
      int num_remote_branches = project_status.get_num_remote_branches();
      std::string project_identifier = project.first;
      std::string repo_name = project_status.get_repo_name();
      bool project_has_been_processed = project.second.first;
      final_status_t final_status = get_final_status(num_local_branches, project_has_been_processed, exists_locally, in_sync, has_no_changed_files, has_no_untracked_files, has_no_staged_files);

      int longest_project_name_length = 24;
      int project_name_right_padding = 3;
      //std::setw(longest_project_name_length + project_name_right_padding) << std::setfill('-');
      std::string status_icon_and_text = " " + get_status_icon_and_text(final_status, num_local_branches, num_remote_branches);
      result_text
         << std::left << std::setw(longest_project_name_length + project_name_right_padding) << std::setfill('-') << (project_identifier + " ")
         << status_icon_and_text;
      if (project_has_been_processed == true && !(final_status == CLEAN || final_status == EXTRA_LOCAL_BRANCHES || final_status == NOT_PRESENT))
      {

         result_text << std::endl;
         result_text << std::endl;
         //result_text << "  " << show_it("repo name", repo_name) << std::endl;
         result_text << "  " << check_it("repo exists locally", exists_locally) << std::endl;
         result_text << "  " << diamond_it("num local branches", num_local_branches) << std::endl;
         result_text << "  " << diamond_it("num remote branches", num_remote_branches) << std::endl;
         result_text << "  " << check_it("in sync with remote", in_sync) << std::endl;
         result_text << "  " << check_it("has no changed files", has_no_changed_files) << std::endl;
         result_text << "  " << check_it("has no untracked files", has_no_untracked_files) << std::endl;
         result_text << "  " << check_it("has no staged files", has_no_staged_files) << std::endl;
      }
      result_text << std::endl;
   }

   //result_text << std::endl << "some processing messaging garbage:" << std::endl << std::endl << std::endl;

   //OUTPUT_REPORT_TEXT.set_text(result_text.str());
   return result_text.str();
}





//std::map<std::string, std::pair<bool, ProjectStatus>> projects = {};

#if defined(_WIN32) || defined(_WIN64)
#define REPOS_BASE_DIR "/msys64/home/Mark/Repos/"
#else
#define REPOS_BASE_DIR "~/Repos/"
#endif




int main(int argc, char **argv)
{
   std::string base_dir = REPOS_BASE_DIR;


   //ProgrammingLogsAutoSynchronizer programming_logs_auto_synchronizer(base_dir);
   //programming_logs_auto_synchronizer.process();


   projects = {
      //{ "Adventures of Beary",  { false, ProjectStatus("adventures-of-beary") } },
      //{ "Alex Park",            { false, ProjectStatus("AlexPark") } },
      //{ "HomeServer",       { false, ProjectStatus("HomeServer") } },
      { "LabyrinthOfLore",  { false, ProjectStatus("LabyrinthOfLore", base_dir) } },
      //{ "Peri",      { false, ProjectStatus("Peri") } },
      { "Solitare",          { false, ProjectStatus("Solitare", base_dir) } },
      { "CatDetective",          { false, ProjectStatus("CatDetective", base_dir) } },
      { "CubeShooter",          { false, ProjectStatus("CubeShooter", base_dir) } },
      //{ "allegro-planet",   { false, ProjectStatus("allegro-planet") } },
      //{ "allegroflare.github.io", { false, ProjectStatus("allegroflare.github.io") } },
      //{ "beary2d",              { false, ProjectStatus("beary2d") } },
      //{ "crayola",          { false, ProjectStatus("crayola") } },
      //{ "crayola-client",   { false, ProjectStatus("crayola-client") } },
      //{ "disclife",         { false, ProjectStatus("disclife") } },
      //{ "dungeon",              { false, ProjectStatus("dungeon") } },
      //{ "Tracko",  { false, ProjectStatus("Tracko", base_dir) } },
      { "first_vim_plugin", { false, ProjectStatus("first_vim_plugin", base_dir) } },
      //{ "flare_network",    { false, ProjectStatus("flare_network") } },
      //{ "fullscore",        { false, ProjectStatus("fullscore", base_dir) } },
      //{ "motris",               { false, ProjectStatus("motris", base_dir) } },
      //{ "tilemap",              { false, ProjectStatus("tilemap") } },
      { "FullScore3",  { false, ProjectStatus("FullScore3", base_dir) } },
      { "Golf2",  { false, ProjectStatus("Golf2", base_dir) } },
      { "RotateWorld",  { false, ProjectStatus("RotateWorld", base_dir) } },
      { "CollisionMesh",  { false, ProjectStatus("CollisionMesh", base_dir) } },
      { "Krampus24", { false, ProjectStatus("Krampus24", base_dir) } },
      { "CygnusAtratus", { false, ProjectStatus("CygnusAtratus", base_dir) } },
      { "Atratus", { false, ProjectStatus("Atratus", base_dir) } },
      { "Fade to White (Krampus21)", { false, ProjectStatus("Krampus21", base_dir) } },
      { ".dotfiles",        { false, ProjectStatus(".dotfiles", base_dir) } },
      { "Railway",  { false, ProjectStatus("Railway", base_dir) } },
      { "TileFPS",      { false, ProjectStatus("TileFPS", base_dir) } },
      { "Character3D",      { false, ProjectStatus("Character3D", base_dir) } },
      { "AlphaMesh",      { false, ProjectStatus("AlphaMesh", base_dir) } },
      { "Planar",      { false, ProjectStatus("Planar", base_dir) } },
      { "DragonWrath",      { false, ProjectStatus("DragonWrath", base_dir) } },
      { "AssetStudio",      { false, ProjectStatus("AssetStudio", base_dir) } },
      { "JourneyOfTheCat",      { false, ProjectStatus("JourneyOfTheCat", base_dir) } },
      //{ "Subscreen",      { false, ProjectStatus("Subscreen", base_dir) } },
      { "SomePlatformer",      { false, ProjectStatus("SomePlatformer", base_dir) } },
      { "AssetForgeCustomBlocks",      { false, ProjectStatus("AssetForgeCustomBlocks", base_dir) } },
      { "ChatGPT",      { false, ProjectStatus("ChatGPT", base_dir) } },
      { "KrampusReturns",      { false, ProjectStatus("KrampusReturns", base_dir) } },
      //{ "Releaser",      { false, ProjectStatus("Releaser", base_dir) } },
      { "Slug3D",               { false, ProjectStatus("slug_3d", base_dir) } },
      { "allegro_flare",    { false, ProjectStatus("allegro_flare", base_dir) } },
      { "beebot",           { false, ProjectStatus("beebot", base_dir) } },
      { "blast",            { false, ProjectStatus("blast", base_dir) } },
      { "ArtGalleryOfCats", { false, ProjectStatus("ArtGalleryOfCats", base_dir) } },
      { "SurviveTheCity", { false, ProjectStatus("SurviveTheCity", base_dir) } },
      //{ "dungeon",            { false, ProjectStatus("dungeon", base_dir) } },
      { "hexagon",          { false, ProjectStatus("hexagon", base_dir) } },
      { "lightracer-max",       { false, ProjectStatus("lightracer-max", base_dir) } },
      { "Robieo",       { false, ProjectStatus("Robieo", base_dir) } },
      { "me",               { false, ProjectStatus("me", base_dir) } },
      //{ "ncurses-art",      { false, ProjectStatus("ncurses-art") } },
      { "oatescodes",       { false, ProjectStatus("oatescodes", base_dir) } },
      //{ "tileo",                { false, ProjectStatus("tileo") } },
      //{ "union",            { false, ProjectStatus("union", base_dir) } },
      //{ "Wicked",            { false, ProjectStatus("Wicked") } },
      //{ "/Library/Application Support/Adobe/CEP/extensions", { false, ProjectStatus("unset") } },
   };


   //if (projects.empty()) return;

   int project_count = projects.size();
   int projects_processed = 0;

   for (auto &project : projects)
   {
      bool project_has_been_processed = project.second.first;
      if (!project_has_been_processed)
      {
         std::string project_identifier = project.first;
         ProjectStatus &project_status = project.second.second;
         bool &project_processed_state = project.second.first;

         std::cout << "processing " << (projects_processed+1) << " of " << project_count << ": " << project_identifier << "..." << std::flush;
         project_status.process();
         std::cout << " ✅ done." << std::endl << std::flush;
         project_processed_state = true;
         projects_processed++;

         //std::cout << "  report:" << std::endl;
         //std::cout << std::endl;
      }
   }


   std::cout << create_output_report() << std::endl;



   return 0;
}



