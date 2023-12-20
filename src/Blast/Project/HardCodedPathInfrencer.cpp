

#include <Blast/Project/HardCodedPathInfrencer.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/String/Trimmer.hpp>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Blast
{
namespace Project
{


HardCodedPathInfrencer::HardCodedPathInfrencer(std::string project_directory)
   : project_directory(project_directory)
{
}


HardCodedPathInfrencer::~HardCodedPathInfrencer()
{
}


void HardCodedPathInfrencer::set_project_directory(std::string project_directory)
{
   this->project_directory = project_directory;
}


std::string HardCodedPathInfrencer::get_project_directory() const
{
   return project_directory;
}


std::string HardCodedPathInfrencer::get_git_command()
{
   if (!(std::filesystem::exists(project_directory)))
   {
      std::stringstream error_message;
      error_message << "[HardCodedPathInfrencer::get_git_command]: error: guard \"std::filesystem::exists(project_directory)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("HardCodedPathInfrencer::get_git_command: error: guard \"std::filesystem::exists(project_directory)\" not met");
   }
   std::stringstream command;
   command << "(cd " << project_directory << " && "
              << "git grep --untracked --break \"/Users/markoates\" "
              << "\":(exclude)./documentation/*\" "
              << "\":(exclude)./include/lib/*\" "
              << "\":(exclude)./tests/*\" " // NOTE: Excluding tests, consider removing this exclusion
           << ")"
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


