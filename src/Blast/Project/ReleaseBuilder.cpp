

#include <Blast/Project/ReleaseBuilder.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <iostream>


namespace Blast
{
namespace Project
{


ReleaseBuilder::ReleaseBuilder(std::string project_repo_name, std::string project_repo_base_path)
   : project_repo_name(project_repo_name)
   , project_repo_base_path(project_repo_base_path)
{
}


ReleaseBuilder::~ReleaseBuilder()
{
}


std::string ReleaseBuilder::get_project_repo_base_path()
{
   return project_repo_base_path;
}


std::vector<std::string> ReleaseBuilder::get_source_file_listing()
{
std::string response = Blast::ShellCommandExecutorWithCallback(
   "find -f **/*",
   ShellCommandExecutorWithCallback::simple_silent_callback
).execute();

std::vector<std::string> response_lines = StringSplitter(response, '\n').split();

return response_lines;

}

std::string ReleaseBuilder::run()
{
std::string project_path_name = "blast/";
std::string repos_base = std::string("/Users/markoates/Repos/") + project_path_name;

std::string project_source_path = "";
std::string project_destination_path = "";

// make folder if not exists
// releases/

// make folder if not exists
// releases/source/

// copy source files
// find src/**/*

// copy   releases/source/data/* files
// copy   releases/source/include/* files
// copy   releases/source/src/* files
// create releases/source/Makefile

//- al_load_bitmap
//- al_load_font
//- bitmaps
//- fonts

}
} // namespace Project
} // namespace Blast


