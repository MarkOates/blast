FOCUSED_COMPONENT_NAME=Blast/Project/SymlinkChecker
FOCUSED_TEST_FILTER=



PROJECT_NAME=blast
VERSION_NUMBER=0.0.1
LIBS_ROOT=/Users/markoates/Repos
ALLEGRO_INCLUDE_DIR=$(LIBS_ROOT)/allegro5/build/include
ALLEGRO_LIB_DIR=$(LIBS_ROOT)/allegro5/build/lib
NCURSES_INCLUDE_DIR=/usr/local/opt/ncurses/include
NCURSES_LIB_DIR=/usr/local/opt/ncurses/lib
YAML_CPP_DIR=$(LIBS_ROOT)/yaml-cpp
YAML_CPP_LIB_DIR=$(YAML_CPP_DIR)/build
YAML_CPP_INCLUDE_DIR=$(YAML_CPP_DIR)/include
GOOGLE_TEST_DIR=$(LIBS_ROOT)/googletest
GOOGLE_TEST_LIB_DIR=$(GOOGLE_TEST_DIR)/build/googlemock/gtest
GOOGLE_TEST_INCLUDE_DIR=$(GOOGLE_TEST_DIR)/googletest/include



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
	$(call output_terminal_message,"Make all the object files")
	@make objects -j8
	$(call output_terminal_message,"Make all the test files")
	@make tests -j8
	$(call output_terminal_message,"Run the tests for all the components")
	@make run_tests
	$(call output_terminal_message,"Build the library")
	@make library
	$(call output_terminal_message,"Make all the programs")
	@make programs -j8
	$(call output_terminal_message,"Make all the example programs")
	@make examples -j8
	$(call output_terminal_message,"================= FINISHED! ===================")



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
	@./build



programs: $(PROGRAMS)



objects: $(OBJECTS)



examples: $(EXAMPLES)



library: $(LIBRARY_NAME)



tests: $(INDIVIDUAL_TEST_EXECUTABLES) bin/tests/test_runner



run_tests: tests
	find bin/tests -type f -exec {} \;



$(LIBRARY_NAME): $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling library \e[1m\e[36m$@\033[0m..."
	@ar rs $(LIBRARY_NAME) $^
	@echo "done. Library file at \033[1m\033[32m$@\033[0m"



bin/programs/%: programs/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling program from \e[1m\e[36m$<\033[0m..."
	@g++ -std=c++17 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< -o $@ -I./include -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS)  -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/examples/%: examples/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling example program from \e[1m\e[36m$<\033[0m..."
	@g++ -std=c++17 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< -o $@ -I./include  -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	@printf "compiling object file from \e[1m\e[34m$<\033[0m..."
	@g++ -c -std=c++17 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(YAML_CPP_INCLUDE_DIR)  -I$(NCURSES_INCLUDE_DIR) -L$(NCURSES_LIB_DIR) -l$(NCURSES_LIB)
	@echo "done. object at \033[1m\033[32m$@\033[0m"



obj/tests/%.o: tests/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling test object file from \e[1m\e[36m$<\033[0m..."
	@g++ -c -std=c++17 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(GOOGLE_TEST_INCLUDE_DIR)
	@echo "done. Object at \033[1m\033[32m$@\033[0m"



bin/tests/%: obj/tests/%.o obj/tests/test_runner.o
	@mkdir -p $(@D)
	@printf "compiling standalone test from \e[1m\e[36m$<\033[0m..."
	@g++ -std=c++17 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< obj/tests/test_runner.o -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) -l$(NCURSES_LIB)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



bin/tests/test_runner: $(TEST_OBJECTS) obj/tests/test_runner.o
	@mkdir -p $(@D)
	@printf "compiling test_runer from \e[1m\e[36m$<\033[0m..."
	@g++ -std=c++17 -Qunused-arguments -Wall -Wuninitialized -Weffc++ $(OBJECTS) obj/tests/test_runner.o $< -o $@ -l$(GOOGLE_TEST_LIBS) -I./include -I$(GOOGLE_TEST_INCLUDE_DIR) -L$(GOOGLE_TEST_LIB_DIR) -l$(NCURSES_LIB)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



clean:
	-rm -rdf obj/
	-rm $(OBJECTS)
	-rm $(TEST_OBJECTS)
	-rm $(ALL_COMPILED_EXECUTABLES_IN_BIN)
