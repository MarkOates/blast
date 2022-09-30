#include <allegro5/allegro.h>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <set>
#include <map>
#include <sstream>
#include <Blast/RegexMatcher.hpp>
#include <iostream>


#include <string_view>

static bool ends_with(std::string_view str, std::string_view suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}

static bool starts_with(std::string_view str, std::string_view prefix)
{
    return str.size() >= prefix.size() && 0 == str.compare(0, prefix.size(), prefix);
}


class DebugBreakpointCommandBuilder
{
private:
   std::string shell_command_result;
   std::vector<std::string> shell_command_result_lines;

   void capture_from_git_command()
   {
      std::stringstream git_locate_debug_command;
      git_locate_debug_command << "git grep -n --untracked --heading --break \"// DEBUG\" "
                               << "\":(exclude)./documentation/*\" \":(exclude)./include/lib/*\" \"*.cpp\"";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(git_locate_debug_command.str());
      shell_command_result = shell_command_executor.execute();
      shell_command_result_lines = Blast::StringSplitter(shell_command_result, '\n').split();
   }

public:
   DebugBreakpointCommandBuilder() {}

   std::string build()
   {
      std::stringstream result;
      std::map<std::string, std::set<int>> parsed_lines;

      capture_from_git_command();
      std::string current_file = "";

      for (auto &shell_command_result_line : shell_command_result_lines)
      {
         if (shell_command_result_line.empty()) continue;
         else if (ends_with(shell_command_result_line, ".cpp"))
         {
            current_file = shell_command_result_line;
            std::cout << "CPP: " << current_file << std::endl;
            continue;
         }
         else
         {
            Blast::RegexMatcher matcher(shell_command_result_line, "^[0-9]+: +// ?DEBUG");
            std::vector<std::pair<int, int>> match_info = matcher.get_match_info();

            std::size_t pos = shell_command_result_line.find_first_of(":", 0);
            if (pos == std::string::npos) throw std::runtime_error("Weird error here");
            std::string line_num_as_str = shell_command_result_line.substr(0, pos);

            int line_num = atoi(line_num_as_str.c_str());
            parsed_lines[current_file].insert(line_num);
            std::cout << "LINE: " << line_num << std::endl;
            continue;
         }
      }

      return result.str();
   }
};


int main(int argc, char** argv)
{
   DebugBreakpointCommandBuilder breakpoint_command_builder;
   breakpoint_command_builder.build();

   return 0;
}


