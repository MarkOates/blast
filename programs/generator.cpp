#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>



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
bin/*
!bin/data/*
.DS_Store
*.a
obj/*
.DS_Store
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




std::string PROGRAM_RUNNER_CLASS_NAME = "ProgramRunner";
std::string main_file_content_template = R"END(
//#include <[[PROGRAM_RUNNER_CLASS_NAME]].hpp>
#include <allegro5/allegro.h>

int main(int argc, char **argv)
{
   //[[PROGRAM_RUNNER_CLASS_NAME]]().run();
   return 0;
}
)END";



std::string PROGRAM_RUNNER_TEST_FILE_CONTENT = R"END(
#include <gtest/gtest.h>

#include <[[PROGRAM_RUNNER_CLASS_NAME]].hpp>

TEST([[PROGRAM_RUNNER_CLASS_NAME]]Test, run__returns_the_expected_response)
{
   [[PROGRAM_RUNNER_CLASS_NAME]] component;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, component.run());
}
)END";



const std::string MAKEFILE_TEMPLATE = R"END(PROJECT_NAME=mylibrary
VERSION_NUMBER=0.0.1
LIBS_ROOT=/Users/markoates/Repos
ALLEGRO_INCLUDE_DIR=$(LIBS_ROOT)/allegro5/build/include
ALLEGRO_LIB_DIR=$(LIBS_ROOT)/allegro5/build/lib
GOOGLE_TEST_DIR=$(LIBS_ROOT)/googletest
GOOGLE_TEST_LIB_DIR=$(GOOGLE_TEST_DIR)/build/googlemock/gtest
GOOGLE_TEST_INCLUDE_DIR=$(GOOGLE_TEST_DIR)/googletest/include
NCURSES_INCLUDE_DIR=/usr/local/opt/ncurses/include
NCURSES_LIB_DIR=/usr/local/opt/ncurses/lib
YAML_CPP_DIR=$(LIBS_ROOT)/yaml-cpp
YAML_CPP_LIB_DIR=$(YAML_CPP_DIR)/build
YAML_CPP_INCLUDE_DIR=$(YAML_CPP_DIR)/include



ALLEGRO_LIBS=allegro_color allegro_font allegro_ttf allegro_dialog allegro_audio allegro_acodec allegro_primitives allegro_image allegro
ALLEGRO_LIBS_MAIN=$(ALLEGRO_LIBS) allegro_main
GOOGLE_TEST_LIBS=gtest
NCURSES_LIB=ncurses
YAML_CPP_LIBS=yaml-cpp



SOURCES := $(shell find src -name '*.cpp')
QUINTESSENCE_SOURCES := $(shell find quintessence -name '*.q.yml')
PROGRAM_SOURCES := $(shell find programs -name '*.cpp')
EXAMPLE_SOURCES := $(shell find examples -name '*.cpp')
TEST_SOURCES := $(shell find tests -name '*Test.cpp')
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)
PROGRAMS := $(PROGRAM_SOURCES:programs/%.cpp=bin/programs/%)
EXAMPLES := $(EXAMPLE_SOURCES:examples/%.cpp=bin/examples/%)
TEST_OBJECTS := $(TEST_SOURCES:tests/%.cpp=obj/tests/%.o)
LIBRARY_NAME := lib/lib$(PROJECT_NAME)-$(VERSION_NUMBER).a
INDIVIDUAL_TEST_EXECUTABLES := $(TEST_SOURCES:tests/%.cpp=bin/tests/%)
ALL_COMPILED_EXECUTABLES_IN_BIN := $(shell find bin/**/* -perm +111 -type f)



ALLEGRO_LIBS_LINK_ARGS := $(ALLEGRO_LIBS:%=-l%)
ALLEGRO_LIBS_LINK_MAIN_ARGS := $(ALLEGRO_LIBS_MAIN:%=-l%)



