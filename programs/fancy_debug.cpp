#include <allegro5/allegro.h>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <set>
#include <map>
#include <sstream>
#include <Blast/RegexMatcher.hpp>
#include <iostream>
#include <Blast/Debugger/BreakpointInfo.hpp>


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
   std::vector<Blast::Debugger::BreakpointInfo> debug_points_v;
   bool silent;

   void capture_from_git_command()
   {
      std::stringstream git_locate_debug_command;
      git_locate_debug_command << "git grep -n --untracked --heading --break \"//" " DEBUG\" " // NOTE: Added this empty " " so the debug finder does not
                                                                                               // think *this* location is a debug point
                               << "\":(exclude)./documentation/*\" \":(exclude)./include/lib/*\" \"*.cpp\"";
      std::function<void(std::string)> callback = silent
                                                ? Blast::ShellCommandExecutorWithCallback::simple_silent_callback
                                                : Blast::ShellCommandExecutorWithCallback::simple_cout_callback
                                                ;

      Blast::ShellCommandExecutorWithCallback shell_command_executor(
            git_locate_debug_command.str(),
            callback
         );
      shell_command_result = shell_command_executor.execute();
      shell_command_result_lines = Blast::StringSplitter(shell_command_result, '\n').split();
   }

public:
   DebugBreakpointCommandBuilder()
      : silent(false)
   {}

   void set_silent(bool silent=false)
   {
      this->silent = silent;
   }

   std::vector<std::string> build()
   {
      debug_points_v.clear();
      std::vector<std::string> result;
      std::map<std::string, std::set<int>> debug_points;

      capture_from_git_command();
      std::string current_file = "";

      // parse the lines from the shell command

      for (auto &shell_command_result_line : shell_command_result_lines)
      {
         if (shell_command_result_line.empty()) continue;
         else if (ends_with(shell_command_result_line, ".cpp"))
         {
            current_file = shell_command_result_line;
            if (!silent) std::cout << "CPP: " << current_file << std::endl;
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
            debug_points[current_file].insert(line_num);
            debug_points_v.push_back(Blast::Debugger::BreakpointInfo(current_file, line_num));
            if (!silent) std::cout << "LINE: " << line_num << std::endl;
            continue;
         }
      }

      // build the lines for the breakpoint commands

      for (auto &debug_point : debug_points)
      {
         std::string filename = debug_point.first;
         std::set<int> debug_line_nums = debug_point.second;

         for (auto &debug_line_num : debug_line_nums)
         {
            std::stringstream command_builder;
            command_builder << "breakpoint set --file \"" << filename << "\" --line " << debug_line_num << "";
            result.push_back(command_builder.str());
         }
      }

      return result;
   }
};


enum Modes
{
   UNDEFINED=0,
   PRESENCE_ONLY,
   COMMAND_PREFIX_ONLY,
};


int main(int argc, char** argv)
{
   Modes mode = UNDEFINED;

   bool outputting_command_prefix_only = false;
   bool outputting_presence_only = false;
   std::vector<std::string> args;
   for (int i=1; i<argc; i++) args.push_back(argv[i]);
   if (!args.empty() && args[0] == "command_or_empty")
   {
      outputting_command_prefix_only = true;
      mode = COMMAND_PREFIX_ONLY;
   }
   else if (!args.empty() && args[0] == "presence_only")
   {
      outputting_presence_only= true;
      mode = PRESENCE_ONLY;
   }
   else if (!args.empty())
   {
      throw std::runtime_error("Unrecognized argument. Check out the program for what arguments are expected (\"command_or_empty\", \"presence_only\".");
   }


   bool silent = (mode == COMMAND_PREFIX_ONLY) || (mode == PRESENCE_ONLY);


   DebugBreakpointCommandBuilder breakpoint_command_builder;
   if (silent) breakpoint_command_builder.set_silent(true);
   std::vector<std::string> breakpoint_commands = breakpoint_command_builder.build();

   if (!silent)
   {
      std::cout << "============ " << breakpoint_commands.size() << " `~* Fancy Debug *~`====================" << std::endl;
      std::cout << "  Note: You can output *only* the command string to use, given the marked lines on this project " << std::endl;
      std::cout << "        If you pass \"command_or_empty\" as a command-line argument to this program." << std::endl;
      std::cout << std::endl;
       
      std::cout << "=== " << breakpoint_commands.size() << " DEBUG points found ====================" << std::endl;
      std::cout << std::endl;
      for (auto &breakpoint_command : breakpoint_commands)
      {
         std::cout << breakpoint_command << std::endl;
      }
      std::cout << std::endl;
      std::cout << "============================================" << std::endl;

      std::cout << std::endl;
   }

   if (mode == PRESENCE_ONLY)
   {
      std::cout << (breakpoint_commands.empty() ? "debug_markers_are_not_present" : "debug_markers_are_present");
   }
   else
   {
      bool output_command = (!breakpoint_commands.empty()) || (!silent);
      if (output_command)
      {
         std::cout << "lldb ";
         for (auto &breakpoint_command : breakpoint_commands)
         {
            std::cout << "-o '" << breakpoint_command << "' ";
         }
         std::cout << "-o 'settings set stop-line-count-before 10' ";
         std::cout << "-o 'settings set stop-line-count-after 10' ";
         std::cout << "-o 'run' -- ";
      }
   }

   if (!silent)
   {
      std::cout << "-- bin/tests/*" << std::endl;
      std::cout << std::endl;
      std::cout << "============================================" << std::endl;
   }
   return 0;
}


