

#include <Blast/Project/HardCodedPathInfrencer.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/String/Trimmer.hpp>
#include <Blast/StringSplitter.hpp>
#include <algorithm>
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
   Blast::ShellCommandExecutorWithCallback executor(
         get_git_command(),
         ShellCommandExecutorWithCallback::simple_silent_callback
      );
   std::string execution_result = executor.execute();
   std::vector<std::string> tokens = Blast::StringSplitter(execution_result, '\n').split();
   tokens = remove_empty(trim_each(tokens));

   return { tokens.empty(), tokens };
}

std::vector<std::string> HardCodedPathInfrencer::trim_each(std::vector<std::string> tokens)
{
   for (auto &s : tokens)
   {
      // ltrim
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
      // rtrim
      s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) {return !std::isspace(c);}).base(), s.end());
   }
   return tokens;
}

std::vector<std::string> HardCodedPathInfrencer::remove_empty(std::vector<std::string> strVector)
{
   // Use the erase-remove idiom to remove empty strings
   strVector.erase(
         std::remove_if(strVector.begin(), strVector.end(), [](const std::string& str)
               {
                  return str.empty();
               }),
               strVector.end());
   return strVector;
}


} // namespace Project
} // namespace Blast