TERMINAL_COLOR_YELLOW=\033[1;33m
TERMINAL_COLOR_RESET=\033[0m



define output_terminal_message
	$(eval compteur=$(shell echo $$(($(compteur)+1))))
	@echo "\n$(TERMINAL_COLOR_YELLOW)===== Stage $(compteur): $(1) =====$(TERMINAL_COLOR_RESET)\n"
endef



.PHONY: main quintessence programs objects examples library tests run_tests



main:
	$(call output_terminal_message,"Compose componets from all quintessence files")
	@make quintessences
	$(call output_terminal_message,"Make all the component object files")
	@make objects
	$(call output_terminal_message,"Make all the test objects")
	@make test_objects
	$(call output_terminal_message,"Make all the test executables")
	@make tests
	$(call output_terminal_message,"Run the tests for all the components")
	@make run_tests
	$(call output_terminal_message,"Build the library")
	@make library
	$(call output_terminal_message,"Make all the programs")
	@make programs
	$(call output_terminal_message,"Make all the example programs")
	@make examples
	$(call output_terminal_message,"🀫 🀫 🀫 🀫 🀫 🀫 🀫 FINISHED! 🀫 🀫 🀫 🀫 🀫 🀫 🀫")



quintessences: $(QUINTESSENCE_SOURCES)
	@./build



programs: $(PROGRAMS)



objects: $(OBJECTS)



examples: $(EXAMPLES)



library: $(LIBRARY_NAME)



test_objects: $(TEST_OBJECTS)



tests: $(INDIVIDUAL_TEST_EXECUTABLES) bin/run_all_tests



run_tests: tests
	bin/run_all_tests



bin/programs/%: programs/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling program \e[1m\e[36m$<\033[0m..."
	@g++ -std=gnu++11 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< -o $@ -I./include -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) $(ALLEGRO_LIBS_LINK_MAIN_ARGS) -D_XOPEN_SOURCE_EXTENDED
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/examples/%: examples/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling example \e[1m\e[36m$<\033[0m..."
	@g++ -std=gnu++11 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< -o $@ -I./include -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) $(ALLEGRO_LIBS_LINK_MAIN_ARGS) -D_XOPEN_SOURCE_EXTENDED
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	@printf "compiling object file \e[1m\e[34m$<\033[0m..."
	@g++ -c -std=gnu++11 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -D_XOPEN_SOURCE_EXTENDED
	@echo "done. object at \033[1m\033[32m$@\033[0m"



$(LIBRARY_NAME): $(OBJECTS)
	@printf "compiling library \e[1m\e[36m$@\033[0m..."
ifeq ($(OBJECTS),)
	@echo "\033[1m\033[32mnothing to be done, there are no objects to build into a library\033[0m."
else
	@ar rs $(LIBRARY_NAME) $^
	@echo "done. Library file at \033[1m\033[32m$@\033[0m"
endif



obj/tests/%.o: tests/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling test object file \e[1m\e[36m$<\033[0m..."
	@g++ -c -std=gnu++11 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -I$(YAML_CPP_INCLUDE_DIR) -I$(ALLEGRO_FLARE_INCLUDE_DIR)
	@echo "done. Object at \033[1m\033[32m$@\033[0m"



obj/tests/[[TEST_RUNNER_CLASS_NAME]].o: tests/[[TEST_RUNNER_CLASS_NAME]].cpp
	@mkdir -p $(@D)
	@printf "compiling test object for [[TEST_RUNNER_CLASS_NAME]] \e[1m\e[36m$<\033[0m..."
	@g++ -c -std=gnu++11 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $< -o $@ -I$(GOOGLE_TEST_INCLUDE_DIR)
	@echo "done. Object at \033[1m\033[32m$@\033[0m"



bin/tests/%: obj/tests/%.o obj/tests/[[TEST_RUNNER_CLASS_NAME]].o
	@mkdir -p $(@D)
	@printf "compiling standalone test \e[1m\e[36m$<\033[0m..."
	@g++ -std=c++1z -Qunused-arguments -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< obj/tests/[[TEST_RUNNER_CLASS_NAME]].o -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) $(ALLEGRO_LIBS_LINK_ARGS) -I$(ALLEGRO_FLARE_INCLUDE_DIR) -L$(ALLEGRO_FLARE_LIB_DIR) $(ALLEGRO_FLARE_LINK_ARGS) -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/run_all_tests: tests/[[TEST_RUNNER_CLASS_NAME]].cpp $(TEST_OBJECTS)
	echo $(TEST_OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling test_runer \e[1m\e[36m$<\033[0m..."
	@g++ -std=gnu++11 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $(OBJECTS) $(TEST_OBJECTS) $< -o $@ -I./include -l$(GOOGLE_TEST_LIBS) -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) $(ALLEGRO_LIBS_LINK_ARGS) -D_XOPEN_SOURCE_EXTENDED



clean:
	-rm -rdf obj/
	-rm $(PROGRAMS)
	-rm $(EXAMPLES)
	-rm $(ALL_COMPILED_EXECUTABLES_IN_BIN)



fresh:
	make clean
	make -j8
	make bin/run_all_tests
)END";



std::string build_file_template = R"END(#!/bin/bash
executable_filename=~/Repos/blast/bin/programs/quintessence_from_yaml
[ -f $executable_filename ] || echo "The needed executable $executable_filename was not found"
find quintessence -name '*.q.yml' | xargs $executable_filename
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
   std::string mkprojdir(std::string dir)
   {
      std::stringstream command;
      command << "mkdir \"" << project_name << "/" << dir << "\"";
      return command.str();
   }
};


int main(int argc, char **argv)
{
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   if (args.size() <= 1) throw std::runtime_error("You must pass a project name");

   Generator generator(argv[1]);
   ConsoleOutputter console_output;

   system(generator.get_command_for_make_dir().c_str());
   system(generator.mkprojdir("bin").c_str());
   system(generator.mkprojdir("lib").c_str());
   system(generator.mkprojdir("include").c_str());
   system(generator.mkprojdir("examples").c_str());
   system(generator.mkprojdir(std::string("include/") + generator.get_project_name()).c_str());
   system(generator.mkprojdir("obj").c_str());
   system(generator.mkprojdir("programs").c_str());
   system(generator.mkprojdir("src").c_str());
   system(generator.mkprojdir("tests").c_str());
   system(generator.mkprojdir("quintessence").c_str());

   std::ofstream outfile(generator.get_project_name() + "/Makefile");
   std::string makefile_content = MAKEFILE_TEMPLATE;
   ___replace(makefile_content, "[[TEST_RUNNER_CLASS_NAME]]", TEST_RUNNER_CLASS_NAME);
   outfile << makefile_content;
   outfile.close();

   std::string gitignore_file_filename = generator.get_project_name() + "/.gitignore";
   std::ofstream outfile3(gitignore_file_filename);
   outfile3 << GITIGNORE_FILE_CONTENT;
   outfile.close();

   //std::stringstream program_runner_path_name;
   //program_runner_path_name << generator.get_project_name();
   //program_runner_path_name << "/quintessence/" << PROGRAM_RUNNER_CLASS_NAME << ".q.yml";

   //std::ofstream outfile4(program_runner_path_name.str());
   //std::string program_runner_quintessence_file_content = PROGRAM_RUNNER_FILE_CONTENT;
   //outfile4 << program_runner_quintessence_file_content;
   //outfile4.close();

   std::ofstream outfile5(generator.get_project_name() + "/programs/main.cpp");
   std::string main_file_content = main_file_content_template;
   ___replace(main_file_content, "[[PROGRAM_RUNNER_CLASS_NAME]]", PROGRAM_RUNNER_CLASS_NAME);
   outfile5 << main_file_content;
   outfile5.close();

   std::ofstream outfile6(generator.get_project_name() + "/tests/" + TEST_RUNNER_CLASS_NAME + ".cpp");
   outfile6 << TEST_RUNNER_FILE_CONTENT;
   outfile6.close();

   //std::ofstream outfile7(generator.get_project_name() + "/tests/" + PROGRAM_RUNNER_CLASS_NAME + "Test.cpp");
   //std::string program_runner_test_file_content = PROGRAM_RUNNER_TEST_FILE_CONTENT;
   //___replace(program_runner_test_file_content, "[[PROGRAM_RUNNER_CLASS_NAME]]", PROGRAM_RUNNER_CLASS_NAME);
   //outfile7 << program_runner_test_file_content;
   //outfile7.close();

   std::string build_file_filename = generator.get_project_name() + "/build";
   std::ofstream outfile2(build_file_filename);
   std::string build_file_content = build_file_template;
   outfile2 << build_file_content;
   outfile.close();
   system((std::string("chmod +x ") + build_file_filename).c_str());

   std::string rerun_script_filename = generator.get_project_name() + "/rr";
   std::ofstream outfile8(rerun_script_filename);
   outfile8 << RERUN_SCRIPT_CONTENT;
   outfile8.close();
   system((std::string("chmod +x ") + rerun_script_filename).c_str());

   std::string rerun_cat_file_script_filename = generator.get_project_name() + "/" + RERUN_CAT_FILE_SCRIPT_FILENAME;
   std::ofstream outfile9(rerun_cat_file_script_filename);
   outfile9 << RERUN_CAT_FILE_SCRIPT_CONTENT;
   outfile9.close();
   system((std::string("chmod +x ") + rerun_cat_file_script_filename).c_str());

   std::string hash_check_script_filename = generator.get_project_name() + "/" + HASH_CHECK_FILENAME;
   std::ofstream outfile10(hash_check_script_filename);
   outfile10 << HASH_CHECK_FILE_CONTENTS;
   outfile10.close();
   system((std::string("chmod +x ") + hash_check_script_filename).c_str());

   std::stringstream finish_message;
   finish_message << "✅ Project files under \"" << generator.get_project_name() << "/\" generated." << std::endl;
   finish_message << "⚠️ Important: You should now generate your first component by first cd-ing into your " << std::endl;
   finish_message << "project directory (\"cd " << generator.get_project_name() << "\") and running the command:" << std::endl;
   finish_message << std::endl;
   finish_message << "  ~/Repos/blast/bin/programs/component_generator NameOfYourComponent" << std::endl;
   finish_message << std::endl;
   finish_message << "📝 Once in the \"" << generator.get_project_name() << "\" directory, use the rerun \"./rr\" "
                  << "script in a separate terminal window to develop your component.  It will run the \"./build\" script "
                  << "to generate and build the first source files from the "
                  << "quintessence/ directory (\"quintessence/" << PROGRAM_RUNNER_CLASS_NAME << ".q.yml\"). "
                  << "as well as build and run the test file \"tests/" << PROGRAM_RUNNER_CLASS_NAME << "Test.cpp\" for the "
                  << "component." << std::endl;

   console_output.output_line(finish_message.str());

   std::runtime_error("You must pass a project name");

   return 0;
}

