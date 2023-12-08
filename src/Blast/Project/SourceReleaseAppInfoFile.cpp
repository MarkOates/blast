

#include <Blast/Project/SourceReleaseAppInfoFile.hpp>

#include <Blast/Errors.hpp>
#include <Blast/String/Trimmer.hpp>
#include <Blast/StringSplitter.hpp>
#include <algorithm>
#include <filesystem>
#include <sstream>


namespace Blast
{
namespace Project
{


SourceReleaseAppInfoFile::SourceReleaseAppInfoFile(std::string app_icon_filename)
   : app_icon_filename(app_icon_filename)
{
}


SourceReleaseAppInfoFile::~SourceReleaseAppInfoFile()
{
}


void SourceReleaseAppInfoFile::set_app_icon_filename(std::string app_icon_filename)
{
   this->app_icon_filename = app_icon_filename;
}


std::string SourceReleaseAppInfoFile::get_app_icon_filename() const
{
   return app_icon_filename;
}


std::string SourceReleaseAppInfoFile::get_contents()
{
   //std::string app_icon_filename = "bin/data/icons/golf-icon-01.png";
   std::stringstream result;
   result << "app_icon_filename=" << app_icon_filename << std::endl;
   return result.str();
}

void SourceReleaseAppInfoFile::load_contents(std::string raw_contents)
{
   std::istringstream iss(raw_contents);
   std::string line;

   // TODO: Check for extra keys, expected keys that were not found, etc
   std::vector<std::string> duplicate_keys;
   std::vector<std::string> excess_keys;
   std::vector<std::string> expected_keys = {
      "app_icon_filename",
   };

   // Process each line
   int line_num = 0;
   while (std::getline(iss, line))
   {
      line_num++;

      std::string trimmed_line = Blast::String::Trimmer(line).trim();
      if (trimmed_line.empty()) continue; // Skip blank lines


      // Validate line format
     
      std::vector<std::string> line_tokens = trim_each(Blast::StringSplitter(trimmed_line, '=').split());
      if (line_tokens.size() != 2)
      {
         // TODO: Throw
         Blast::Errors::throw_error(
            "Blast::Project::SourceReleaseAppInfoFile::load_contents",
            "Expecting 2 tokens between a '=' character, but there were " + std::to_string(line_tokens.size())
               + " on line " + std::to_string(line_num)
         );
      }

      if (line_tokens[0].empty() || line_tokens[1].empty())
      {
         // TODO: Throw
         Blast::Errors::throw_error(
            "Blast::Project::SourceReleaseAppInfoFile::load_contents",
            "Expecting 2 non-blank tokens between a '=' character, but one or the other is blank on line "
               + std::to_string(line_num)
         );
      }

      std::string prefix = line_tokens[0];
      std::string postfix = line_tokens[1];


      // Pull variable
      // TODO: Check for extra keys, expected keys that were not found, duplicate keys, etc

      if (prefix == "app_icon_filename") app_icon_filename = postfix;
   }
   return;
}

std::vector<std::string> SourceReleaseAppInfoFile::trim_each(std::vector<std::string> tokens)
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


} // namespace Project
} // namespace Blast


