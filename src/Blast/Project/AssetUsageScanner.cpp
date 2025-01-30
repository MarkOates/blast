

#include <Blast/Project/AssetUsageScanner.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/String/Trimmer.hpp>
#include <Blast/StringSplitter.hpp>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <stdexcept>


namespace Blast
{
namespace Project
{


AssetUsageScanner::AssetUsageScanner(std::string project_directory)
   : project_directory(project_directory)
{
}


AssetUsageScanner::~AssetUsageScanner()
{
}


void AssetUsageScanner::set_project_directory(std::string project_directory)
{
   this->project_directory = project_directory;
}


std::string AssetUsageScanner::get_project_directory() const
{
   return project_directory;
}


std::string AssetUsageScanner::get_git_command()
{
   if (!(std::filesystem::exists(project_directory)))
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::AssetUsageScanner::get_git_command]: error: guard \"std::filesystem::exists(project_directory)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Project::AssetUsageScanner::get_git_command]: error: guard \"std::filesystem::exists(project_directory)\" not met");
   }
   std::stringstream command;
   command << "(cd " << project_directory << " && "
              << "git grep --untracked --break \"asset_studio::\" "
              << "\":(exclude)./documentation/*\" "
              << "\":(exclude)./include/lib/*\" "
              << "\":(exclude)./project_files/*\" "
              << "\":(exclude)./tmp/*\" "
              << "\":(exclude)./scripts/*\" "
              << "\":(exclude)./tests/*\" " // NOTE: Excluding tests, consider removing this exclusion
           << ")"
           ;
   return command.str();
}

std::string AssetUsageScanner::build_comma_separated_unique_asset_identifier_list(std::vector<std::pair<std::string, std::string>>* asset_studio_data, std::string separator)
{
   if (!(asset_studio_data))
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::AssetUsageScanner::build_comma_separated_unique_asset_identifier_list]: error: guard \"asset_studio_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Project::AssetUsageScanner::build_comma_separated_unique_asset_identifier_list]: error: guard \"asset_studio_data\" not met");
   }
   if (!asset_studio_data) return "";

   std::ostringstream result_stream;
   std::set<std::string> unique_items;

   // Extract unique elements
   for (const auto &entry : *asset_studio_data)
   {
      unique_items.insert(entry.second);
   }

   // Format as quoted strings
   auto it = unique_items.begin();
   while (it != unique_items.end())
   {
      result_stream << "\"" << *it << "\"";
      if (++it != unique_items.end())
      {
         result_stream << separator;
      }
   }

   return result_stream.str();
}

std::vector<std::pair<std::string, std::string>> AssetUsageScanner::extract_asset_studio_data(std::vector<std::string>* lines)
{
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::AssetUsageScanner::extract_asset_studio_data]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Project::AssetUsageScanner::extract_asset_studio_data]: error: guard \"lines\" not met");
   }
   std::vector<std::pair<std::string, std::string>> results;
   std::regex asset_regex(R"(asset_studio::([^\"}]+))");

   for (const std::string &line : *lines)
   {
      std::smatch match;
      if (std::regex_search(line, match, asset_regex))
      {
         std::string full_match = match.str(0);
         std::string trimmed_match = match.str(1);
         results.emplace_back(full_match, trimmed_match);
      }
   }
   return results;
}

std::pair<bool, std::vector<std::string>> AssetUsageScanner::check_for_prefixed_assets()
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

std::vector<std::string> AssetUsageScanner::trim_each(std::vector<std::string> tokens)
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

std::vector<std::string> AssetUsageScanner::remove_empty(std::vector<std::string> strVector)
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


