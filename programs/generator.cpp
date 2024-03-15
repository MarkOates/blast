#include <allegro5/allegro.h> // for compatibility with union/Makefile


#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


class ConsoleOutputter
{
public:
   ConsoleOutputter() {}
   ~ConsoleOutputter() {}
   void output_line(std::string message)
   {
      std::cout << message << std::endl;
   }
};



std::string const PROGRAM_RUNNER_FILE_CONTENT = R"END(functions:
  - name: run
    type: std::string
    body: return "Hello Buddy!";
)END";



std::string const GITIGNORE_FILE_CONTENT = R"END(
# temp files from building build dir

build/tmp*
tmp/*
obj/**
*.a


# compiled object files and any executable files (but maintain the data folder)

bin/*
!bin/data/
!bin/data/**


# Dep files

.deps/**


# OSX image caches

**/.DS_store


# Allegro log files

allegro.log


# Hexagon files

~TMP.txt


# vim swap files

*.swp
*.swo


)END";



std::string const APPINFO_YML_FILE_CONTENT = R"END(# appinfo.yml
app_icon_filename: data/icons/allegro-flare-generic-icon-1024.png
)END";




std::string const HASH_CHECK_FILENAME = "hash_check";
std::string const HASH_CHECK_FILE_CONTENTS = R"END(#!/bin/bash
find quintessence -name '*.q.yml'| xargs md5
)END";




std::string const RERUN_SCRIPT_FILENAME = "rr";
std::string const RERUN_SCRIPT_CONTENT = R"END(#!/bin/bash

yellow='\033[1;33m'
reset_text='\033[0m'

if [ "$#" == "0" ]
then
  echo "Error: You must provide an argument, which should be a name of a component."
  echo "Example: \"./rr ProgramRunner\""
else
  chruby 2.5.1
  rerun "./build && make obj/$1.o && make bin/tests/$1Test && bin/tests/$1Test && make bin/examples/$1Example && bin/examples/$1Example" -c --pattern "{quintessence/**/*.q.yml,tests/**/*Test.cpp,examples/**/*Example.cpp}"
fi
)END";



std::string TEST_RUNNER_CLASS_NAME = "TestRunner";
std::string const TEST_RUNNER_FILE_CONTENT = R"END(
#include <gtest/gtest.h>
#include <allegro5/allegro.h>

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
)END";



std::string const RERUN_CAT_FILE_SCRIPT_FILENAME = "rerun_cat_file";
std::string const RERUN_CAT_FILE_SCRIPT_CONTENT = R"END(#!/bin/bash

if [ "$#" == "0" ]
then
  echo "Error: You must provide an argument, which is the name of a file."
  echo "Example: \"./rerun_cat_file include/MyProject/MyComponent.hpp\""
else
  rerun -c "echo -en \"\033[93m\"; cat -n $1; echo -en \"\033[0m\"" -p "$1"
fi
)END";



std::string const VERSION_YAML_FILE_FILENAME = "version.yml";
std::string const VERSION_YAML_FILE_CONTENT = R"END(note: This is a machine generated file. Do not modify.
version:
  major: 0
  minor: 0
  patch: 0
  labels:
    - wip
  metadata: []
)END";







std::string PROGRAM_RUNNER_CLASS_NAME = "Runner";
std::string PROGRAM_RUNNER_CLASS_END_FRAGMENTS_NAME = "Runner";
std::string main_file_content_template = R"END(
#include <[[PROJECT_NAME]]/[[PROGRAM_RUNNER_CLASS_NAME]].hpp>
#include <allegro5/allegro.h>
#include <vector> // for parsing command line args
#include <algorithm> // for parsing command line args

int main(int argc, char **argv)
{
   std::vector<std::string> command_line_args;
   for (int i=1; i<argc; i++) command_line_args.push_back(argv[i]);
   bool contains_development_flag = std::count(command_line_args.begin(), command_line_args.end(), "--development");

   // TODO: improve this to return an error when an unrecognized flag is present

   std::string deployment_environment =
         contains_development_flag
         ? AllegroFlare::DeploymentEnvironment::ENVIRONMENT_DEVELOPMENT
         : AllegroFlare::DeploymentEnvironment::ENVIRONMENT_PRODUCTION;

   [[PROJECT_NAME]]::[[PROGRAM_RUNNER_CLASS_END_FRAGMENTS_NAME]]().run(deployment_environment);
   return 0;
}
)END";



