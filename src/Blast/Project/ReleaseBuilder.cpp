

#include <Blast/Project/ReleaseBuilder.hpp>
#include <sstream>
#include <Blast/StringSplitter.hpp>
#include <Blast/DirectoryCreator.hpp>
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
std::stringstream command;

command << "(cd " << project_repo_base_path << project_repo_name << " && " << "find -f **/*)";

std::string response = Blast::ShellCommandExecutorWithCallback(
   command.str(),
   ShellCommandExecutorWithCallback::simple_silent_callback
).execute();

std::vector<std::string> response_lines = StringSplitter(response, '\n').split();

return response_lines;

}

std::vector<std::string> ReleaseBuilder::build_repo_base_path_directory_components()
{
return StringSplitter(project_repo_base_path, '/').split();
}

std::vector<std::string> ReleaseBuilder::build_include_folder_directory_components()
{
std::vector<std::string> result = StringSplitter(project_repo_base_path, '/').split();
result.push_back("releases");
result.push_back("include");
return result;

}

void ReleaseBuilder::create_folders()
{
// make folder if not exists
// releases/
//bool result = Blast::DirectoryCreator({
//},
//true).create();

//if (result != 0) { throw std::runtime_error("could not create directories"); }

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


