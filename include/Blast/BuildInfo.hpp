#pragma once


#include <string>


namespace Blast
{
   class BuildInfo
   {
   private:
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

   protected:


   public:
      BuildInfo();
      ~BuildInfo();

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
   };
}