std::string main_file_content_template_with_configuration = R"END(

#include <AllegroFlare/Runners/Complete.hpp>
#include <[[PROJECT_NAME]]/GameConfigurations/Main.hpp>
#include <allegro5/allegro.h>
#include <vector> // for parsing command line args
#include <algorithm> // for parsing command line args

int main(int argc, char **argv)
{
   std::vector<std::string> command_line_args;
   for (int i=1; i<argc; i++) command_line_args.push_back(argv[i]);
   bool contains_development_flag = std::count(command_line_args.begin(), command_line_args.end(), "--development");

   // TODO: improve this to return an error when an unrecognized flag is present

   [[PROJECT_NAME]]::GameConfigurations::Main main_configuration;

   std::string deployment_environment =
         contains_development_flag
         ? AllegroFlare::DeploymentEnvironment::ENVIRONMENT_DEVELOPMENT
         : AllegroFlare::DeploymentEnvironment::ENVIRONMENT_PRODUCTION;

   AllegroFlare::Runners::Complete().run(&main_configuration, deployment_environment);
   return 0;
}

)END";




std::string README_FILE_CONTENT_TEMPLATE = R"END(# [[PROJECT_NAME]]
)END";




void ___replace(std::string& str, std::string from, std::string to)
{
   //static const std::string from = "\t";
   //static const std::string to = std::string(3, ' ');

   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
}


std::vector<std::string> args;


class Generator
{
private:
   std::string project_name;

public:
   Generator(std::string project_name)
      : project_name(project_name)
   {}

   std::string get_project_name()
   {
      return project_name;
   }
   std::string get_command_for_make_dir()
   {
      std::stringstream command;
      command << "mkdir \"" << project_name << "\"";
      return command.str();
   }
   std::string mkprojdir_and_keep_file(std::string dir)
   {
      std::string full_dir_path = project_name + "/" + dir;

      std::stringstream command;
      command << "mkdir \"" << full_dir_path << "\""
              << " && "
              << "touch \"" << full_dir_path << "/.keep\""
              << " && "
              << "echo \"# keep\" " << full_dir_path << "/.keep";

      return command.str();
   }
};


void create_makefile(Generator &generator)
{
   std::string command = std::string("(cd ") + generator.get_project_name() + " && ln -s ../blast/Makefile ./Makefile)";
   Blast::ShellCommandExecutorWithCallback makefile_symlink_command_executor(command);
   makefile_symlink_command_executor.execute();
}


void create_test_runner(Generator &generator)
{
   std::string command = std::string("(cd ") + generator.get_project_name() + " && ln -s ../../blast/tests/TestRunner.cpp ./tests/TestRunner.cpp)";
   Blast::ShellCommandExecutorWithCallback makefile_symlink_command_executor(command);
   makefile_symlink_command_executor.execute();

   //std::ofstream outfile6;
   //outfile6.open(generator.get_project_name() + "/tests/" + TEST_RUNNER_CLASS_NAME + ".cpp", std::ios::binary);
   //outfile6 << TEST_RUNNER_FILE_CONTENT;
   //outfile6.close();
}


void create_version_yaml(Generator &generator)
{
   std::ofstream outfile;
   outfile.open(generator.get_project_name() + "/" + VERSION_YAML_FILE_FILENAME, std::ios::binary);
   outfile << VERSION_YAML_FILE_CONTENT;
   outfile.close();
}


//void create_game_progress_and_state_info(Generator &generator)
//{
   //std::ofstream outfile;
   //outfile.open(generator.get_project_name() + "/" + VERSION_YAML_FILE_FILENAME, std::ios::binary);
   //outfile << VERSION_YAML_FILE_CONTENT;
   //outfile.close();
