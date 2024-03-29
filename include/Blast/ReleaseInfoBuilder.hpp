#pragma once


#include <Blast/ReleaseInfo.hpp>
#include <string>


namespace Blast
{
   class ReleaseInfoBuilder
   {
   private:
      std::string project_name;
      std::string projects_folder;
      std::string project_folder();
      bool project_folder_exists();
      bool project_git_repo_active();
      bool allegro_folder_exists();
      bool allegro_git_repo_active();
      bool allegro_flare_folder_exists();
      bool allegro_flare_git_repo_active();

   protected:


   public:
      ReleaseInfoBuilder(std::string project_name="[unset]", std::string projects_folder="/Users/markoates/Repos");
      ~ReleaseInfoBuilder();

      void set_project_name(std::string project_name);
      void set_projects_folder(std::string projects_folder);
      std::string get_project_name() const;
      std::string get_projects_folder() const;
      Blast::ReleaseInfo build();
      std::string get_project_git_hash();
      std::string get_project_git_branch();
      int get_project_git_num_commits();
      std::string get_project_git_latest_commit_date_and_time();
      std::string get_allegro_version_git_hash();
      std::string get_allegro_version_git_branch();
      int get_allegro_version_git_num_commits();
      std::string get_allegro_version_git_latest_commit_date_and_time();
      std::string get_allegro_flare_version_git_hash();
      int get_allegro_flare_version_git_num_commits();
      std::string get_allegro_flare_version_git_branch();
      std::string get_allegro_flare_version_git_latest_commit_date_and_time();
      std::string get_blast_version_git_hash();
      int get_blast_version_git_num_commits();
      std::string get_blast_version_git_branch();
      std::string get_blast_version_git_latest_commit_date_and_time();
      bool project_name_is_valid();
   };
}



