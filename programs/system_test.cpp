//#include "Projekt2.h"

#include <allegro5/allegro.h> // only needed in this ase so tests wil compile
#include <gtest/gtest.h>

#include <NcursesArt/GithubRepoStatusFetcher.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/Project/ProgramLister.hpp>
#include <Blast/FileLastWriteTime.hpp>
#include <StringSplitter.hpp>

#include <iostream>
#include <utility>
#include <ctime> // for std::time_t


//#define MOVE_CURSOR_UP "MOVE_CURSOR_UP"
//#define MOVE_CURSOR_DOWN "MOVE_CURSOR_DOWN"
//#define MOVE_CURSOR_LEFT "MOVE_CURSOR_LEFT"
//#define MOVE_CURSOR_RIGHT "MOVE_CURSOR_RIGHT"
#define INITIALIZE_SCENE "INITIALIZE_SCENE"
#define REFRESH_STATUSES "REFRESH_STATUSES"


std::map<std::string, void(*)()> events = {
   //{ EVENT_PROGRAM_INITIALIZED, initialize },
};


#include <fstream> // for std::ifstream

// this technique would fail if the file existed, but were not accessible, or if it were opened
// by another application
// see here for a more thorough set of options: https://stackoverflow.com/a/12774387
bool file_exists__implementation_1(const std::string name)
{
   std::ifstream f(name.c_str());
   return f.good();
}


#include <filesystem>

bool file_exists__implementation_2(std::string file_location)
{
   //return std::__fs::filesystem::exists(file_location);
   return false;
}



enum test_status
{
   UNRUN = 0,
   QUEUED,
   STARTED,
   FAILED,
   PASSED,
   ERROR_DURING_RUNNING,
};

#define PROPERTY_DELIMITER ": "

//std::map<std::string, bool (*)()> tests = {};
std::map<std::string, std::string> tests = {};


auto command_callback = Blast::ShellCommandExecutorWithCallback::simple_silent_callback;



class TestResultInterface
{
public:
   TestResultInterface() {}
   virtual ~TestResultInterface() {}
   virtual bool assessment() = 0;
   virtual std::string message() = 0;
};



class TestResultList : public TestResultInterface
{
public:
   std::vector<std::tuple<bool, std::string, std::string>> list;

public:
   TestResultList(std::vector<std::tuple<bool, std::string, std::string>> list)
      : TestResultInterface()
      , list(list)
   {}

   bool assessment() override
   {
      for (auto &list_element : list)
      {
         if (!std::get<0>(list_element)) return false;
      }
      return true;
   }

   std::string message() override
   {
      std::string result;
      if (!assessment())
      {
         std::stringstream msg;
         msg << "The following elements in the comparison list were prefixed with false:" << std::endl;
         for (auto &list_element : list)
         {
            if (!std::get<0>(list_element))
            {
               msg << "  element: " << std::get<1>(list_element) << std::endl;
            }
         }
         result = msg.str();
      }
      else
      {
         result = "pass";
      }
      return result;
   }
};


class TestResultEq : public TestResultInterface
{
public:
   std::string expected;
   std::string actual;

public:
   TestResultEq(std::string expected="foo", std::string actual="foo")
      : TestResultInterface()
      , expected(expected)
      , actual(actual)
   {}

   bool assessment() override
   {
      return expected == actual;
   }

   std::string message() override
   {
      std::string result;
      if (expected != actual)
      {
         std::stringstream msg;
         msg << "Test condition not met:" << std::endl
             << "  expected: " << expected << std::endl
             << "  actual: " << actual << std::endl
             ;
         result = msg.str();
      }
      else
      {
         result = "pass";
      }
      return result;
   }
};


#include <Hexagon/RegexMatcher.hpp>


class TestResultMatcher : public TestResultInterface
{
public:
   std::string expression;
   std::string actual;

public:
   TestResultMatcher(std::string expression=".*", std::string actual="foo")
      : TestResultInterface()
      , expression(expression)
      , actual(actual)
   {}

   bool assessment() override
   {
      return !RegexMatcher(actual, expression).get_match_info().empty();
   }

   std::string message() override
   {
      std::string result;
      if (!assessment())
      {
         std::stringstream msg;
         msg << "Test condition not met:" << std::endl
             << "  expression: " << expression << std::endl
             << "  actual: " << actual << std::endl
             ;
         result = msg.str();
      }
      else
      {
         result = "pass";
      }
      return result;
   }
};


TestResultInterface *last_test_result = nullptr;



std::time_t get_last_write_time__implementation_1(std::string filename)
{
   //auto ftime = Blaststd::__fs::filesystem::last_write_time(filename);
   //std::time_t last_write_time = decltype(ftime)::clock::to_time_t(ftime);

   std::time_t last_write_time = Blast::FileLastWriteTime(filename).last_write_time();

   return last_write_time;
}


std::time_t get_last_write_time__null_implementation(std::string filename)
{
   return 0;
}


std::time_t get_last_write_time(std::string filename)
{
   return get_last_write_time__implementation_1(filename);
}



std::string file_get_contents(std::string filename, bool raise_on_missing_file=true)
{
   std::ifstream file(filename.c_str());
   std::string input = "";
   if (!file)
   {
      if (raise_on_missing_file)
      {
         std::stringstream error_message;
         error_message << "Attempting to open file \"" << filename << "\" but it was not found." << std::endl;
         throw std::runtime_error(error_message.str());
      }
      else
      {
         return "";
      }
   }
   char ch;
   while (file.get(ch)) input.append(1, ch);
   if (!file.eof()) return ""; // strange error
   file.close();
   return input;
}


