

#include <Blast/BuildInfo.hpp>




namespace Blast
{


BuildInfo::BuildInfo()
   : time_of_build("[unset]")
   , building_platform_os_name("[unset]")
   , building_platform_os_version("[unset]")
   , building_platform_chipset("[unset]")
   , compiler_name("[unset]")
   , compiler_version("[unset]")
   , allegro_version_num("[unset]")
   , allegro_version_git_branch("[unset]")
   , allegro_version_git_hash("[unset]")
   , allegro_version_git_latest_commit_date_and_time("[unset]")
   , allegro_version_git_num_commits(0)
{
}


BuildInfo::~BuildInfo()
{
}


void BuildInfo::set_time_of_build(std::string time_of_build)
{
   this->time_of_build = time_of_build;
}


void BuildInfo::set_building_platform_os_name(std::string building_platform_os_name)
{
   this->building_platform_os_name = building_platform_os_name;
}


void BuildInfo::set_building_platform_os_version(std::string building_platform_os_version)
{
   this->building_platform_os_version = building_platform_os_version;
}


void BuildInfo::set_building_platform_chipset(std::string building_platform_chipset)
{
   this->building_platform_chipset = building_platform_chipset;
}


void BuildInfo::set_compiler_name(std::string compiler_name)
{
   this->compiler_name = compiler_name;
}


void BuildInfo::set_compiler_version(std::string compiler_version)
{
   this->compiler_version = compiler_version;
}


void BuildInfo::set_allegro_version_num(std::string allegro_version_num)
{
   this->allegro_version_num = allegro_version_num;
}


void BuildInfo::set_allegro_version_git_branch(std::string allegro_version_git_branch)
{
   this->allegro_version_git_branch = allegro_version_git_branch;
}


void BuildInfo::set_allegro_version_git_hash(std::string allegro_version_git_hash)
{
   this->allegro_version_git_hash = allegro_version_git_hash;
}


void BuildInfo::set_allegro_version_git_latest_commit_date_and_time(std::string allegro_version_git_latest_commit_date_and_time)
{
   this->allegro_version_git_latest_commit_date_and_time = allegro_version_git_latest_commit_date_and_time;
}


void BuildInfo::set_allegro_version_git_num_commits(int allegro_version_git_num_commits)
{
   this->allegro_version_git_num_commits = allegro_version_git_num_commits;
}


std::string BuildInfo::get_time_of_build() const
{
   return time_of_build;
}


std::string BuildInfo::get_building_platform_os_name() const
{
   return building_platform_os_name;
}


std::string BuildInfo::get_building_platform_os_version() const
{
   return building_platform_os_version;
}


std::string BuildInfo::get_building_platform_chipset() const
{
   return building_platform_chipset;
}


std::string BuildInfo::get_compiler_name() const
{
   return compiler_name;
}


std::string BuildInfo::get_compiler_version() const
{
   return compiler_version;
}


std::string BuildInfo::get_allegro_version_num() const
{
   return allegro_version_num;
}


std::string BuildInfo::get_allegro_version_git_branch() const
{
   return allegro_version_git_branch;
}


std::string BuildInfo::get_allegro_version_git_hash() const
{
   return allegro_version_git_hash;
}


std::string BuildInfo::get_allegro_version_git_latest_commit_date_and_time() const
{
   return allegro_version_git_latest_commit_date_and_time;
}


int BuildInfo::get_allegro_version_git_num_commits() const
{
   return allegro_version_git_num_commits;
}




} // namespace Blast