//}


void create_game_progress_and_state_info_classes(std::string project_name)
{
   {
      std::string cmd = "~/Repos/blast/bin/programs/component_generator " + project_name + "/Testing/Comparison/" + project_name + "/GameProgressAndStateInfo game_progress_and_state_info_comparison";
      std::string command = std::string("(cd ") + project_name + " && " + cmd + ")";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(command);
      shell_command_executor.execute();
   }

   {
      std::string cmd = "~/Repos/blast/bin/programs/component_generator " + project_name + "/JSONLoaders/" + project_name + "/GameProgressAndStateInfo game_progress_and_state_info_json_loader";
      std::string command = std::string("(cd ") + project_name + " && " + cmd + ")";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(command);
      shell_command_executor.execute();
   }

   {
      std::string cmd = "~/Repos/blast/bin/programs/component_generator " + project_name + "/GameProgressAndStateInfo game_progress_and_state_info";
      std::string command = std::string("(cd ") + project_name + " && " + cmd + ")";
      Blast::ShellCommandExecutorWithCallback shell_command_executor(command);
      shell_command_executor.execute();
   }
}


void create_readme_file(Generator &generator)
{
   std::ofstream outfile5;
   outfile5.open(generator.get_project_name() + "/README.md", std::ios::binary);
   std::string main_file_content = README_FILE_CONTENT_TEMPLATE;
   ___replace(main_file_content, "[[PROJECT_NAME]]", generator.get_project_name());
   outfile5 << main_file_content;
   outfile5.close();
}


void create_main_file_with_configuration(Generator &generator)
{
   std::ofstream outfile5;
   outfile5.open(generator.get_project_name() + "/programs/main.cpp", std::ios::binary);
   std::string main_file_content = main_file_content_template_with_configuration;
   ___replace(main_file_content, "[[PROJECT_NAME]]", generator.get_project_name());
   ___replace(main_file_content, "[[PROGRAM_RUNNER_CLASS_NAME]]", PROGRAM_RUNNER_CLASS_NAME);
   ___replace(main_file_content, "[[PROGRAM_RUNNER_CLASS_END_FRAGMENTS_NAME]]", PROGRAM_RUNNER_CLASS_END_FRAGMENTS_NAME);
   outfile5 << main_file_content;
   outfile5.close();
}


void create_main_file(Generator &generator)
{
   std::ofstream outfile5;
   outfile5.open(generator.get_project_name() + "/programs/main.cpp", std::ios::binary);
   std::string main_file_content = main_file_content_template;
   ___replace(main_file_content, "[[PROJECT_NAME]]", generator.get_project_name());
   ___replace(main_file_content, "[[PROGRAM_RUNNER_CLASS_NAME]]", PROGRAM_RUNNER_CLASS_NAME);
   ___replace(main_file_content, "[[PROGRAM_RUNNER_CLASS_END_FRAGMENTS_NAME]]", PROGRAM_RUNNER_CLASS_END_FRAGMENTS_NAME);
   outfile5 << main_file_content;
   outfile5.close();
}


void create_gitignore(Generator &generator)
{
   std::string gitignore_file_filename = generator.get_project_name() + "/.gitignore";
   std::ofstream outfile;
   outfile.open(gitignore_file_filename, std::ios::binary);
   outfile << GITIGNORE_FILE_CONTENT;
   outfile.close();
}


void create_appinfo_yml(Generator &generator)
{
   std::string filename = generator.get_project_name() + "/appinfo.yml";
   std::ofstream outfile;
   outfile.open(filename, std::ios::binary);
   outfile << APPINFO_YML_FILE_CONTENT;
   outfile.close();
}


