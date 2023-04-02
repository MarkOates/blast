

#include <Blast/ReleaseInfo.hpp>




namespace Blast
{


ReleaseInfo::ReleaseInfo()
   : project_git_branch("[unset]")
   , project_git_hash("[unset]")
   , project_git_num_commits(0)
   , project_git_latest_commit_date_and_time("[unset]")
   , version_number_major(0)
   , version_number_minor(0)
   , version_number_patch(0)
   , version_number_labels({})
   , version_number_metadata({})
   , build_number(0)
   , time_of_build("[unset]")
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
   , allegro_flare_version_num("[unset]")
   , allegro_flare_version_git_branch("[unset]")
   , allegro_flare_version_git_hash("[unset]")
   , allegro_flare_version_git_latest_commit_date_and_time("[unset]")
   , allegro_flare_version_git_num_commits(0)
{
}


ReleaseInfo::~ReleaseInfo()
{
}


void ReleaseInfo::set_project_git_branch(std::string project_git_branch)
{
   this->project_git_branch = project_git_branch;
}


void ReleaseInfo::set_project_git_hash(std::string project_git_hash)
{
   this->project_git_hash = project_git_hash;
}


void ReleaseInfo::set_project_git_num_commits(int project_git_num_commits)
{
   this->project_git_num_commits = project_git_num_commits;
}


void ReleaseInfo::set_project_git_latest_commit_date_and_time(std::string project_git_latest_commit_date_and_time)
{
   this->project_git_latest_commit_date_and_time = project_git_latest_commit_date_and_time;
}


void ReleaseInfo::set_version_number_major(int version_number_major)
{
   this->version_number_major = version_number_major;
}


void ReleaseInfo::set_version_number_minor(int version_number_minor)
{
   this->version_number_minor = version_number_minor;
}


void ReleaseInfo::set_version_number_patch(int version_number_patch)
{
   this->version_number_patch = version_number_patch;
}


void ReleaseInfo::set_version_number_labels(std::vector<std::string> version_number_labels)
{
   this->version_number_labels = version_number_labels;
}


void ReleaseInfo::set_version_number_metadata(std::vector<std::string> version_number_metadata)
{
   this->version_number_metadata = version_number_metadata;
}


void ReleaseInfo::set_build_number(int build_number)
{
   this->build_number = build_number;
}


void ReleaseInfo::set_time_of_build(std::string time_of_build)
{
   this->time_of_build = time_of_build;
}


void ReleaseInfo::set_building_platform_os_name(std::string building_platform_os_name)
{
   this->building_platform_os_name = building_platform_os_name;
}


void ReleaseInfo::set_building_platform_os_version(std::string building_platform_os_version)
{
   this->building_platform_os_version = building_platform_os_version;
}


void ReleaseInfo::set_building_platform_chipset(std::string building_platform_chipset)
{
   this->building_platform_chipset = building_platform_chipset;
}


void ReleaseInfo::set_compiler_name(std::string compiler_name)
{
   this->compiler_name = compiler_name;
}


void ReleaseInfo::set_compiler_version(std::string compiler_version)
{
   this->compiler_version = compiler_version;
}


void ReleaseInfo::set_allegro_version_num(std::string allegro_version_num)
{
   this->allegro_version_num = allegro_version_num;
}


void ReleaseInfo::set_allegro_version_git_branch(std::string allegro_version_git_branch)
{
   this->allegro_version_git_branch = allegro_version_git_branch;
}


void ReleaseInfo::set_allegro_version_git_hash(std::string allegro_version_git_hash)
{
   this->allegro_version_git_hash = allegro_version_git_hash;
}


void ReleaseInfo::set_allegro_version_git_latest_commit_date_and_time(std::string allegro_version_git_latest_commit_date_and_time)
{
   this->allegro_version_git_latest_commit_date_and_time = allegro_version_git_latest_commit_date_and_time;
}


void ReleaseInfo::set_allegro_version_git_num_commits(int allegro_version_git_num_commits)
{
   this->allegro_version_git_num_commits = allegro_version_git_num_commits;
}


void ReleaseInfo::set_allegro_flare_version_num(std::string allegro_flare_version_num)
{
   this->allegro_flare_version_num = allegro_flare_version_num;
}


void ReleaseInfo::set_allegro_flare_version_git_branch(std::string allegro_flare_version_git_branch)
{
   this->allegro_flare_version_git_branch = allegro_flare_version_git_branch;
}


void ReleaseInfo::set_allegro_flare_version_git_hash(std::string allegro_flare_version_git_hash)
{
   this->allegro_flare_version_git_hash = allegro_flare_version_git_hash;
}


void ReleaseInfo::set_allegro_flare_version_git_latest_commit_date_and_time(std::string allegro_flare_version_git_latest_commit_date_and_time)
{
   this->allegro_flare_version_git_latest_commit_date_and_time = allegro_flare_version_git_latest_commit_date_and_time;
}


void ReleaseInfo::set_allegro_flare_version_git_num_commits(int allegro_flare_version_git_num_commits)
{
   this->allegro_flare_version_git_num_commits = allegro_flare_version_git_num_commits;
}


std::string ReleaseInfo::get_project_git_branch() const
{
   return project_git_branch;
}


std::string ReleaseInfo::get_project_git_hash() const
{
   return project_git_hash;
}


int ReleaseInfo::get_project_git_num_commits() const
{
   return project_git_num_commits;
}


std::string ReleaseInfo::get_project_git_latest_commit_date_and_time() const
{
   return project_git_latest_commit_date_and_time;
}


int ReleaseInfo::get_version_number_major() const
{
   return version_number_major;
}


int ReleaseInfo::get_version_number_minor() const
{
   return version_number_minor;
}


int ReleaseInfo::get_version_number_patch() const
{
   return version_number_patch;
}


std::vector<std::string> ReleaseInfo::get_version_number_labels() const
{
   return version_number_labels;
}


std::vector<std::string> ReleaseInfo::get_version_number_metadata() const
{
   return version_number_metadata;
}


int ReleaseInfo::get_build_number() const
{
   return build_number;
}


std::string ReleaseInfo::get_time_of_build() const
{
   return time_of_build;
}


std::string ReleaseInfo::get_building_platform_os_name() const
{
   return building_platform_os_name;
}


std::string ReleaseInfo::get_building_platform_os_version() const
{
   return building_platform_os_version;
}


std::string ReleaseInfo::get_building_platform_chipset() const
{
   return building_platform_chipset;
}


std::string ReleaseInfo::get_compiler_name() const
{
   return compiler_name;
}


std::string ReleaseInfo::get_compiler_version() const
{
   return compiler_version;
}


std::string ReleaseInfo::get_allegro_version_num() const
{
   return allegro_version_num;
}


std::string ReleaseInfo::get_allegro_version_git_branch() const
{
   return allegro_version_git_branch;
}


std::string ReleaseInfo::get_allegro_version_git_hash() const
{
   return allegro_version_git_hash;
}


std::string ReleaseInfo::get_allegro_version_git_latest_commit_date_and_time() const
{
   return allegro_version_git_latest_commit_date_and_time;
}


int ReleaseInfo::get_allegro_version_git_num_commits() const
{
   return allegro_version_git_num_commits;
}


std::string ReleaseInfo::get_allegro_flare_version_num() const
{
   return allegro_flare_version_num;
}


std::string ReleaseInfo::get_allegro_flare_version_git_branch() const
{
   return allegro_flare_version_git_branch;
}


std::string ReleaseInfo::get_allegro_flare_version_git_hash() const
{
   return allegro_flare_version_git_hash;
}


std::string ReleaseInfo::get_allegro_flare_version_git_latest_commit_date_and_time() const
{
   return allegro_flare_version_git_latest_commit_date_and_time;
}


int ReleaseInfo::get_allegro_flare_version_git_num_commits() const
{
   return allegro_flare_version_git_num_commits;
}




} // namespace Blast