bool compare_last_write_time(std::string source_file_location, std::string executable_file_location)
{
   if (!file_exists__implementation_1(source_file_location))
   {
      std::stringstream error_message;
      error_message << "Attempting to check if source file is up-to-date, but the file \"" << source_file_location << "\" does not exist.";
      throw std::runtime_error(error_message.str());
   }
   else if (!file_exists__implementation_1(executable_file_location))
   {
      std::stringstream error_message;
      error_message << "Attempting to check if executable file is up-to-date, but the file \"" << executable_file_location << "\" does not exist.";
      throw std::runtime_error(error_message.str());
   }

   std::time_t source_last_write_time = get_last_write_time(source_file_location);
   std::time_t executable_last_write_time = get_last_write_time(executable_file_location);

   //std::cout << "Source file write time is " << source_last_write_time << '\n';
   //std::cout << "Executable file write time is " << executable_last_write_time << '\n';
   //std::cout << "File write time is " << std::asctime(std::localtime(&last_write_time)) << '\n';

   return executable_last_write_time >= source_last_write_time;
}



bool run_chruby_test()
{
   std::string expected_line = "source /usr/local/opt/chruby/share/chruby/chruby.sh";
   std::string zsh_filename = "/Users/markoates/Repos/.dotfiles/.zshrc";
   std::string file_contents = file_get_contents(zsh_filename);
   StringSplitter string_splitter(file_contents, '\n');
   std::vector<std::string> file_lines = string_splitter.split();

   bool found = false;
   for (auto &file_line : file_lines)
   {
      if (file_line == expected_line) found = true;
   }

   return found;
}

bool run_hexagon_app_package_test()
{
   std::string EXPECTED_HEXAGON_APP_PACKAGE_INFO_PLIST_FILENAME = "/Users/markoates/Repos/hexagon/bin/Hexagon.app/Contents/Info.plist";
   std::string content = file_get_contents(EXPECTED_HEXAGON_APP_PACKAGE_INFO_PLIST_FILENAME, true);
   return !content.empty();
}


std::string trim(const std::string& str,
                 const std::string& whitespace = " \t\n\r")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}


