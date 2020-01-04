

#include <Blast/Project/ReleaseBuilder.hpp>
#include <Blast/Project/SymlinkChecker.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>


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


std::vector<std::pair<std::string, std::string>> ReleaseBuilder::list_symlinks()
{
std::string command = "find ~/Desktop/Release";
Blast::ShellCommandExecutorWithCallback executor(command);
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
} // namespace Project
} // namespace Blast


