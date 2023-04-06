#pragma once


#include <Blast/BuildInfo.hpp>
#include <string>


namespace Blast
{
   class BuildInfoBuilder
   {
   private:
      bool project_git_repo_active();
      bool allegro_folder_exists();
      bool allegro_git_repo_active();
      bool allegro_flare_folder_exists();
      bool allegro_flare_git_repo_active();

   protected:


   public:
      BuildInfoBuilder();
      ~BuildInfoBuilder();

      Blast::BuildInfo build();
      std::string get_allegro_version_git_hash();
      std::string get_allegro_version_git_branch();
      int get_allegro_version_git_num_commits();
      std::string get_allegro_version_git_latest_commit_date_and_time();
   };
}



