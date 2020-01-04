

#include <Blast/Project/ReleaseBuilder.hpp>
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


std::pair<std::string, std::string> ReleaseBuilder::list_symlinks()
{
std::string command = "find ~/Desktop/Release";
Blast::ShellCommandExecutorWithCallback executor(command);
std::string result = executor.execute();
StringSplitter splitter(result, '\n');

return {};

}
} // namespace Project
} // namespace Blast