void copy_resource_files(Generator &generator)
{
   std::string resource_file_folder = "/Users/markoates/Repos/blast/programs/templates/resource_files/";
   std::string new_project_data_folder = generator.get_project_name() + "/bin/data/";
   std::string new_project_fixtures_folder = generator.get_project_name() + "/tests/fixtures/";
   std::string asset_name = "";

   std::filesystem::copy(resource_file_folder + "fonts/fa-solid-900.ttf", new_project_data_folder + "fonts/fa-solid-900.ttf");
   std::filesystem::copy(resource_file_folder + "fonts/fa-solid-900.ttf", new_project_fixtures_folder + "fonts/fa-solid-900.ttf");

   std::filesystem::copy(resource_file_folder + "fonts/Inter-Regular.ttf", new_project_data_folder + "fonts/Inter-Regular.ttf");
   std::filesystem::copy(resource_file_folder + "fonts/Inter-Regular.ttf", new_project_fixtures_folder + "fonts/Inter-Regular.ttf");

   std::filesystem::copy(resource_file_folder + "fonts/Inter-Medium.ttf", new_project_data_folder + "fonts/Inter-Medium.ttf");
   std::filesystem::copy(resource_file_folder + "fonts/Inter-Medium.ttf", new_project_fixtures_folder + "fonts/Inter-Medium.ttf");

   std::filesystem::copy(resource_file_folder + "fonts/Inter-Bold.ttf", new_project_data_folder + "fonts/Inter-Bold.ttf");
   std::filesystem::copy(resource_file_folder + "fonts/Inter-Bold.ttf", new_project_fixtures_folder + "fonts/Inter-Bold.ttf");

   std::filesystem::copy(resource_file_folder + "fonts/Abel-Regular.ttf", new_project_data_folder + "fonts/Abel-Regular.ttf");
   // TODO: Add symlinks for fonts in fixtures folder: e.g. "ln -s ../../../bin/data/fonts/Abel-Regular.ttf ./Abel-Regular.ttf"
   std::filesystem::copy(resource_file_folder + "fonts/Abel-Regular.ttf", new_project_fixtures_folder + "fonts/Abel-Regular.ttf");

   std::filesystem::copy(resource_file_folder + "fonts/PathwayGothicOne-Regular.ttf", new_project_data_folder + "fonts/PathwayGothicOne-Regular.ttf");
   std::filesystem::copy(resource_file_folder + "fonts/PathwayGothicOne-Regular.ttf", new_project_fixtures_folder + "fonts/PathwayGothicOne-Regular.ttf");

   std::filesystem::copy(resource_file_folder + "fonts/Oswald-Medium.ttf", new_project_data_folder + "fonts/Oswald-Medium.ttf");
   std::filesystem::copy(resource_file_folder + "fonts/Oswald-Medium.ttf", new_project_fixtures_folder + "fonts/Oswald-Medium.ttf");

   //std::filesystem::copy(resource_file_folder + "bitmaps/clubcatt-game-logo-01.jpg", new_project_data_folder + "bitmaps/clubcatt-game-logo-01.jpg");
   //std::filesystem::copy(resource_file_folder + "bitmaps/clubcatt-game-logo-01.jpg", new_project_fixtures_folder + "bitmaps/clubcatt-game-logo-01.jpg");

   std::filesystem::copy(resource_file_folder + "bitmaps/clubcatt-website-01.jpg", new_project_data_folder + "bitmaps/clubcatt-website-01.jpg");
   std::filesystem::copy(resource_file_folder + "bitmaps/clubcatt-website-01.jpg", new_project_fixtures_folder + "bitmaps/clubcatt-website-01.jpg");

   asset_name = "models/centered_unit_cube-02.obj";
   std::filesystem::copy(resource_file_folder + asset_name, new_project_data_folder + asset_name);
   std::filesystem::copy(resource_file_folder + asset_name, new_project_fixtures_folder + asset_name);

   asset_name = "bitmaps/clubcatt_cube_texture-01.png";
   std::filesystem::copy(resource_file_folder + asset_name, new_project_data_folder + asset_name);
   std::filesystem::copy(resource_file_folder + asset_name, new_project_fixtures_folder + asset_name);

   asset_name = "bitmaps/clubcatt_cube_texture-01b.png";
   std::filesystem::copy(resource_file_folder + asset_name, new_project_data_folder + asset_name);
   std::filesystem::copy(resource_file_folder + asset_name, new_project_fixtures_folder + asset_name);

   asset_name = "bitmaps/storyboard-1-01-1165x500.png";
   std::filesystem::copy(resource_file_folder + asset_name, new_project_data_folder + asset_name);
   std::filesystem::copy(resource_file_folder + asset_name, new_project_fixtures_folder + asset_name);

   asset_name = "bitmaps/storyboard-2-01-1165x500.png";
   std::filesystem::copy(resource_file_folder + asset_name, new_project_data_folder + asset_name);
   std::filesystem::copy(resource_file_folder + asset_name, new_project_fixtures_folder + asset_name);

   // Default icons
   std::string icon_filename = "icons/allegro-flare-generic-icon-1024.png";
   std::filesystem::copy(resource_file_folder + icon_filename, new_project_data_folder + icon_filename);
   std::filesystem::copy(resource_file_folder + icon_filename, new_project_fixtures_folder + icon_filename);
}


