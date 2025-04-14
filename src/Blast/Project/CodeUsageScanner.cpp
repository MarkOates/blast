

#include <Blast/Project/CodeUsageScanner.hpp>

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
#include <string>


namespace Blast
{
namespace Project
{


CodeUsageScanner::CodeUsageScanner(std::string project_directory)
   : project_directory(project_directory)
{
}


CodeUsageScanner::~CodeUsageScanner()
{
}


void CodeUsageScanner::set_project_directory(std::string project_directory)
{
   this->project_directory = project_directory;
}


std::string CodeUsageScanner::get_project_directory() const
{
   return project_directory;
}


std::pair<bool, std::string> CodeUsageScanner::build_report()
{
   std::stringstream result_report;

   std::unordered_map<std::string, std::string> common_required_headers = build_common_required_headers_list();
   bool all_clear = true;
   for (auto &common_required_header : common_required_headers)
   {
      std::string token = common_required_header.first;

      Blast::ShellCommandExecutorWithCallback executor(
            build_scan_shell_command(token),
            ShellCommandExecutorWithCallback::simple_silent_callback
         );
      std::string execution_result = executor.execute();
      std::vector<std::string> execution_result_as_lines = Blast::StringSplitter(execution_result, '\n').split();
      std::vector<std::pair<std::string, std::string>> tokenized_found_occurrences =
         tokenize_lines(&execution_result_as_lines);

      for (auto &tokenized_found_occurrence : tokenized_found_occurrences)
      {
         std::string &filename = tokenized_found_occurrence.first;
         std::string &line = tokenized_found_occurrence.second;

         result_report << "\"" << token << "\"" << " found in \"" << filename << "\" with line " << line << std::endl;

         // See if required header is present in this file
         std::string required_header_token = obtain_required_header_for_token(token);
         bool header_token_exists_in_file = token_exists_in_file(filename, required_header_token);

         if (!header_token_exists_in_file)
         {
            result_report << "    !! header token \"" << required_header_token << "\" not found" << std::endl;
            all_clear = false;
         }
         else
         {
            result_report << "    PASS: header token \"" << required_header_token << "\" found." << std::endl;
         }
      }
   }
   std::cout << "============ Blast::Project::CodeUsageScanner::build_report ============" << std::endl;
   std::cout << result_report.str() << std::endl;
   return { all_clear, result_report.str(), };
}

bool CodeUsageScanner::token_exists_in_file(std::string filename, std::string search_token)
{
   std::string sanitized_search_token = sanitize_search_token(search_token);
   std::string sanitized_filename = sanitize_search_token(filename);
   //command << "(cd " << project_directory << " && "
   std::string shell_command = "(cd " + project_directory + " && "
                             + "grep --line-number \"" + sanitized_search_token + "\" \""
                             + sanitized_filename + "\""
                             + ")";
   std::cout << "Executing: " << std::endl;
   std::cout << "    " << shell_command << std::endl;
   Blast::ShellCommandExecutorWithCallback executor(
         shell_command,
         ShellCommandExecutorWithCallback::simple_silent_callback
      );

   std::string execution_result = executor.execute();
   std::vector<std::string> execution_result_as_lines = Blast::StringSplitter(execution_result, '\n').split();


   ///execution_result_as_lines

   return (executor.get_executed_successfully() && execution_result_as_lines.size() >= 1);
}

std::string CodeUsageScanner::build_scan_shell_command(std::string search_token)
{
   if (!(std::filesystem::exists(project_directory)))
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::CodeUsageScanner::build_scan_shell_command]: error: guard \"std::filesystem::exists(project_directory)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Project::CodeUsageScanner::build_scan_shell_command]: error: guard \"std::filesystem::exists(project_directory)\" not met");
   }
   std::string sanitized_search_token = sanitize_search_token(search_token);
   std::stringstream command;
   command << "(cd " << project_directory << " && "
              << "git grep --untracked --break \"" << sanitized_search_token << "\" "
              << "\":(exclude)./documentation/*\" "
              << "\":(exclude)./quintessence/*\" " // NOTE: We're only looking in .cpp and .hpp files
              << "\":(exclude)./include/lib/*\" "
              << "\":(exclude)./project_files/*\" "
              << "\":(exclude)./tmp/*\" "
              << "\":(exclude)./scripts/*\" "
              << "\":(exclude)./tests/*\" " // NOTE: Excluding tests, consider removing this exclusion
           << ")"
           ;
   return command.str();
}

std::string CodeUsageScanner::obtain_required_header_for_token(std::string token)
{
   std::unordered_map<std::string, std::string> common_required_headers_list =
      build_common_required_headers_list();
   auto it = common_required_headers_list.find(token);
   if (it == common_required_headers_list.end())
   {
      throw std::runtime_error(
         "Blast::Project::CodeUsageScanner::obtain_required_header_for_token: error: "
            "Token \"" + token + "\" not found"
      );
   }
   return it->second;
}

