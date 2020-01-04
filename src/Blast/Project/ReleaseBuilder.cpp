

#include <Blast/Project/ReleaseBuilder.hpp>
#include <fstream>
#include <fstream>
#include <iostream>
#include <Blast/Project/SymlinkChecker.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <cstdio>
#include <sstream>


namespace Blast
{
namespace Project
{


ReleaseBuilder::ReleaseBuilder(std::string base_directory)
   : base_directory(base_directory)
{
}


ReleaseBuilder::~ReleaseBuilder()
{
}


void ReleaseBuilder::copy_file(std::string source_filename, std::string destination_filename)
{
std::ifstream src(source_filename, std::ios::binary);
std::ofstream dst(destination_filename,   std::ios::binary);
dst << src.rdbuf();

}

std::vector<std::pair<std::string, std::string>> ReleaseBuilder::list_symlinks()
{
std::string command = std::string("find ") + base_directory;
Blast::ShellCommandExecutorWithCallback executor(command, ShellCommandExecutorWithCallback::simple_silent_callback);
std::string executor_result = executor.execute();
StringSplitter splitter(executor_result, '\n');

std::vector<std::string> filenames = splitter.split();
std::vector<std::pair<std::string, std::string>> result;

for (auto &filename : filenames)
{
   Blast::Project::SymlinkChecker symlink_checker(filename);
   if (symlink_checker.is_symlink())
   {
      std::pair<std::string, std::string> this_symlink_info{ filename, symlink_checker.read_symlink_target() };
      result.push_back(this_symlink_info);
   }
}

return result;

}

void ReleaseBuilder::replace_symlinks_with_copies_of_linked_files()
{
std::vector<std::pair<std::string, std::string>> symlinks = list_symlinks();

for (auto &symlink : symlinks)
{
   std::string file_to_remove = symlink.first;
   std::string file_to_copy_source = symlink.second;
   std::string file_to_copy_destination = symlink.first;

   if (remove(file_to_remove.c_str()) != 0)
   {
      std::stringstream error_message;
      error_message << "There was an error trying to delete the file \"" << file_to_remove << "\"" << std::endl;
      throw std::runtime_error(error_message.str());
   }

   copy_file(file_to_copy_source, file_to_copy_destination);
}
return;

}
} // namespace Project
} // namespace Blast