void create_directories(Generator &generator)
{
   system(generator.get_command_for_make_dir().c_str());
   system(generator.mkprojdir_and_keep_file("bin").c_str());
   system(generator.mkprojdir_and_keep_file("bin/data").c_str());
   system(generator.mkprojdir_and_keep_file("bin/data/bitmaps").c_str());
   system(generator.mkprojdir_and_keep_file("bin/data/fonts").c_str());
   system(generator.mkprojdir_and_keep_file("bin/data/models").c_str());
   system(generator.mkprojdir_and_keep_file("bin/data/samples").c_str());
   system(generator.mkprojdir_and_keep_file("bin/data/icons").c_str());
   system(generator.mkprojdir_and_keep_file("bin/data/samples/music_tracks").c_str());
   system(generator.mkprojdir_and_keep_file("bin/data/samples/sound_effects").c_str());
   system(generator.mkprojdir_and_keep_file("lib").c_str());
   system(generator.mkprojdir_and_keep_file("tmp").c_str());
   system(generator.mkprojdir_and_keep_file("tmp/test_snapshots").c_str());
   system(generator.mkprojdir_and_keep_file("docs").c_str());
   system(generator.mkprojdir_and_keep_file("include").c_str());
   system(generator.mkprojdir_and_keep_file("examples").c_str());
   system(generator.mkprojdir_and_keep_file("documentation").c_str());
   system(generator.mkprojdir_and_keep_file(std::string("include/") + generator.get_project_name()).c_str());
   system(generator.mkprojdir_and_keep_file("obj").c_str());
   system(generator.mkprojdir_and_keep_file("programs").c_str());
   system(generator.mkprojdir_and_keep_file("src").c_str());
   system(generator.mkprojdir_and_keep_file("tests").c_str());
   system(generator.mkprojdir_and_keep_file("tests/fixtures").c_str());
   system(generator.mkprojdir_and_keep_file("tests/fixtures/bitmaps").c_str());
   system(generator.mkprojdir_and_keep_file("tests/fixtures/fonts").c_str());
   system(generator.mkprojdir_and_keep_file("tests/fixtures/samples").c_str());
   system(generator.mkprojdir_and_keep_file("tests/fixtures/icons").c_str());
   system(generator.mkprojdir_and_keep_file("tests/fixtures/samples/music_tracks").c_str());
   system(generator.mkprojdir_and_keep_file("tests/fixtures/samples/sound_effects").c_str());
   system(generator.mkprojdir_and_keep_file("tests/fixtures/models").c_str());
   system(generator.mkprojdir_and_keep_file("quintessence").c_str());
}


void output_finished_message(std::string project_name)
{
   ConsoleOutputter console_output;
   std::stringstream finish_message;
   finish_message << "✅ Project files under \"" << project_name << "/\" generated." << std::endl;
   console_output.output_line(finish_message.str());
}



void generate_gameplay_screen_class(std::string project_name)
{
   std::string cmd = "~/Repos/blast/bin/programs/component_generator " + project_name + "/Gameplay/Screen gameplay_screen";
   std::string command = std::string("(cd ") + project_name + " && " + cmd + ")";
   Blast::ShellCommandExecutorWithCallback shell_command_executor(command);
   shell_command_executor.execute();
}


