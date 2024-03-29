#pragma once


#include <string>
#include <vector>


namespace NcursesArt
{
   class GithubRepoStatusFetcher
   {
   public:
      static constexpr char* GIT_STATUS_COMMAND = (char*)"git status -uno -u";

   private:
      std::string repo_name;
      std::string repos_directory;
      std::string last_captured_output_from_status_request;
      bool only_poll_once;
      bool status_polled;
      std::string git_pull_command;
      std::string git_precheck_pull_has_no_conflicts_command;
      std::string git_branch_count_command;
      std::string git_current_branch_command;
      std::string git_current_branch_num_commits_command;
      std::string git_latest_commit_date_and_time_command;
      std::string git_current_hash_command;
      std::string git_remote_branch_names_command;
      std::string component_quintessence_filenames_command;
      std::string git_current_staged_files_command;
      std::string git_is_clean_command;

   protected:


   public:
      GithubRepoStatusFetcher(std::string repo_name="blast", std::string repos_directory="~/Repos");
      ~GithubRepoStatusFetcher();

      void set_status_polled(bool status_polled);
      std::string get_repo_name() const;
      std::string get_repos_directory() const;
      std::string get_last_captured_output_from_status_request() const;
      bool get_only_poll_once() const;
      bool get_status_polled() const;
      std::string get_git_pull_command() const;
      std::string get_git_precheck_pull_has_no_conflicts_command() const;
      std::string get_git_branch_count_command() const;
      std::string get_git_current_branch_command() const;
      std::string get_git_current_branch_num_commits_command() const;
      std::string get_git_latest_commit_date_and_time_command() const;
      std::string get_git_current_hash_command() const;
      std::string get_git_remote_branch_names_command() const;
      std::string get_component_quintessence_filenames_command() const;
      std::string get_git_current_staged_files_command() const;
      std::string get_git_is_clean_command() const;
      bool local_repo_exists();
      bool has_file_changes();
      bool has_untracked_files();
      bool is_the_repo_in_sync_with_remote();
      bool is_the_local_repo_ahead();
      bool is_the_local_repo_behind();
      bool is_clean();
      std::string get_current_hash();
      int get_branch_count();
      int get_current_branch_num_commits();
      std::string get_latest_commit_date_and_time();
      std::vector<std::string> get_branch_names_at_remote();
      int get_branch_count_at_remote();
      bool is_current_branch_master();
      std::string get_current_branch_name_command();
      std::string get_pull_command();
      std::string get_precheck_pull_has_no_conflicts_command();
      std::string get_status_command();
      std::string get_current_staged_files_command();
      std::string get_is_clean_command();
      std::vector<std::string> get_current_staged_files();
      std::string get_current_branch_name();
      std::vector<std::string> get_quintessence_filenames();
      bool have_the_local_and_remote_repos_diverged();
      bool last_captured_output_from_status_request_contains_string(std::string string_to_find);
      bool poll_status();
      std::string execute_command(std::string command);
   };
}