std::unordered_map<std::string, std::string> CodeUsageScanner::build_common_required_headers_list()
{
   std::unordered_map<std::string, std::string> required_headers =
   {
      {"ceil(", "<cmath>"},
      {"floor(", "<cmath>"},
      {"sin(", "<cmath>"},
      {"cos(", "<cmath>"},
      {"tan(", "<cmath>"},
      {"sqrt(", "<cmath>"},
      {"pow(", "<cmath>"},
      {"fabs(", "<cmath>"},
      //{"log", "<cmath>"},

      {"std::sort(", "<algorithm>"},
      
      //{"memcpy", "<cstring>"},
      //{"memset", "<cstring>"},
      //{"memcmp", "<cstring>"},
      //{"strlen", "<cstring>"},
      //{"strcpy", "<cstring>"},
      //{"strcmp", "<cstring>"},

      {"isalpha(", "<cctype>"},
      {"isdigit(", "<cctype>"},
      {"toupper(", "<cctype>"},
      {"tolower(", "<cctype>"},

      //{"exit", "<cstdlib>"},
      //{"abort", "<cstdlib>"},
      //{"rand", "<cstdlib>"},
      //{"srand", "<cstdlib>"},

      //{"printf", "<cstdio>"},
      //{"scanf", "<cstdio>"},
      //{"sprintf", "<cstdio>"},
      //{"sscanf", "<cstdio>"},

      //{"cout", "<iostream>"},
      //{"cin", "<iostream>"},
      //{"endl", "<iostream>"},

      //{"vector", "<vector>"},
      //{"map", "<map>"},
      //{"set", "<set>"},
      //{"string", "<string>"}
   };
   return required_headers;
}

std::vector<std::pair<std::string, std::string>> CodeUsageScanner::tokenize_lines(std::vector<std::string>* lines)
{
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::CodeUsageScanner::tokenize_lines]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Project::CodeUsageScanner::tokenize_lines]: error: guard \"lines\" not met");
   }
   std::vector<std::pair<std::string, std::string>> result;

   for (const std::string &line : *lines)
   {
      size_t colon_pos = line.find(':');
      if (colon_pos == std::string::npos || colon_pos + 1 >= line.size())
      {
         continue; // Skip malformed lines
      }

      // Extract filename
      std::string filename = line.substr(0, colon_pos);

      // Extract the contents after ":"
      std::string contents = line.substr(colon_pos + 1);
      while (!contents.empty() && std::isspace(contents.front()))
      {
         contents.erase(contents.begin()); // Trim leading spaces
      }

      // Extract first word (token)
      //std::istringstream iss(contents);
      //std::string token;
      //iss >> token; // Get first word

      result.emplace_back(filename, contents);
   }

   return result;
}

std::string CodeUsageScanner::sanitize_search_token(std::string search_token)
{
   std::string sanitized;
   for (char c : search_token)
   {
      switch (c)
      {
         case '\\': sanitized += "\\\\"; break; // Escape backslash
         case '\"': sanitized += "\\\""; break; // Escape double quote
         case '\'': sanitized += "\\'"; break;  // Escape single quote (optional)
         case '`': sanitized += "\\`"; break;  // Escape backtick (optional)
         case '$': sanitized += "\\$"; break;  // Escape dollar sign (optional)
         //case '<': sanitized += "\\<"; break;   // Escape less than
         //case '>': sanitized += "\\>"; break;   // Escape greater than
         default: sanitized += c; break;
      }
   }
   return sanitized;
}

std::string CodeUsageScanner::build_comma_separated_unique_asset_identifier_list(std::vector<std::pair<std::string, std::string>>* asset_studio_data, std::string separator)
{
   if (!(asset_studio_data))
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::CodeUsageScanner::build_comma_separated_unique_asset_identifier_list]: error: guard \"asset_studio_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Project::CodeUsageScanner::build_comma_separated_unique_asset_identifier_list]: error: guard \"asset_studio_data\" not met");
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

std::vector<std::pair<std::string, std::string>> CodeUsageScanner::extract_code_studio_data(std::vector<std::string>* lines)
{
   if (!(lines))
   {
      std::stringstream error_message;
      error_message << "[Blast::Project::CodeUsageScanner::extract_code_studio_data]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Project::CodeUsageScanner::extract_code_studio_data]: error: guard \"lines\" not met");
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

std::pair<bool, std::vector<std::string>> CodeUsageScanner::check_for_prefixed_assets()
{
   Blast::ShellCommandExecutorWithCallback executor(
         build_scan_shell_command(),
         ShellCommandExecutorWithCallback::simple_silent_callback
      );
   std::string execution_result = executor.execute();
   std::vector<std::string> tokens = Blast::StringSplitter(execution_result, '\n').split();
   tokens = remove_empty(trim_each(tokens));

   return { tokens.empty(), tokens };
}

std::vector<std::string> CodeUsageScanner::trim_each(std::vector<std::string> tokens)
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

std::vector<std::string> CodeUsageScanner::remove_empty(std::vector<std::string> strVector)
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