bool check_hexagon_app_package_alias_test()
{
   std::string success_message = "symlink exists";
   std::string symlink_check_command = std::string("if [ -L \"/Applications/Hexagon.app\" ]; then echo \"") + success_message + "\"; else echo \"symlink does not exist\"; fi";
   std::string COMMAND_TO_CREATE_SYMLINK = "ln -s /Users/markoates/Repos/hexagon/bin/Hexagon.app /Applications/Hexagon.app";

   Blast::ShellCommandExecutorWithCallback executor(symlink_check_command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output == success_message;
}


bool check_tiled_extensions_symlinks_exist()
{
   std::string success_message = "symlink exists";
   std::string symlink_check_command = std::string("if [ -L \"~/Library/Preferences/Tiled/extensions/list_map_properties.js\" ]; then echo \"") + success_message + "\"; else echo \"symlink does not exist\"; fi";
   std::string COMMAND_TO_CREATE_SYMLINK = "ln -s /Users/markoates/Repos/allegro_flare/scripts/tiled/extensions/list_map_properties.js ~/Library/Preferences/Tiled/extensions/list_map_properties.js";

   Blast::ShellCommandExecutorWithCallback executor(symlink_check_command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output == success_message;
}



#include <Blast/DirectoryExistenceChecker.hpp>
bool check_vimbackup_folder_exists()
{
   std::string expected_vimbackup_directory = "~/.vimbackup";

   std::vector<std::string> expected_directories = {
      expected_vimbackup_directory,
   };

   bool directories_missing = false;
   for (auto &expected_directory : expected_directories)
   {
      if (!Blast::DirectoryExistenceChecker(expected_directory).exists()) directories_missing = true;
   }
   return directories_missing;
}


bool check_google_test_and_google_mock_installed()
{
   std::string base_repos_dir = "/Users/markoates/Repos";

   std::string googletest_expected_directory = base_repos_dir + "/googletest";
   std::string googletest_lib_dir = base_repos_dir + "/googletest/build/googlemock/gtest";
   std::string googletest_include_dir = base_repos_dir + "/googletest/googletest/include";
   std::string googletest_mock_include_dir = base_repos_dir + "/googletest/googlemock/include";

   std::vector<std::string> expected_directories = {
      googletest_expected_directory,
      googletest_lib_dir,
      googletest_include_dir,
      googletest_mock_include_dir,
   };

   bool directories_missing = false;
   for (auto &expected_directory : expected_directories)
   {
      if (!Blast::DirectoryExistenceChecker(expected_directory).exists()) directories_missing = true;
   }

   return directories_missing;
}


std::string get_head_sha_of_vim_plugin_first_vim_plugin()
{
   std::string command = "cd /Users/markoates/.vim/bundle/first_vim_plugin && git rev-parse HEAD";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_head_sha_of_first_vim_plugin_repo()
{
   std::string command = "cd /Users/markoates/Repos/first_vim_plugin && git rev-parse HEAD";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_ruby_version()
{
   std::string command = "ruby --version";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;

}


//class ValidateDylibBundlerVersion : public Blast::BuildSystem::BuildStages::Base
//{
//private:
   //std::string get_result_of_dylibbuilder_shell_execution()
   //{
      //std::stringstream shell_command;
      //shell_command << "dylibbundler";
      //Blast::ShellCommandExecutorWithCallback shell_command_executor(shell_command.str());
      //return shell_command_executor.execute();
   //}

//public:
   //static constexpr char* TYPE = (char*)"ValidateDylibBundlerVersion";

   //ValidateDylibBundlerVersion()
      //: Blast::BuildSystem::BuildStages::Base(TYPE)
   //{}

   //virtual bool execute() override
   //{
      //std::string match_expression = "dylibbundler is a utility that helps bundle dynamic libraries inside macOS app bundles.\n";
      //std::string actual_string = get_result_of_dylibbuilder_shell_execution();
      //if (!ExpressionMatcher(match_expression, actual_string).matches()) return false;
      //return true;
   //}
//};


std::string get_dylibbundler_shell_command_response()
{
   std::string command = "dylibbundler";
   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   //std::string trimmed_output = trim(output);

   //std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   //std::string first_line = tokens.empty() ? "" : tokens[0];

   return output;
}




std::string get_imagemagick_version()
{
   std::string command = "convert -version";
   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   std::string first_line = tokens.empty() ? "" : tokens[0];

   return first_line;
}


std::string get_clang_version()
{
   std::string command = "clang --version";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   std::string first_line = tokens.empty() ? "" : tokens[0];

   return first_line;
}


std::string get_ninja_version()
{
   std::string command = "ninja --version";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   std::string first_line = tokens.empty() ? "" : tokens[0];

   return first_line;
}


std::string get_brew_yaml_info_string()
{
   std::string command = "brew info yaml-cpp";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   std::string first_line = tokens.empty() ? "" : tokens[0];

   return first_line;
}



std::string get_brew_ffmpeg_info_string() // actually not brew
{
   std::string command = "brew info ffmpeg";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   std::string first_line = tokens.empty() ? "" : tokens[0];

   return first_line;
}



std::string get_brew_ripgrep_info_string()
{
   std::string command = "brew info ripgrep";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   std::string first_line = tokens.empty() ? "" : tokens[0];

   return first_line;
}



std::string get_brew_ghostscript_info_string()
{
   std::string command = "brew info ghostscript";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   std::string first_line = tokens.empty() ? "" : tokens[0];

   return first_line;
}



std::string get_bundler_version()
{
   std::string command = "bundler --version";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_rerun_version()
{
   std::string command = "rerun --version";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_gcloud_version()
{
   std::string command = "gcloud -v";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_ngrok_version()
{
   std::string command = "ngrok -v";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}



std::string get_gcloud_current_project_in_config()
{
   std::string command = "gcloud config get-value project";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_rails_version()
{
   std::string command = "rails --version";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


std::string get_git_default_branch_name()
{
   std::string command = "git config --global init.defaultBranch";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output;
}


bool check_beebot_response_ping()
{
   std::string command = "ruby /Users/markoates/Repos/beebot/lib/runner.rb ping";

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   std::vector<std::string> tokens = StringSplitter(trimmed_output, '\n').split();
   for (auto &token : tokens)
   {
      if (token == "pong") return true;
   }

   return false;
}


bool check_bashrc_exists_with_term_export()
{
   std::string expected_line = "export TERMINFO=/mingw64/share/terminfo";
   // note: the existence of this line needs to be scanned for from the last line up (to ensure it is the last definition)
   return false;
}


bool check_bashrc_exists_with_terminfo_export()
{
   std::string expected_line = "export TERM=xterm-256color";
   // note: the existence of this line needs to be scanned for from the last line up (to ensure it is the last definition)
   return false;
}


bool check_tiled_ReverseVertexOrder_script_symlink()
{
   std::string expected_destination = "/Users/markoates/Repos/allegro_flare/scripts/tiled/ReverseVertexOrder.js";
   std::string symlink_check_command = "readlink /Users/markoates/Library/Preferences/Tiled/extensions/ReverseVertexOrder.js";

   Blast::ShellCommandExecutorWithCallback executor(symlink_check_command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output == expected_destination;
}


bool check_hexagon_app_package_symlink_destination()
{
   std::string expected_destination = "/Users/markoates/Repos/hexagon/bin/Hexagon.app";
   std::string symlink_check_command = "readlink /Applications/Hexagon.app";

   Blast::ShellCommandExecutorWithCallback executor(symlink_check_command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output == expected_destination;
}


bool run_git_default_branch_name_is_master_test()
{
   std::string match_expression = "master";
   std::string actual_string = get_git_default_branch_name();
   last_test_result = new TestResultMatcher(match_expression, actual_string);
   return last_test_result->assessment();
}


bool run_dylibbundler_presence_test()
{
   std::string match_expression = "dylibbundler is a utility that helps bundle dynamic libraries inside macOS app bundles.";
   //std::string match_expression = "ruby 2.6.10p210";
   std::string actual_string = get_dylibbundler_shell_command_response();
   last_test_result = new TestResultMatcher(match_expression, actual_string);
   return last_test_result->assessment();
}


bool run_imagemagick_version_test()
{
   // first line version string looks like:
   //"Version: ImageMagick 7.0.8-68 Q16 x86_64 2019-10-07 https://imagemagick.org\n"
   //std::string match_expression = R"HEREDOC(^Version: ImageMagick [0-9\.\-a-zA-Z].* [a-zA-Z0_]+ [0-9\-].* https://imagemagick.org)HEREDOC";
   std::string match_expression = R"HEREDOC(^Version: ImageMagick [0-9\.\-a-zA-Z].* [a-zA-Z0_]+)HEREDOC";
   std::string actual_string = get_imagemagick_version();
   last_test_result = new TestResultMatcher(match_expression, actual_string);
   return last_test_result->assessment();
}


bool run_ruby_version_test()
{
   //std::string match_expression = "ruby 2\\.6\\.5p114 \\(2019-10-01 revision 67812\\).+";
   std::string match_expression = "ruby 2.6.10p210";
   std::string actual_string = get_ruby_version();
   last_test_result = new TestResultMatcher(match_expression, actual_string);
   return last_test_result->assessment();
}


bool run_yaml_cpp_presence_test()
{
   std::string match_expression = "==> yaml-cpp: ";
   std::string actual_string = get_brew_yaml_info_string();
   last_test_result = new TestResultMatcher(match_expression, actual_string);
   return last_test_result->assessment();
}


bool run_ffmpeg_presence_test()
{
   std::string match_expression = "==> ffmpeg: "; // TODO use "brew info ffmpeg --json"
   std::string actual_string = get_brew_ffmpeg_info_string();
   last_test_result = new TestResultMatcher(match_expression, actual_string);
   return last_test_result->assessment();
}


bool run_ripgrep_presence_test()
{
   std::string match_expression = "==> ripgrep: "; // TODO: consider using "brew info ripgrep --json"
   std::string actual_string = get_brew_ripgrep_info_string();
   last_test_result = new TestResultMatcher(match_expression, actual_string);
   return last_test_result->assessment();
}


bool asio_standalone_is_present()
{
   std::string expected_present_file = "/Users/markoates/Repos/asio/asio/include/asio.hpp";
   bool file_exists = file_exists__implementation_1(expected_present_file);
   last_test_result = new TestResultEq("exists", file_exists ? "exists" : "does not exist");
   return last_test_result->assessment();
}


bool run_ghostscript_presence_test()
{
   std::string match_expression = "==> ghostscript: "; // TODO: consider using "brew info ghostscript --json" and parsing the json, with version info
   std::string actual_string = get_brew_ghostscript_info_string();
   last_test_result = new TestResultMatcher(match_expression, actual_string);
   return last_test_result->assessment();
}


bool check_vim_plugins_are_in_sync_with_local_repos()
{
   std::string sha_from_plugin = get_head_sha_of_vim_plugin_first_vim_plugin();
   std::string sha_from_local_repo = get_head_sha_of_first_vim_plugin_repo();
   return sha_from_plugin == sha_from_local_repo;
}


bool build_celebrator_executable_presence_check()
{
   std::string expected_program_location = "/Users/markoates/Repos/blast/bin/programs/build_celebrator";
   std::string command = "command -v " + expected_program_location;

   Blast::ShellCommandExecutorWithCallback executor(command, command_callback);
   std::string output = executor.execute();
   std::string trimmed_output = trim(output);

   return trimmed_output == expected_program_location;
}


bool build_celebrator_is_up_to_date()
{
   std::string source_file_location = "/Users/markoates/Repos/blast/programs/build_celebrator.cpp";
   std::string executable_file_location = "/Users/markoates/Repos/blast/bin/programs/build_celebrator";
   return compare_last_write_time(source_file_location, executable_file_location);
}


bool check_select_executables_are_up_to_date_to_their_source()
{
   std::vector<std::tuple<bool, std::string, std::string>> source_executable_pairs = {
      // blast files

      { false, "/Users/markoates/Repos/blast/programs/component_generator.cpp", "/Users/markoates/Repos/blast/bin/programs/component_generator" },
      { false, "/Users/markoates/Repos/blast/programs/generator.cpp", "/Users/markoates/Repos/blast/bin/programs/generator" },
      { false, "/Users/markoates/Repos/blast/programs/quintessence_from_yaml.cpp", "/Users/markoates/Repos/blast/bin/programs/quintessence_from_yaml" },
      { false, "/Users/markoates/Repos/blast/programs/symlink_component_from_another_project.cpp", "/Users/markoates/Repos/blast/bin/programs/symlink_component_from_another_project" },
      { false, "/Users/markoates/Repos/blast/programs/build_celebrator.cpp", "/Users/markoates/Repos/blast/bin/programs/build_celebrator" },
      { false, "/Users/markoates/Repos/blast/programs/create_source_release.cpp", "/Users/markoates/Repos/blast/bin/programs/create_source_release" },
      { false, "/Users/markoates/Repos/blast/programs/fancy_find.cpp", "/Users/markoates/Repos/blast/bin/programs/fancy_find" },
      { false, "/Users/markoates/Repos/blast/programs/fancy_stager.cpp", "/Users/markoates/Repos/blast/bin/programs/fancy_stager" },
      //{ false, "/Users/markoates/Repos/blast/programs/ncurses_status_fetcher.cpp", "/Users/markoates/Repos/blast/bin/programs/ncurses_status_fetcher" },
      { false, "/Users/markoates/Repos/blast/programs/system_test.cpp", "/Users/markoates/Repos/blast/bin/programs/system_test" },

      // hexagon files

      { false, "/Users/markoates/Repos/hexagon/programs/hexagon.cpp", "/Users/markoates/Repos/hexagon/bin/programs/hexagon" },
      { false, "/Users/markoates/Repos/hexagon/programs/daemus.cpp", "/Users/markoates/Repos/hexagon/bin/programs/daemus" },
      { false, "/Users/markoates/Repos/hexagon/programs/macos_release_builder.cpp", "/Users/markoates/Repos/hexagon/bin/programs/macos_release_builder" },

      // TODO: Update these ncurses-art/bin/programs files to blast/programs files

      //{ false, "/Users/markoates/Repos/ncurses-art/programs/builder.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/builder" },
      //{ false, "/Users/markoates/Repos/ncurses-art/programs/builder2.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/builder2" },
      //{ false, "/Users/markoates/Repos/ncurses-art/programs/project_filename_generator.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/project_filename_generator" },
      //{ false, "/Users/markoates/Repos/ncurses-art/programs/system_test.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/system_test" },
      //{ false, "/Users/markoates/Repos/ncurses-art/programs/fancy_branch.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/fancy_branch" },
      //{ false, "/Users/markoates/Repos/ncurses-art/programs/fancy_component.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/fancy_component" },
      //{ false, "/Users/markoates/Repos/ncurses-art/programs/fancy_component_lister.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/fancy_component_lister" },
      //{ false, "/Users/markoates/Repos/ncurses-art/programs/fancy_list.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/fancy_list" },
      //{ false, "/Users/markoates/Repos/ncurses-art/programs/fancy_log.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/fancy_log" },
      //{ false, "/Users/markoates/Repos/ncurses-art/programs/quiz.cpp", "/Users/markoates/Repos/ncurses-art/bin/programs/quiz" },
   };

   for (auto &source_executable_pair : source_executable_pairs)
   {
      bool &is_up_to_date = std::get<0>(source_executable_pair);
      std::string &source_filename = std::get<1>(source_executable_pair);
      std::string &executable_filename = std::get<2>(source_executable_pair);

      is_up_to_date = compare_last_write_time(source_filename, executable_filename);
   }

   last_test_result = new TestResultList(source_executable_pairs);
   return last_test_result->assessment();
}


bool check_clang_version_is_expected_version()
{
   last_test_result = new TestResultMatcher("^Apple clang version 15\\.[0-9]\\.[0-9]+ \\(clang-15[0-9][0-9]\\.[0-9]+\\.[0-9]+(\\.[0-9]+)+\\)$", get_clang_version());
   // Examples:
   // Apple clang version 15.0.0 (clang-1500.1.0.2.5)
   // Apple clang version 15.0.0 (clang-1500.1.0.2)
   return last_test_result->assessment();
}


bool check_ninja_version_is_expected_version()
{
   last_test_result = new TestResultMatcher("^1\\.10\\.1$", get_ninja_version());
   return last_test_result->assessment();
}




bool run_bundler_version_test()
{
   last_test_result = new TestResultMatcher("^Bundler version [0-9]+\\.[0-9]+\\.[0-9]+", get_bundler_version());
   return last_test_result->assessment();
}



bool run_rerun_version_test()
{
   last_test_result = new TestResultMatcher("^[0-9]+\\.[0-9]+\\.[0-9]+", get_rerun_version());
   return last_test_result->assessment();
}



bool run_gcloud_presence_test()
{
   last_test_result = new TestResultMatcher("^Google Cloud SDK [0-9]+\\.[0-9]+\\.[0-9]+", get_gcloud_version());
   return last_test_result->assessment();
}


bool run_ngrok_presence_test()
{
   last_test_result = new TestResultMatcher("^ngrok version [0-9]+\\.[0-9]+\\.[0-9]+", get_ngrok_version());
   return last_test_result->assessment();
}



bool run_gcloud_project_status_test()
{
   last_test_result = new TestResultMatcher("game-development-workflow", get_gcloud_current_project_in_config());
   return last_test_result->assessment();
}


bool run_rails_version_test()
{
   last_test_result = new TestResultMatcher("^Rails [0-9]+\\.[0-9]+\\.[0-9]+", get_rails_version());
   return last_test_result->assessment();
}



bool just_a_failing_test()
{
   return false;
}


std::string diamond_it(std::string label, int number)
{
   std::stringstream result;
   bool check = number == 1;
   result << label;
   if (check) result << PROPERTY_DELIMITER << "🔹 ";
   else result << PROPERTY_DELIMITER << "🔸 ";
   result << number;

   return result.str();
}

std::string check_it(std::string label, bool check)
{
   std::stringstream result;
   result << label;
   if (check) result << PROPERTY_DELIMITER << "✅ pass";
   else
   {
      result << PROPERTY_DELIMITER << "🔺 FAIL" << std::endl;
      if (last_test_result) result << last_test_result->message() << std::endl;
   }
   return result.str();
}



#include <iostream>
#include <string>
#include <cctype>

// courtesy ChatGPT:
std::string remove_non_alphanumeric(std::string input) {
    std::string output = "";
    for (int i = 0; i < input.size(); i++) {
        if (isalnum(input[i]) || isspace(input[i])) {
            output += input[i];
        }
    }
    return output;
}

// courtesy ChatGPT:
std::string replace_multiple_spaces(std::string input) {
    std::string output = "";
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == ' ') {
            output += '_';
            while (input[i] == ' ' && i < input.size()) {
                i++;
            }
            i--;
        } else {
            output += input[i];
        }
    }
    return output;
}

#include <iostream>
#include <string>

// courtesy ChatGPT:
std::string escape_quotes(std::string input) {
    std::string output = "";
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '\"') {
            output += "\\\"";
        } else if (input[i] == '\'') {
            output += "\\\'";
        } else {
            output += input[i];
        }
    }
    return output;
}

std::string sanitize_test_name(std::string source_test_name)
{
   return replace_multiple_spaces(remove_non_alphanumeric(source_test_name));
}



//void initialize();
//emit_event(INITIALIZE_SCENE);


//TEST(SystemTest, will_format_tests)
//{
   //initialize();
   //events[INITIALIZE_SCENE](); //(INITIALIZE_SCENE);

   //int i=0; 
   //for (auto &test : tests)
   //{
      //i++;
      //std::string sanitized_test_name = sanitize_test_name(test.first);
      //std::cout << "TEST(SystemTest, " << sanitized_test_name << ")" << std::endl;
      //std::cout << "{" << std::endl;
      //std::cout << "   EXPECT_EQ(true, " << test.second << "()) << \"Test: " << escape_quotes(test.first) << "\";" << std::endl;
      //std::cout << "}" << std::endl;
      //std::cout << std::endl;
      //std::cout << std::endl;
   //}
//}



TEST(SystemTest, git_is_configured_to_use_master_as_the_default_new_branch_name)
{
   EXPECT_EQ(true, run_git_default_branch_name_is_master_test()) << "Test: Git default new branch name is master (run \"git config --global init.defaultBranch master\")";
}



TEST(SystemTest, ImageMagick_is_present_in_the_command_line_run_brew_update_brew_install_imagemagick)
{
   EXPECT_EQ(true, run_imagemagick_version_test()) << "Test: ImageMagick is present in the command line (run \"brew update && brew install imagemagick\")";
}


TEST(SystemTest, dylibbundler_is_present)
{
   EXPECT_EQ(true, run_dylibbundler_presence_test()) << "Test: dylibbundler is present in the command line (run \"brew update && brew install dylibbundler\")";
}



TEST(SystemTest, DISABLED__Rails_is_present_and_installed_otherwise_sudo_gem_install_rails_after_instaling_ruby_Needed_by_inflector_components_in_blast)
{
   EXPECT_EQ(true, run_rails_version_test()) << "Test: Rails is present and installed (otherwise \"sudo gem install rails\", after instaling ruby. Needed by inflector components in blast)";
}


TEST(SystemTest, Ruby_version_is_the_expected_version_otherwise_sudo_rubyinstall_ruby_265_then_sudo_rubyinstall_system_ruby_265)
{
   EXPECT_EQ(true, run_ruby_version_test()) << "Test: Ruby version is the expected version (otherwise \"sudo ruby-install ruby 2.6.5\", then \"sudo ruby-install --system ruby 2.6.5\")";
}


TEST(SystemTest, a_targeted_set_of_executables_are_uptodate_to_their_source_files)
{
   EXPECT_EQ(true, check_select_executables_are_up_to_date_to_their_source()) << "Test: a targeted set of executables are up-to-date to their source files";
}


TEST(SystemTest, asio_standalone_is_present)
{
   EXPECT_EQ(true, asio_standalone_is_present()) << "Test: asio standalone is present";
}


TEST(SystemTest, bundler_is_present_and_installed_otherwise_sudo_gem_install_bundler201_after_instaling_ruby)
{
   EXPECT_EQ(true, run_bundler_version_test()) << "Test: bundler is present and installed (otherwise \"sudo gem install bundler:2.0.1\", after instaling ruby)";
}


TEST(SystemTest, celebrate_executable_is_present)
{
   EXPECT_EQ(true, build_celebrator_executable_presence_check()) << "Test: celebrate executable is present";
}


TEST(SystemTest, celebrate_executable_is_uptodate_executable_been_created_at_a_time_later_than_the_last_change_to_its_source_file)
{
   EXPECT_EQ(true, build_celebrator_is_up_to_date()) << "Test: celebrate executable is up-to-date (executable been created at a time later than the last change to its source file)";
}


TEST(SystemTest, DISABLED__chruby_is_present)
{
   EXPECT_EQ(true, run_chruby_test()) << "Test: chruby is present";
}


TEST(SystemTest, clang_version_is_the_expected_version_consider_running_brew_install_llvm_to_update_to_a_more_recent_version)
{
   EXPECT_EQ(true, check_clang_version_is_expected_version()) << "Test: clang version is the expected version (consider the following: \"brew install llvm\", install from git (https://github.com/llvm/llvm-project), or use clang installed natively on Mac through xcode)";
}


TEST(SystemTest, ffmpeg_is_installed_through_homebrew_used_to_convert_wav_files_to_ogg)
{
   EXPECT_EQ(true, run_ffmpeg_presence_test()) << "Test: ffmpeg is installed through homebrew (used to convert wav files to ogg)";
}


TEST(SystemTest, ghostscript_is_installed_through_homebrew_needed_for_imagemagicks_convert_filepdf_filepng)
{
   EXPECT_EQ(true, run_ghostscript_presence_test()) << "Test: ghostscript is installed through homebrew (needed for imagemagick\'s `convert file.pdf file.png`";
}


TEST(SystemTest, googletest_and_googlemock_library_are_installed)
{
   EXPECT_EQ(true, check_google_test_and_google_mock_installed()) << "Test: googletest and googlemock library are installed";
}


TEST(SystemTest, rerun_is_present_and_installed_otherwise_sudo_gem_install_rerun_after_instaling_ruby)
{
   EXPECT_EQ(true, run_rerun_version_test()) << "Test: rerun is present and installed (otherwise \"sudo gem install rerun\", after instaling ruby)";
}


TEST(SystemTest, gcloud_is_present)
{
   EXPECT_EQ(true, run_gcloud_presence_test()) << "Test: gcloud is not installed. See .dotfiles setup script for mac (at the bottom).";
}


TEST(SystemTest, gcloud_is_configured_to_the_expected_project)
{
   EXPECT_EQ(true, run_gcloud_project_status_test()) << "Test: gcloud is not setup as expected. May not be logged in, or, there may have been a change in the config to the active project.";
}


TEST(SystemTest, ripgrep_is_installed_through_homebrew)
{
   EXPECT_EQ(true, run_ripgrep_presence_test()) << "Test: ripgrep is installed through homebrew";
}


TEST(SystemTest, the_tiled_ReverseVertexOrder_script_symlink_points_to_the_expected_script)
{
   EXPECT_EQ(true, check_tiled_ReverseVertexOrder_script_symlink()) << "Test: There is a symlink in the tiled \"extensions\" "
      "folder that points to the expected ReverseVertexOrder.js extension. (More info on this extension at https://discourse.mapeditor.org/t/polygons-can-point-order-be-reversed/6973)";
}


TEST(SystemTest, the_Applications_Hexagon_app_symlink_points_to_the_expected_hexagon_app_package)
{
   EXPECT_EQ(true, check_hexagon_app_package_symlink_destination()) << "Test: the /Applications/Hexagon.app symlink points to the expected hexagon app package (create with \"ln -s /Users/markoates/Repos/hexagon/bin/Hexagon.app /Applications/Hexagon.app\")";
}


TEST(SystemTest, the_hexagon_app_package_is_present_in_the_hexagon_repo)
{
   EXPECT_EQ(true, run_hexagon_app_package_test()) << "Test: the hexagon app package is present in the hexagon repo";
}


TEST(SystemTest, the_systems_Applications_folder_contains_a_symlink_to_the_hexagon_repos_app_package)
{
   EXPECT_EQ(true, check_hexagon_app_package_alias_test()) << "Test: the system\'s /Applications folder contains a symlink to the hexagon repo\'s app package. "
                                                           << "Use \"ln -s /Applications/Hexagon.app /Users/markoates/Repos/hexagon/bin/Hexagon.app\" to add it.";
}


//// This test is no longer relvant, but it is kept here as a clue for managing symlinks for Tiled in the future
//TEST(SystemTest, the_systems_Tiled_extensions_folder_contains_a_targed_extsion_symlink)
//{
   //EXPECT_EQ(true, check_tiled_extensions_symlinks_exist()) << "Test: the system\'s ~/Library/Preferences/Tiled/extensions/list_map_properties.js folder contains a symlink to allegro_flare's list_map_properties.js tiled script. "
                                                           //<< "Use \"ln -s /Users/markoates/Repos/allegro_flare/scripts/tiled/extensions/list_map_properties.js ~/Library/Preferences/Tiled/extensions/list_map_properties.js\" to add it.";
//}


TEST(SystemTest, vims_firstvimplugin_is_in_sync_to_the_latest_version_run_PluginUpdate_in_vim)
{
   EXPECT_EQ(true, check_vim_plugins_are_in_sync_with_local_repos()) << "Test: vim\'s first_vim_plugin is in sync to the latest version (run \":PluginUpdate\" in vim)";
}


TEST(SystemTest, yamlcpp_is_installed_through_homebrew)
{
   EXPECT_EQ(true, run_yaml_cpp_presence_test()) << "Test: yaml-cpp is installed through homebrew";
}


TEST(SystemTest, vimbackup_folder_exists_run_mkdir_vimbackup_to_create)
{
   EXPECT_EQ(true, check_vimbackup_folder_exists()) << "Test: ~/.vimbackup folder exists (run \"mkdir .vimbackup\" to create)";
}


TEST(SystemTest, ngrok_is_present_on_the_system)
{
   EXPECT_EQ(true, run_ngrok_presence_test()) << "Test: ngrok does not appear to be installed on the system (\"ngrok -v\"). Check https://dashboard.ngrok.com/get-started/setup/macos for instructions on how to install with homebrew.";
}



//EST(SystemTest, yaml_cpp_is_installed_through_homebrew)
//{
   //EXPECT_EQ(true, run_yaml_cpp_presence_test);
//}





//void initialize()
//{
   //events[INITIALIZE_SCENE] = []{
      ////create_text("output");

      //tests = {
         //{ "yaml-cpp is installed through homebrew", "run_yaml_cpp_presence_test" },
         //{ "ffmpeg is installed through homebrew (used to convert wav files to ogg)", "run_ffmpeg_presence_test" },
         //{ "Ruby version is the expected version (otherwise \"sudo ruby-install ruby 2.6.5\", then \"sudo ruby-install --system ruby 2.6.5\")", "run_ruby_version_test" },
         //{ "a targeted set of executables are up-to-date to their source files", "check_select_executables_are_up_to_date_to_their_source" },
         //{ "ripgrep is installed through homebrew", "run_ripgrep_presence_test" },
         //{ "asio standalone is present", "asio_standalone_is_present" },
         //{ "chruby is present", "run_chruby_test" },
         //{ "rerun is present and installed (otherwise \"sudo gem install rerun\", after instaling ruby)", "run_rerun_version_test" },
         //{ "bundler is present and installed (otherwise \"sudo gem install bundler:2.0.1\", after instaling ruby)", "run_bundler_version_test" },
         //{ "Rails is present and installed (otherwise \"sudo gem install rails\", after instaling ruby. Needed by inflector components in blast)", "run_rails_version_test" },
         //{ "googletest and googlemock library are installed", "check_google_test_and_google_mock_installed" },
         //{ "celebrate executable is present", "build_celebrator_executable_presence_check" },
         //{ "celebrate executable is up-to-date (executable been created at a time later than the last change to its source file)", "build_celebrator_is_up_to_date" },
         //{ "the hexagon app package is present in the hexagon repo", "run_hexagon_app_package_test" },
         //{ "the /Applications/Hexagon.app symlink points to the expected hexagon app package (create with \"ln -s /Users/markoates/Repos/hexagon/bin/Hexagon.app /Applications/Hexagon.app\")", "check_hexagon_app_package_symlink_destination" },
         //{ "vim's first_vim_plugin is in sync to the latest version (run \":PluginUpdate\" in vim)", "check_vim_plugins_are_in_sync_with_local_repos" },
         //{ "~/.vimbackup folder exists (run \"mkdir .vimbackup\" to create)", "check_vimbackup_folder_exists" },
         //{ "ImageMagick is present in the command line (run \"brew update && brew install imagemagick\")", "run_imagemagick_version_test" },
         ////{ "Ruby version is the expected version (otherwise \"sudo ruby-install ruby 2.6.5\", then \"sudo ruby-install --system ruby 2.6.5\")", "run_ruby_version_test" },
         //{ "ghostscript is installed through homebrew (needed for imagemagick's `convert file.pdf file.png`", "run_ghostscript_presence_test" },
         ////{ "beebot is responsive", "check_beebot_response_ping" },
         ////{ "clang version is the expected version (consider the following: \"brew install llvm\", install from git (https://github.com/llvm/llvm-project), or use clang installed natively on Mac through xcode)", "check_clang_version_is_expected_version" },
         ////{ "ninja version is the expected version (consider running \"brew install ninja\" to update to a more recent version)", "check_ninja_version_is_expected_version" },
         //{ "the system's /Applications folder contains a symlink to the hexagon repo's app package", "check_hexagon_app_package_alias_test" },


         ////{ "on MacOS, Hexagon has an override keyboard shortcut for hiding the window (https://stackoverflow.com/q/45601543/6072362, https://superuser.com/a/1328252)", "just_a_failing_test" },
         ////{ "terminal sessions are still open despite ./dotfile changes", "just_a_failing_test" },
         ////{ "project binaries are up-to-date despite project file changes", "just_a_failing_test" },
         ////{ "terminal session has installed new ruby verions and chruby has been refreshed (with a terminal refresh)", "just_a_failing_test" },
         ////{ "generating a blast project adds ./.keep files for the necessary created directories", "just_a_failing_test" },
      //};

//#ifdef _WIN32
      //std::map<std::string, bool (*)()> windows_specific_tests = {
         //{ "bashrc exists", "just_a_failing_test" },
         //{ "bashrc exports a TERM system variable with the expected value", "just_a_failing_test" },
         //{ "bashrc exports a TERMINFO system variable with the expected value", "just_a_failing_test" },
         //{ "pacman has the mingw-w64-x86_64-yaml-cpp package installed", "just_a_failing_test" },
         //{ "pacman has the ncurses-devel package installed", "just_a_failing_test" },
         //{ "vim is set as the git default global editor", "just_a_failing_test" },
         //{ "~/.vimbackup folder exists", "check_vimbackup_folder_exists" },
      //};

      //tests.insert(windows_specific_tests.begin(), windows_specific_tests.end());
//#endif

   //};
   //events[REFRESH_STATUSES] = []{
      ////Text &text = find_text("output");

      ////std::stringstream result_text;

      ////for (auto &test : tests)
      ////{
         ////last_test_result = new TestResultEq();
         ////result_text << "running \"" << test.first << "\"";

         ////bool test_result = (*test.second)();
         ////if (test_result == true)
         ////{
            ////result_text << " --- " << check_it("status", test_result);
         ////}
         ////else if (test_result == false)
         ////{
            ////result_text << std::endl;
            ////result_text << " --- " << check_it("status", test_result) << std::endl;
         ////}
         ////result_text << std::endl;
      ////}
      
      ////text.set_text(result_text.str());
   //};

   ////emit_event(INITIALIZE_SCENE);
   ////emit_event(REFRESH_STATUSES);
//}




int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}