void generate_complete_gameplay_screen_class(std::string project_name)
{
   std::string cmd = "~/Repos/blast/bin/programs/component_generator " + project_name + "/Gameplay/Screen complete_gameplay_screen";
   std::string command = std::string("(cd ") + project_name + " && " + cmd + ")";
   Blast::ShellCommandExecutorWithCallback shell_command_executor(command);
   shell_command_executor.execute();
}


void generate_gameplay_level_class(std::string project_name)
{
   std::string cmd = "~/Repos/blast/bin/programs/component_generator " + project_name + "/Gameplay/Level gameplay_level";
   std::string command = std::string("(cd ") + project_name + " && " + cmd + ")";
   Blast::ShellCommandExecutorWithCallback shell_command_executor(command);
   shell_command_executor.execute();
}


void generate_gameplay_level_factory_class(std::string project_name)
{
   std::string cmd = "~/Repos/blast/bin/programs/component_generator " + project_name + "/Gameplay/LevelFactory gameplay_level_factory";
   std::string command = std::string("(cd ") + project_name + " && " + cmd + ")";
   Blast::ShellCommandExecutorWithCallback shell_command_executor(command);
   shell_command_executor.execute();
}


void generate_complete_game_configurations_main_class(std::string project_name)
{
   std::string cmd = "~/Repos/blast/bin/programs/component_generator " + project_name + "/GameConfigurations/Main complete_game_configuration";
   std::string command = std::string("(cd ") + project_name + " && " + cmd + ")";
   Blast::ShellCommandExecutorWithCallback shell_command_executor(command);
   shell_command_executor.execute();
}


void generate_game_configurations_main_class(std::string project_name)
{
   std::string cmd = "~/Repos/blast/bin/programs/component_generator " + project_name + "/GameConfigurations/Main game_configuration";
   std::string command = std::string("(cd ") + project_name + " && " + cmd + ")";
   Blast::ShellCommandExecutorWithCallback shell_command_executor(command);
   shell_command_executor.execute();
}


void generate_runner_class(std::string project_name)
{
   std::string cmd = "~/Repos/blast/bin/programs/component_generator " + project_name + "/" + PROGRAM_RUNNER_CLASS_NAME + " runner_with_router";
   std::string command = std::string("(cd ") + project_name + " && " + cmd + ")";
   Blast::ShellCommandExecutorWithCallback shell_command_executor(command);
   shell_command_executor.execute();
}


bool project_folder_exists(std::string project_name)
{
   std::string folder_path = "./" + project_name;
   bool exists = (std::filesystem::exists(folder_path) && std::filesystem::is_directory(folder_path));
   return exists;
}


int main(int argc, char **argv)
{
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   if (args.size() <= 1) throw std::runtime_error("You must pass a project name");

   Generator generator(argv[1]);
   std::string project_name = generator.get_project_name();
   // TODO: sanitize the project_name (it's passed in to shell commands)

   // Guard against overwriting an existing folder
   if (project_folder_exists(project_name))
   {
      throw std::runtime_error("This project folder already exists.");
   }

   // Generate the files
   create_directories(generator);
   create_makefile(generator);
   create_gitignore(generator);
   create_appinfo_yml(generator);
   create_readme_file(generator);
   create_test_runner(generator);
   copy_resource_files(generator);
   create_version_yaml(generator);

   //generate_gameplay_screen_class(project_name);
   generate_gameplay_level_class(project_name);
   { // With AllegroFlare-managed Runner - Runners::Complete
      generate_complete_game_configurations_main_class(project_name);
      create_main_file_with_configuration(generator);
      generate_complete_gameplay_screen_class(project_name);
      create_game_progress_and_state_info_classes(project_name);
   }
   { // With previous "manual" runner
      //create_main_file(generator);
      //generate_gameplay_screen_class(project_name);
      //generate_game_configurations_main_class(project_name);
      //generate_runner_class(project_name);
   }

   output_finished_message(project_name);

   return 0;
}


