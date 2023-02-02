#include <allegro5/allegro.h> // for compatibility with union/Makefile


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
bin/*
!bin/data/*
.DS_Store
*.a
obj/*
tmp/*
.deps/*
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




std::string PROGRAM_RUNNER_CLASS_NAME = "Runner";
std::string main_file_content_template = R"END(
#include <[[PROJECT_NAME]]/[[PROGRAM_RUNNER_CLASS_NAME]].hpp>
#include <allegro5/allegro.h>
#include <vector> // for parsing command line args
#include <algorithm> // for parsing command line args

int main(int argc, char **argv)
{
   std::vector<std::string> command_line_args;
   for (int i=1; i<argc; i++) command_line_args.push_back(argv[i]);
   bool contains_production_flag = std::count(command_line_args.begin(), command_line_args.end(), "--production");

   // TODO: improve this to return an error when an unrecognized flag is present

   std::string deployment_environment =
         contains_production_flag
         ? AllegroFlare::DeploymentEnvironment::ENVIRONMENT_PRODUCTION
         : AllegroFlare::DeploymentEnvironment::ENVIRONMENT_DEVELOPMENT;

   [[PROJECT_NAME]]::[[PROGRAM_RUNNER_CLASS_NAME]]().run(deployment_environment);
   return 0;
}
)END";



const std::string MAKEFILE_TEMPLATE = R"END(
FOCUSED_COMPONENT_NAME=Blast/Project/SymlinkChecker
FOCUSED_TEST_FILTER=



PROJECT_NAME=mylibrary
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



QUINTESSENCE_BUILDER_EXECUTABLE=~/Repos/blast/bin/programs/quintessence_from_yaml



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
TERMINAL_COLOR_GREEN=\033[1;32m
TERMINAL_COLOR_BLUE=\033[1;34m
TERMINAL_COLOR_LIGHT_BLUE=\033[1;94m
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
	$(call output_terminal_message,"Celebrate passing all tests")
	@make celebrate_passing_tests
	$(call output_terminal_message,"Build the library")
	@make library
	$(call output_terminal_message,"Make all the programs")
	@make programs
	$(call output_terminal_message,"Make all the example programs")
	@make examples
	$(call output_terminal_message,"🀫 🀫 🀫 🀫 🀫 🀫 🀫 FINISHED! 🀫 🀫 🀫 🀫 🀫 🀫 🀫")



focus:
	$(call output_terminal_message,"Announce built type")
	@echo "Focusing build on \033[48;5;27m$(FOCUSED_COMPONENT_NAME)$(TERMINAL_COLOR_RESET)"
	@echo "testing filter in $(FOCUSED_TEST_FILTER)"
	$(call output_terminal_message,"Compose componets from all quintessence files")
	@make quintessences
	$(call output_terminal_message,"Make all the component object files")
	@make objects
	$(call output_terminal_message,"Make the focused component test")
	@make obj/tests/$(FOCUSED_COMPONENT_NAME)Test.o
	$(call output_terminal_message,"Make the focused component test")
	@make bin/tests/$(FOCUSED_COMPONENT_NAME)Test
	$(call output_terminal_message,"Run the focused component test")
	@./bin/tests/$(FOCUSED_COMPONENT_NAME)Test --gtest_filter=*$(FOCUSED_TEST_NAME)*
	$(call output_terminal_message,"Make all the programs")
	@make programs
	$(call output_terminal_message,"Celebrate passing focused component tests")
	@make celebrate_built_component



quintessences: $(QUINTESSENCE_SOURCES)
	[ -f $(QUINTESSENCE_BUILDER_EXECUTABLE) ] || echo "The needed executable $(QUINTESSENCE_BUILDER_EXECUTABLE) was not found"
	find quintessence -name '*.q.yml' | xargs $(QUINTESSENCE_BUILDER_EXECUTABLE) -f



programs: $(PROGRAMS)



objects: $(OBJECTS)



examples: $(EXAMPLES)



library: $(LIBRARY_NAME)



test_objects: $(TEST_OBJECTS)



tests: $(INDIVIDUAL_TEST_EXECUTABLES) bin/run_all_tests



run_tests: tests
	bin/run_all_tests



celebrate_passing_tests:
	@echo "\033[1m\033[32m🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"
	@echo "\033[1m\033[32m🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"
	@echo "\033[1m\033[32m🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫    PASS   🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"
	@echo "\033[1m\033[32m🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"
	@echo "\033[1m\033[32m🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"



celebrate_built_component:
	@echo "\033[1m$(TERMINAL_COLOR_BLUE)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"
	@echo "\033[1m$(TERMINAL_COLOR_BLUE)🀫$(TERMINAL_COLOR_GREEN) 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_BLUE)🀫\033[0m"
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_BLUE)🀫$(TERMINAL_COLOR_GREEN) 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫  $(TERMINAL_COLOR_BLUE)   COMPONENT BUILT     $(TERMINAL_COLOR_GREEN)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_BLUE)🀫\033[0m"
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_BLUE)🀫$(TERMINAL_COLOR_GREEN) 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_BLUE)🀫\033[0m"
	@echo "\033[1m$(TERMINAL_COLOR_BLUE)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"



celebrate_everything_built:
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_GREEN)████$(TERMINAL_COLOR_YELLOW)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_GREEN)████$(TERMINAL_COLOR_RESET)\033[0m"
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_GREEN)██$(TERMINAL_COLOR_GREEN)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_GREEN)██$(TERMINAL_COLOR_RESET)\033[0m"
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_YELLOW)🀫$(TERMINAL_COLOR_GREEN) 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫        BUILT      🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_YELLOW)🀫$(TERMINAL_COLOR_RESET)\033[0m"
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_GREEN)██$(TERMINAL_COLOR_GREEN)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_GREEN)██$(TERMINAL_COLOR_RESET)\033[0m"
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_GREEN)████$(TERMINAL_COLOR_YELLOW)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_GREEN)████$(TERMINAL_COLOR_RESET)\033[0m"



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
	@g++ -std=c++1z -Qunused-arguments -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< obj/tests/[[TEST_RUNNER_CLASS_NAME]].o -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) $(ALLEGRO_LIBS_LINK_MAIN_ARGS) -I$(ALLEGRO_FLARE_INCLUDE_DIR) -L$(ALLEGRO_FLARE_LIB_DIR) $(ALLEGRO_FLARE_LINK_ARGS) -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/run_all_tests: tests/[[TEST_RUNNER_CLASS_NAME]].cpp $(TEST_OBJECTS)
	echo $(TEST_OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling test_runer \e[1m\e[36m$<\033[0m..."
	@g++ -std=gnu++11 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $(OBJECTS) $(TEST_OBJECTS) $< -o $@ -I./include -l$(GOOGLE_TEST_LIBS) -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) $(ALLEGRO_LIBS_LINK_MAIN_ARGS) -D_XOPEN_SOURCE_EXTENDED



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


#include <Blast/ShellCommandExecutorWithCallback.hpp>


void create_makefile(Generator &generator)
{
   std::string command = std::string("(cd ") + generator.get_project_name() + " && ln -s ../union/Makefile ./Makefile)";
   Blast::ShellCommandExecutorWithCallback makefile_symlink_command_executor(command);
   makefile_symlink_command_executor.execute();

   //std::ofstream outfile;
   //outfile.open(generator.get_project_name() + "/Makefile", std::ios::binary);
   //std::string makefile_content = MAKEFILE_TEMPLATE;
   //___replace(makefile_content, "[[TEST_RUNNER_CLASS_NAME]]", TEST_RUNNER_CLASS_NAME);
   //outfile << makefile_content;
   //outfile.close();
}


void create_test_runner(Generator &generator)
{
   std::string command = std::string("(cd ") + generator.get_project_name() + " && ln -s ../../union/tests/TestRunner.cpp ./tests/TestRunner.cpp)";
   Blast::ShellCommandExecutorWithCallback makefile_symlink_command_executor(command);
   makefile_symlink_command_executor.execute();

   //std::ofstream outfile6;
   //outfile6.open(generator.get_project_name() + "/tests/" + TEST_RUNNER_CLASS_NAME + ".cpp", std::ios::binary);
   //outfile6 << TEST_RUNNER_FILE_CONTENT;
   //outfile6.close();
}


void create_main_file(Generator &generator)
{
   std::ofstream outfile5;
   outfile5.open(generator.get_project_name() + "/programs/main.cpp", std::ios::binary);
   std::string main_file_content = main_file_content_template;
   ___replace(main_file_content, "[[PROJECT_NAME]]", generator.get_project_name());
   ___replace(main_file_content, "[[PROGRAM_RUNNER_CLASS_NAME]]", PROGRAM_RUNNER_CLASS_NAME);
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


void create_directories(Generator &generator)
{
   system(generator.get_command_for_make_dir().c_str());
   system(generator.mkprojdir_and_keep_file("bin").c_str());
   system(generator.mkprojdir_and_keep_file("lib").c_str());
   system(generator.mkprojdir_and_keep_file("tmp").c_str());
   system(generator.mkprojdir_and_keep_file("docs").c_str());
   system(generator.mkprojdir_and_keep_file("include").c_str());
   system(generator.mkprojdir_and_keep_file("examples").c_str());
   system(generator.mkprojdir_and_keep_file("documentation").c_str());
   system(generator.mkprojdir_and_keep_file(std::string("include/") + generator.get_project_name()).c_str());
   system(generator.mkprojdir_and_keep_file("obj").c_str());
   system(generator.mkprojdir_and_keep_file("programs").c_str());
   system(generator.mkprojdir_and_keep_file("src").c_str());
   system(generator.mkprojdir_and_keep_file("tests").c_str());
   system(generator.mkprojdir_and_keep_file("quintessence").c_str());
}


void output_finished_message(std::string project_name)
{
   ConsoleOutputter console_output;
   std::stringstream finish_message;
   finish_message << "✅ Project files under \"" << project_name << "/\" generated." << std::endl;
   console_output.output_line(finish_message.str());
}


void generate_gameplay_screen_screen_class(std::string project_name)
{
   // TODO: prompt to create
   // TODO: sanitize the project name so it cannot be injected with arbitrary commands
   Blast::ShellCommandExecutorWithCallback shell_command_executor(
      "~/Repos/blast/bin/programs/component_generator " + project_name + "/PrimaryGameplay/Screen screen"
   );
   shell_command_executor.execute();
}


void generate_runner_class(std::string project_name)
{
   // TODO: prompt to create
   // TODO: sanitize the project name so it cannot be injected with arbitrary commands
   Blast::ShellCommandExecutorWithCallback shell_command_executor(
      "~/Repos/blast/bin/programs/component_generator " + project_name + "/Runner runner"
   );
   shell_command_executor.execute();
}


int main(int argc, char **argv)
{
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   if (args.size() <= 1) throw std::runtime_error("You must pass a project name");

   Generator generator(argv[1]);
   std::string project_name = generator.get_project_name();
   // TODO: sanitize the project_name (it's passed in to shell commands)

   create_directories(generator);
   create_makefile(generator);
   create_gitignore(generator);
   create_main_file(generator);
   create_test_runner(generator);

   generate_gameplay_screen_screen_class(project_name);
   generate_runner_class(project_name);

   output_finished_message(project_name);

   return 0;
}

