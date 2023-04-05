#pragma once


#include <set>
#include <string>


namespace Blast
{
   class ReleaseInfo
   {
   private:
      std::string project_git_branch;
      std::string project_git_hash;
      int project_git_num_commits;
      std::string project_git_latest_commit_date_and_time;
      int version_number_major;
      int version_number_minor;
      int version_number_patch;
      std::set<std::string> version_number_labels;
      std::set<std::string> version_number_metadata;
      std::string time_of_source_release;
      int build_number;
      std::string time_of_build;
      std::string building_platform_os_name;
      std::string building_platform_os_version;
      std::string building_platform_chipset;
      std::string compiler_name;
      std::string compiler_version;
      std::string allegro_version_num;
      std::string allegro_version_git_branch;
      std::string allegro_version_git_hash;
      std::string allegro_version_git_latest_commit_date_and_time;
      int allegro_version_git_num_commits;
      std::string allegro_flare_version_num;
      std::string allegro_flare_version_git_branch;
      std::string allegro_flare_version_git_hash;
      std::string allegro_flare_version_git_latest_commit_date_and_time;
      int allegro_flare_version_git_num_commits;

   protected:


   public:
      ReleaseInfo();
      ~ReleaseInfo();

      void set_project_git_branch(std::string project_git_branch);
      void set_project_git_hash(std::string project_git_hash);
      void set_project_git_num_commits(int project_git_num_commits);
      void set_project_git_latest_commit_date_and_time(std::string project_git_latest_commit_date_and_time);
      void set_version_number_major(int version_number_major);
      void set_version_number_minor(int version_number_minor);
      void set_version_number_patch(int version_number_patch);
      void set_version_number_labels(std::set<std::string> version_number_labels);
      void set_version_number_metadata(std::set<std::string> version_number_metadata);
      void set_time_of_source_release(std::string time_of_source_release);
      void set_build_number(int build_number);
      void set_time_of_build(std::string time_of_build);
      void set_building_platform_os_name(std::string building_platform_os_name);
      void set_building_platform_os_version(std::string building_platform_os_version);
      void set_building_platform_chipset(std::string building_platform_chipset);
      void set_compiler_name(std::string compiler_name);
      void set_compiler_version(std::string compiler_version);
      void set_allegro_version_num(std::string allegro_version_num);
      void set_allegro_version_git_branch(std::string allegro_version_git_branch);
      void set_allegro_version_git_hash(std::string allegro_version_git_hash);
      void set_allegro_version_git_latest_commit_date_and_time(std::string allegro_version_git_latest_commit_date_and_time);
      void set_allegro_version_git_num_commits(int allegro_version_git_num_commits);
      void set_allegro_flare_version_num(std::string allegro_flare_version_num);
      void set_allegro_flare_version_git_branch(std::string allegro_flare_version_git_branch);
      void set_allegro_flare_version_git_hash(std::string allegro_flare_version_git_hash);
      void set_allegro_flare_version_git_latest_commit_date_and_time(std::string allegro_flare_version_git_latest_commit_date_and_time);
      void set_allegro_flare_version_git_num_commits(int allegro_flare_version_git_num_commits);
      std::string get_project_git_branch() const;
      std::string get_project_git_hash() const;
      int get_project_git_num_commits() const;
      std::string get_project_git_latest_commit_date_and_time() const;
      int get_version_number_major() const;
      int get_version_number_minor() const;
      int get_version_number_patch() const;
      std::set<std::string> get_version_number_labels() const;
      std::set<std::string> get_version_number_metadata() const;
      std::string get_time_of_source_release() const;
      int get_build_number() const;
      std::string get_time_of_build() const;
      std::string get_building_platform_os_name() const;
      std::string get_building_platform_os_version() const;
      std::string get_building_platform_chipset() const;
      std::string get_compiler_name() const;
      std::string get_compiler_version() const;
      std::string get_allegro_version_num() const;
      std::string get_allegro_version_git_branch() const;
      std::string get_allegro_version_git_hash() const;
      std::string get_allegro_version_git_latest_commit_date_and_time() const;
      int get_allegro_version_git_num_commits() const;
      std::string get_allegro_flare_version_num() const;
      std::string get_allegro_flare_version_git_branch() const;
      std::string get_allegro_flare_version_git_hash() const;
      std::string get_allegro_flare_version_git_latest_commit_date_and_time() const;
      int get_allegro_flare_version_git_num_commits() const;
      void set_project_version(int version_number_major=0, int version_number_minor=0, int version_number_patch=0, std::set<std::string> version_number_labels={}, std::set<std::string> version_number_metadata={});
      std::string build_project_version_string();
   };
}



