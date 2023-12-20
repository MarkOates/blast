

#include <Blast/Project/HardCodedPathInfrencer.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/String/Trimmer.hpp>
#include <sstream>


namespace Blast
{
namespace Project
{


HardCodedPathInfrencer::HardCodedPathInfrencer()
{
}


HardCodedPathInfrencer::~HardCodedPathInfrencer()
{
}


std::string HardCodedPathInfrencer::get_git_command()
{
   std::stringstream command;
   command << "git grep --untracked --break \"/Users/markoates/Repos\" "
           << "\":(exclude)./documentation/*\" \":(exclude)./include/lib/*\""
           ;
   return command.str();
}

std::pair<bool, std::vector<std::string>> HardCodedPathInfrencer::check_for_hard_coded_paths()
{
   //std::pair<bool, std::vector<std::string>> result;
   Blast::ShellCommandExecutorWithCallback executor(
         get_git_command(),
         ShellCommandExecutorWithCallback::simple_silent_callback
      );
   std::string execution_result = executor.execute();
   std::string trimmed_result = Blast::String::Trimmer(execution_result).trim();

   // TODO: Split "result" into multiple lines
   return std::pair<bool, std::vector<std::string>>(trimmed_result.empty(), { execution_result });
}


} // namespace Project
} // namespace Blast


