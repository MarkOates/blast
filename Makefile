# see this SO for techniques in using a separate file to define variables
# https://unix.stackexchange.com/questions/235223/makefile-include-env-file


# Silence the "make[1]: Entering directory ..." messages
MAKEFLAGS += --no-print-directory

FOCUSED_PROJECT_FOLDER_FILENAME=/Users/markoates/Repos/hexagon/bin/programs/data/tmp/current_project_directory.txt
# PROJECT_BASE_DIRECTORY := $$PWD
PROJECT_BASE_DIRECTORY=`cat ${FOCUSED_PROJECT_FOLDER_FILENAME}`
FOCUSED_COMPONENT_FILENAME=/Users/markoates/Repos/hexagon/bin/programs/data/tmp/focused_component.txt
BUILD_STATUS_SIGNALING_FILENAME=/Users/markoates/Repos/hexagon/bin/programs/data/tmp/build_signal.txt
FOCUSED_COMPONENT_NAME=`cat ${FOCUSED_COMPONENT_FILENAME}`
FOCUSED_TEST_FILTER=${FILTER}


mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))


PROJECT_LIB_NAME=mylibrary
VERSION_NUMBER=0.0.1
## This is a temporary hack to have blast/Makefile build with allegro_flare
ifeq ($(OS),Windows_NT)
	LIBS_ROOT=/home/Mark/Repos
	ASIO_LIBS_ROOT=$(LIBS_ROOT)
else
	LIBS_ROOT=/Users/markoates/Repos
	ASIO_LIBS_ROOT=$(LIBS_ROOT)
endif
ALLEGRO_INCLUDE_DIR=$(LIBS_ROOT)/allegro5/include
ALLEGRO_FLARE_INCLUDE_DIR=$(LIBS_ROOT)/allegro_flare/include
ALLEGRO_PLATFORM_INCLUDE_DIR=$(LIBS_ROOT)/allegro5/build/include
ALLEGRO_LIB_DIR=$(LIBS_ROOT)/allegro5/build/lib
ALLEGRO_FLARE_LIB_DIR=$(LIBS_ROOT)/allegro_flare/lib
ASIO_INCLUDE_DIR=$(ASIO_LIBS_ROOT)/asio/asio/include
GOOGLE_TEST_DIR=$(LIBS_ROOT)/googletest
GOOGLE_TEST_LIB_DIR=$(GOOGLE_TEST_DIR)/build/googlemock/gtest
GOOGLE_TEST_INCLUDE_DIR=$(GOOGLE_TEST_DIR)/googletest/include
GOOGLE_MOCK_INCLUDE_DIR=$(GOOGLE_TEST_DIR)/googlemock/include
YAML_CPP_DIR=$(LIBS_ROOT)/yaml-cpp
YAML_CPP_LIB_DIR=$(YAML_CPP_DIR)/build
YAML_CPP_INCLUDE_DIR=$(YAML_CPP_DIR)/include



QUINTESSENCE_BUILDER_EXECUTABLE=~/Repos/blast/bin/programs/quintessence_from_yaml
OUTPUT_BANNER_EXECUTABLE=~/Repos/blast/bin/programs/build_celebrator
SOURCE_RELEASER_EXECUTABLE=~/Repos/blast/bin/programs/create_source_release
WIN64_RELEASER_EXECUTABLE=~/Repos/blast/scripts/build_win64_release.sh
MACOS_RELEASER_EXECUTABLE=~/Repos/blast/bin/programs/macos_release_builder







ALLEGRO_LIBS=allegro_color allegro_font allegro_ttf allegro_dialog allegro_audio allegro_acodec allegro_video allegro_primitives allegro_image allegro
ALLEGRO_LIBS_MAIN=$(ALLEGRO_LIBS) allegro_main
ALLEGRO_FLARE_LIB=allegro_flare-0.8.11wip
ALLEGRO_FLARE_LIB_FOR_TESTS=allegro_flare-0.8.11wip-for_tests
GOOGLE_TEST_LIBS=gtest
GOOGLE_MOCK_LIBS=gmock
YAML_CPP_LIBS=yaml-cpp
ifeq ($(OS), Windows_NT)
	OPENGL_LIB=-lopengl32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OPENGL_LIB=[ERROR:OPENGL_LIBS_NOT_DEFINED_FOR_LINUX]
	endif
	ifeq ($(UNAME_S),Darwin)
		OPENGL_LIB=-framework OpenGL
	endif
endif



# Set an @rpath
ifeq ($(OS), Windows_NT)
  # Nothing to do, @rpath is expected to work without special cases
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		# Nothing to do, @rpath is expected to work without special cases
	endif
	ifeq ($(UNAME_S),Darwin)
	  RPATH_STATEMENT=-rpath '/usr/local/lib/'
	endif
endif




ifeq ($(OS), Windows_NT)
	# MIDI_AUDIO_LIB not supported in Windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		# MIDI_AUDIO_LIB not supported in Linux
	endif
	ifeq ($(UNAME_S),Darwin)
		MIDI_AUDIO_LIB=-framework CoreAudio -framework CoreMIDI -framework CoreFoundation
	endif
endif


#TEST_RUNNER_PROGRAM_NAME=TestRunnerWithFocusedTestPreflightCheck
TEST_RUNNER_PROGRAM_NAME=TestRunner



# ProjectMakefile can be included in each project repo, and includes values like
# PROJECT_LIB_NAME and VERSION_NUMBER
-include ProjectMakefile



# Preferred build warnings

ifeq ($(OS),Windows_NT)
else
	#DISABLE_UNUSED_LINK_ARGUMENTS_WARNING_FLAG is for unused command line arguments
	DISABLE_UNUSED_LINK_ARGUMENTS_WARNING_FLAG=-Qunused-arguments

	ERROR_IF_UNINITIALIZED=-Werror=uninitialized
	ERROR_IF_INCORRECT_RETURN_TYPE=-Werror=return-type
	ERROR_IF_CONSTRUCTOR_INIT_OUT_OF_ORDER=-Werror=reorder-ctor
	ERROR_IF_ACCIDENTAL_OVERLOAD=-Werror=overloaded-virtual
	ERROR_IF_VIRTUAL_NOT_MARKED_OVERRIDE=-Werror=inconsistent-missing-override
	ERROR_IF_MACRO_REDEFINED=-Werror=macro-redefined
	#TODO: Activate this ERROR_IF_UNKNOWN_ESCAPE_SEQUENCE error:
	#ERROR_IF_UNKNOWN_ESCAPE_SEQUENCE=-Werror=unknown-escape-sequence
	ERROR_IF_ASSIGNMENT_IN_CONDITIONAL=-Werror=parentheses
	ERROR_ON_HEADER_HYGINE=-Werror=header-hygiene
	# Implicit conversion with -conversion: https://chat.openai.com/c/eb58fb9d-507d-4361-bcc9-a8d87556d1e8
	ERROR_IF_IMPLICIT_CONVERSION=-Werror=conversion # Consider
	ERROR_IF_OVERFLOW_ON_CONVERSION=-Werror=overflow # Consider
	ERROR_IF_MISSING_TERMINATING_CHARACTER=-Werror=invalid-pp-token
	ERROR_IF_SELF_ASSIGNMENT_ON_FIELD=-Werror=self-assign-field
	# TODO: Consider using -Werror=switch:
	# ERROR_IF_UNHANDLED_ENUMERATION_VALUE=-Werror=switch
	# TODO: Consider using -fms-extensions to remove certain symbol errors that appear on ms-compilation only
  #NOTE: -fsanitize=address is added to this list thought it is in a different category of flags
	DISABLE_UNUSED_WARNINGS_FLAG=-Wno-unused-variable -Wno-unused-private-field -Wno-unused-function
	ERROR_IF_STRING_LITERAL_TO_CONST_CHAR=-Werror=writable-strings
	# TODO: Consider erroring -Wunused-lambda-capture, which will warn when there are variables in a lambda capture that are not used
	ERROR_IF_UNUSED_VARIABLE_IN_LAMBDA_CAPTURE=-Werror=unused-lambda-capture
	#TODO: Consider adding -Wheader-hygine to catch instances where a header may be present on clang but not on other systems
	# https://chat.openai.com/c/eb58fb9d-507d-4361-bcc9-a8d87556d1e8
	#TODO: Consider -Werror=literal-conversion e.g. ./include/AllegroFlare/AssetStudio/Asset.hpp:42:403: warning: implicit conversion from 'float' to 'int' changes value from 0.5 to 0 [-Wliteral-conversion]
	ERROR_IF_IMPLICIT_CONVERSION_TO_WRONG_TYPE=-Werror=literal-conversion
	WARN_IF_COMPARISON_OF_DIFFERENT_SIGNEDNESS=-Wsign-compare # gcc will enable this by default but clang apparently does not. This flag is added to align the two systems

	#TODO: update to this line that includes an out-of-order ctor error promotion
	#TODO: include -Woverloaded-virtual -Winconsistent-missing-override to promoted errors
	#TODO: consider unused-but-set-variable
	#TODO: consider braced-scalar-init
  WARNINGS_PROMOTED_TO_ERRORS_FLAGS=$(ERROR_IF_UNINITIALIZED) $(ERROR_IF_INCORRECT_RETURN_TYPE) $(ERROR_IF_CONSTRUCTOR_INIT_OUT_OF_ORDER) $(ERROR_IF_ACCIDENTAL_OVERLOAD) $(ERROR_IF_VIRTUAL_NOT_MARKED_OVERRIDE) $(ERROR_IF_MACRO_REDEFINED) $(ERROR_IF_ASSIGNMENT_IN_CONDITIONAL) $(ERROR_ON_HEADER_HYGINE) $(ERROR_IF_SELF_ASSIGNMENT_ON_FIELD) $(ERROR_IF_UNHANDLED_ENUMERATION_VALUE) $(ERROR_IF_MISSING_TERMINATING_CHARACTER) $(ERROR_IF_STRING_LITERAL_TO_CONST_CHAR) $(ERROR_IF_UNUSED_VARIABLE_IN_LAMBDA_CAPTURE) $(ERROR_IF_IMPLICIT_CONVERSION_TO_WRONG_TYPE) $(WARN_IF_COMPARISON_OF_DIFFERENT_SIGNEDNESS)
  #WARNINGS_PROMOTED_TO_ERRORS_FLAGS=$(ERROR_IF_UNINITIALIZED) $(ERROR_IF_INCORRECT_RETURN_TYPE) $(ERROR_ON_HEADER_HYGINE)

	ERROR_LIMIT_FLAG=-ferror-limit=1
endif






# NCURSES

# To use NCURSES, add "USING_NCURSES=TRUE" to your ProjectMakefile
# TODO: Fix "USING_NCURSES=FALSE" that will still evaluate to "ifdef USING_NCURSES"

ifdef USING_NCURSES
	ifeq ($(OS),Windows_NT)
		NCURSES_INCLUDE_DIR_ARG=-I/usr/include
		NCURSES_LIB_DIR_ARG=-L.
		NCURSES_REQUIRED_STATIC_FLAG_ARG=-DNCURSES_STATIC
	else
		NCURSES_INCLUDE_DIR_ARG=-I/usr/local/opt/ncurses/include
		NCURSES_LIB_DIR_ARG=-L/usr/local/opt/ncurses/lib
	endif

	NCURSES_LIB=ncurses
	NCURSES_LIB_ARG=-l$(NCURSES_LIB)
	# NOTE: the include args are not included in build steps, it's assumed (begrudgingly), that ncurses in installed on the system
	NCURSES_BUILD_ARGS=$(NCURSES_INCLUDE_DIR_ARG) $(NCURSES_REQUIRED_STATIC_FLAG_ARG)
	# NOTE: the include args are not included in link steps, it's assumed (begrudgingly), that ncurses in installed on the system
	NCURSES_LINK_ARGS=$(NCURSES_LIB_ARG)
endif





# ALLEGRO_FLARE

# To use ALLEGRO_FLARE, add "USING_ALLEGRO_FLARE=TRUE" to your ProjectMakefile

# TODO: modify this conditional to an ifdef
ifneq ($(USING_ALLEGRO_FLARE),FALSE)
	#ifeq ($(OS),Windows_NT)
	ALLEGRO_FLARE_BUILD_ARGS=-I$(ALLEGRO_FLARE_INCLUDE_DIR)
	ALLEGRO_FLARE_LINK_ARGS=-L$(ALLEGRO_FLARE_LIB_DIR) -l$(ALLEGRO_FLARE_LIB)
	#endif

	#NCURSES_LIB=ncurses
	#NCURSES_LIB_ARG=-l$(NCURSES_LIB)
	## NOTE: the include args are not included in build steps, it's assumed (begrudgingly), that ncurses in installed on the system
	#NCURSES_BUILD_ARGS=$(NCURSES_INCLUDE_DIR_ARG)
	## NOTE: the include args are not included in link steps, it's assumed (begrudgingly), that ncurses in installed on the system
	#NCURSES_LINK_ARGS=$(NCURSES_LIB_ARG)
endif




# BULLET PHYSICS

# For now, using bullet physics on Mac by installing through homebrew "brew install bullet"
# Note that the homebrew path is different depending on if you're using an Intel Mac or Apple Silicon Mac

ifeq ($(USING_BULLET_PHYSICS),TRUE)
	HOMEBREW_PATH_PREFIX := $(shell brew --prefix)
	echo "Using Bullet physics (USING_BULLET_PHYSICS=TRUE in ProjectMakefile)"
  BULLET_PHYSICS_LIB_DIR=$(HOMEBREW_PATH_PREFIX)/lib
  BULLET_PHYSICS_INCLUDE_DIR=$(HOMEBREW_PATH_PREFIX)/include/bullet
  BULLET_PHYSICS_LIBS=BulletDynamics BulletCollision LinearMath
  BULLET_PHYSICS_LIBS_LINK_ARGS := $(BULLET_PHYSICS_LIBS:%=-l%)

  BULLET_PHYSICS_BUILD_ARGS=-I$(BULLET_PHYSICS_INCLUDE_DIR)
  BULLET_PHYSICS_LINK_ARGS=-L$(BULLET_PHYSICS_LIB_DIR) $(BULLET_PHYSICS_LIBS_LINK_ARGS)
endif




# CURL

# To use CURL, add "USING_CURL=TRUE" to your ProjectMakefile

# TODO: modify this conditional to an ifdef
ifneq ($(USING_CURL),FALSE)
	#ifeq ($(OS),Windows_NT)
	#CURL_INCLUDE_DIR=??? ### This does not appear to be needed
	#CURL_BUILD_ARGS=-I$(CURL_INCLUDE_DIR) ### This does not appear to be needed
	#CURL_LIB_DIR=??? ### This does not appear to be needed
	#CURL_LIB_DIR_ARGS=-L$(CURL_LIB_DIR) ### This does not appear to be needed
	CURL_LIB=curl
	CURL_LINK_ARGS=$(CURL_LIB_DIR_ARGS) -l$(CURL_LIB)
	#endif

	#NCURSES_LIB=ncurses
	#NCURSES_LIB_ARG=-l$(NCURSES_LIB)
	## NOTE: the include args are not included in build steps, it's assumed (begrudgingly), that ncurses in installed on the system
	#NCURSES_BUILD_ARGS=$(NCURSES_INCLUDE_DIR_ARG)
	## NOTE: the include args are not included in link steps, it's assumed (begrudgingly), that ncurses in installed on the system
	#NCURSES_LINK_ARGS=$(NCURSES_LIB_ARG)
endif





# SQLITE

# To use SQLITE, add "USING_SQLITE=TRUE" to your ProjectMakefile

ifneq ($(USING_SQLITE),FALSE)
	SQLITE_LIB=sqlite3
	SQLITE_LINK_ARGS=-l$(SQLITE_LIB)
endif






SOURCES := $(shell find src -name '*.cpp')
QUINTESSENCE_SOURCES := $(shell find quintessence -name '*.q.yml')
PROGRAM_SOURCES := $(shell find programs -name '*.cpp')
EXAMPLE_SOURCES := $(shell find examples -name '*.cpp')
DEMO_SOURCES := $(shell find demos -name '*.cpp')
TEST_SOURCES := $(shell find tests -name '*Test.cpp')
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)
DEPS := $(SOURCES:src/%.cpp=.deps/%.d)
PROGRAMS := $(PROGRAM_SOURCES:programs/%.cpp=bin/programs/%)
EXAMPLES := $(EXAMPLE_SOURCES:examples/%.cpp=bin/examples/%)
DEMOS := $(DEMO_SOURCES:demos/%.cpp=bin/demos/%)
TEST_OBJECTS := $(TEST_SOURCES:tests/%.cpp=obj/tests/%.o)
LIBRARY_FOR_LINKING_NAME := $(PROJECT_LIB_NAME)-$(VERSION_NUMBER)
LIBRARY_FOR_TESTS_FOR_LINKING_NAME := $(LIBRARY_FOR_LINKING_NAME)-for_tests
LIBRARY_DIR := lib/
LIBRARY_FOR_TESTS_NAME := lib/lib$(PROJECT_LIB_NAME)-$(VERSION_NUMBER)-for_tests.a
LIBRARY_NAME := lib/lib$(PROJECT_LIB_NAME)-$(VERSION_NUMBER).a
INDIVIDUAL_TEST_EXECUTABLES := $(TEST_SOURCES:tests/%.cpp=bin/tests/%)
ifeq ($(OS),Windows_NT)
	ALL_COMPILED_EXECUTABLES_IN_BIN := $(shell find bin/**/* -perm /111 -type f)
else
	ALL_COMPILED_EXECUTABLES_IN_BIN := $(shell find bin/**/* -perm +111 -type f)
endif
OBJECTS_RESPONSE_FILE=tmp/response_file_for_build-object_files.lst




## Counts
NUMBER_OF_QUINTESSENCE_SOURCES := $(words $(QUINTESSENCE_SOURCES))
NUMBER_OF_SOURCES := $(words $(SOURCES))
NUMBER_OF_PROGRAM_SOURCES := $(words $(PROGRAM_SOURCES))





ALLEGRO_LIBS_LINK_ARGS := $(ALLEGRO_LIBS:%=-l%)
ALLEGRO_LIBS_LINK_MAIN_ARGS := $(ALLEGRO_LIBS_MAIN:%=-l%)
ifeq ($(OS),Windows_NT)
	REQUIRED_WINDOWS_NETWORK_FLAGS=-lwsock32 -lws2_32
endif



TERMINAL_COLOR_YELLOW=\033[1;33m
TERMINAL_COLOR_RED=\033[1;31m
TERMINAL_COLOR_GREEN=\033[1;32m
TERMINAL_COLOR_BLUE=\033[1;34m
TERMINAL_COLOR_LIGHT_BLUE=\033[1;94m
TERMINAL_COLOR_RESET=\033[0m


BUILD_FILE_PATH_ROOT=/Users/markoates/Repos/hexagon/bin/programs/data/builds/dumps
BUILD_FILE_QUINTESSENCE_EXTRAPOLATION=$(BUILD_FILE_PATH_ROOT)/quintessence_build.txt
BUILD_FILE_DEPS_BUILD=$(BUILD_FILE_PATH_ROOT)/deps_build.txt
BUILD_FILE_COMPONENT_OBJECT_BUILD=$(BUILD_FILE_PATH_ROOT)/component_object_build.txt
# NOTE: this PROGRAMS_BUILD is currently not captured in daemus
# TODO: include BUILD_FILE_PROGRAMS_BUILD file in deamus
BUILD_FILE_PROGRAMS_BUILD=$(BUILD_FILE_PATH_ROOT)/programs_build.txt
BUILD_FILE_COMPONENT_TEST_OBJECT_BUILD=$(BUILD_FILE_PATH_ROOT)/component_test_object_build.txt
BUILD_FILE_COMPONENT_TEST_EXECUTABLE_BUILD=$(BUILD_FILE_PATH_ROOT)/component_test_executable.txt
BUILD_FILE_COMPONENT_TESTS_RUN=$(BUILD_FILE_PATH_ROOT)/component_test_run.txt


define output_terminal_message
	$(eval compteur=$(shell echo $$(($(compteur)+1))))
	$(eval columns=$(shell tput cols))
	@echo
	@${OUTPUT_BANNER_EXECUTABLE} -c yellow -l $(columns) -m Stage ${compteur}: ${1}
	@echo
endef


# Capture the number of cores on this system
ifeq ($(OS), Windows_NT)
  CORES := $(shell expr $(shell nproc --all) - 1)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CORES = 4
	else ifeq ($(UNAME_S),Darwin)
    CORES := $(shell echo $$((`sysctl -n hw.ncpu` - 1)))
	else
		CORES = 4
	endif
endif
$(info Using $(CORES) cores for parallel jobs)


.PHONY: main quintessence programs objects examples demos library tests docs run_tests deps



main:
	$(call output_terminal_message,"Compose componets from all quintessence files")
	@make quintessences -j$(CORES)
	$(call output_terminal_message,"Make all the dependency files")
	@make deps -j$(CORES)
	$(call output_terminal_message,"Make all the component object files")
	@make objects -j$(CORES)
	$(call output_terminal_message,"Make all the test object files")
	@make test_objects -j$(CORES)
	$(call output_terminal_message,"Build the library-for-tests")
	@make library_for_tests -j$(CORES)
	$(call output_terminal_message,"Make all the individual test executables")
	@make tests -j$(CORES)
	$(call output_terminal_message,"Make single test executable containing all tests")
	@make all_tests -j$(CORES)
	$(call output_terminal_message,"Run the tests for all the components")
	@(bin/run_all_tests && (make celebrate_passing_tests) || (make signal_failing_tests && exit 1) )
	$(call output_terminal_message,"Build the library")
	@make library -j$(CORES)
	$(call output_terminal_message,"Make all the programs")
	@make programs -j$(CORES)
	$(call output_terminal_message,"Make all the example programs")
	@make examples -j$(CORES)
	$(call output_terminal_message,"Make all the demo programs")
	@make demos -j$(CORES)
	$(call output_terminal_message,"Update the documentation")
	@make docs
	$(call output_terminal_message,"Celebrate successful build")
	@make celebrate_everything_built



check_for_debug_markers:  # This is an example of how to check for debug markers using fancy_debug
	$(eval DEBUG_MARKER_PREFIX_COMMAND=$(shell /Users/markoates/Repos/blast/bin/programs/fancy_debug command_or_empty))
	@if [ "$(DEBUG_MARKER_PREFIX_COMMAND)" = "" ]; then \
			echo "(No debugging symbols found)"; \
	else \
			echo "Debugging symbols have been found"; \
	fi



## note: For this process, there are several build stages.  Some stages have their outputs dumpted to a
## file located under $(BUILD_FILE_PATH_ROOT).  Both the stdout and stderr are captured using "some_command_here 2>&1 | tee file_to_dump"
## For how output piping is used, see reference https://askubuntu.com/questions/420981/how-do-i-save-terminal-output-to-a-file
## Also, to capture the exit status of the build stage (and not the "tee" process), "pipefail" is used, see this stack overflow:
## https://stackoverflow.com/questions/6871859/piping-command-output-to-tee-but-also-save-exit-code-of-command
## Also, see also "$pipestatus" for a more ellaborate way to capture the exit status of each step in the pipe

focus:
	$(call output_terminal_message,"Announce focus build info")
	@echo "                    Project: $(PROJECT_BASE_DIRECTORY)"
	@echo "Focusing build on component: \033[48;5;27m$(FOCUSED_COMPONENT_NAME)$(TERMINAL_COLOR_RESET)"
	@echo "          testing filter in: \033[48;5;27m$(FOCUSED_TEST_FILTER)$(TERMINAL_COLOR_RESET)"
	$(call output_terminal_message,"Signal to Hexagon build has started and clear builds/dumps/ files")
	@echo "started" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@-rm $(BUILD_FILE_QUINTESSENCE_EXTRAPOLATION)
	@-rm $(BUILD_FILE_COMPONENT_OBJECT_BUILD)
	@-rm $(BUILD_FILE_PROGRAMS_BUILD)
	@-rm $(BUILD_FILE_COMPONENT_TEST_OBJECT_BUILD)
	@-rm $(BUILD_FILE_COMPONENT_TEST_EXECUTABLE_BUILD)
	@-rm $(BUILD_FILE_COMPONENT_TESTS_RUN)
	$(call output_terminal_message,"Compose componets from all quintessence files")
	@echo "generating_sources_files_from_quintessence" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@set -o pipefail && (make quintessences -j$(CORES) 2>&1 | tee $(BUILD_FILE_QUINTESSENCE_EXTRAPOLATION))
	$(call output_terminal_message,"Build dependency file for component")
	@echo "building_dependency_file_for_component" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@set -o pipefail && (make deps -j$(CORES) 2>&1 | tee $(BUILD_FILE_DEPS_BUILD))
	$(call output_terminal_message,"Make all the component object files")
	@echo "building_component_object_files" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@set -o pipefail && (make objects 2>&1 | tee $(BUILD_FILE_COMPONENT_OBJECT_BUILD))
	$(call output_terminal_message,"Make the library-for-tests")
	@echo "make_library_for_tests" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@make library_for_tests -j$(CORES)
	$(call output_terminal_message, "Delete the existing focused component test object and test binary")
	@echo "delete_focused_component_test_object_file_and_test_executable" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@-rm obj/tests/$(FOCUSED_COMPONENT_NAME)Test.o
	@-rm bin/tests/$(FOCUSED_COMPONENT_NAME)Test
	$(call output_terminal_message,"Make the focused component test")
	@echo "build_focused_component_test_object_file" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@set -o pipefail && (make obj/tests/$(FOCUSED_COMPONENT_NAME)Test.o 2>&1 | tee $(BUILD_FILE_COMPONENT_TEST_OBJECT_BUILD))
	@echo "build_focused_component_test_executable" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@set -o pipefail && (make bin/tests/$(FOCUSED_COMPONENT_NAME)Test 2>&1 | tee $(BUILD_FILE_COMPONENT_TEST_EXECUTABLE_BUILD))
	$(call output_terminal_message,"Check for DEBUG markers in source files")
	@echo "run_test_for_focused_component" > $(BUILD_STATUS_SIGNALING_FILENAME)
	$(eval DEBUG_MARKER_PREFIX_COMMAND=$(shell (cd $(PROJECT_BASE_DIRECTORY) && /Users/markoates/Repos/blast/bin/programs/fancy_debug command_or_empty)))
	@if [ "$(DEBUG_MARKER_PREFIX_COMMAND)" = "" ]; then \
			echo "(No debugging symbols found)"; \
	else \
			echo "Debugging symbols have been found; TODO: Continue running test with debugger."; \
			make celebrate_debug_symbol_found; \
			echo "Use \"/Users/markoates/Repos/blast/bin/programs/fancy_debug command_or_empty\" to output the command."; \
	fi
	$(call output_terminal_message,"Run the focused component test")
	@echo "run_test_for_focused_component" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@if [ "$(DEBUG_MARKER_PREFIX_COMMAND)" = "" ]; then \
		((set -o pipefail && (./bin/tests/$(FOCUSED_COMPONENT_NAME)Test --gtest_filter=*$(FOCUSED_TEST_FILTER)* 2>&1 | tee $(BUILD_FILE_COMPONENT_TESTS_RUN))) && (make celebrate_passing_tests) || (make signal_failing_tests && exit 1) ) \
	else \
		echo "Use the debugger"; \
		exit 1; \
	fi
	$(call output_terminal_message,"Make the library")
	@echo "make_library" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@make library -j$(CORES)
	$(call output_terminal_message,"Make all the programs")
	@echo "make_all_programs" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@set -o pipefail && (make programs -j$(CORES) 2>&1 | tee $(BUILD_FILE_PROGRAMS_BUILD))
	$(call output_terminal_message,"Update the documentation")
	@echo "make_documentation" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@make docs
	$(call output_terminal_message,"Celebrate integrated component tests")
	@echo "signal_component_built_and_integrated" > $(BUILD_STATUS_SIGNALING_FILENAME)
	@make celebrate_built_component
	$(call output_terminal_message,"Run any post-build process if present in the ProjectMakefile")
	$(POST_FOCUS_BUILD_COMMAND)
	$(call output_terminal_message,"Signal to Hexagon that build has completed")
	@echo "completed" > $(BUILD_STATUS_SIGNALING_FILENAME)



version:
	@git log --format="%H" -n 1
	@git log -1 --pretty=format:%h
	@git log -1 --format=%cd



fast:
	make clean
	make quintessences -j$(CORES)
	make objects -j$(CORES)
	make library



quintessences: $(QUINTESSENCE_SOURCES)
	@[ -f $(QUINTESSENCE_BUILDER_EXECUTABLE) ] || echo "The needed executable $(QUINTESSENCE_BUILDER_EXECUTABLE) was not found"
	@find quintessence -name '*.q.yml' | xargs $(QUINTESSENCE_BUILDER_EXECUTABLE) --less_verbose -f
	@echo "(finished)"



$(OBJECTS_RESPONSE_FILE): $(OBJECTS)
	@echo $(OBJECTS) > $(OBJECTS_RESPONSE_FILE)


programs: $(PROGRAMS)



objects: $(OBJECTS)



examples: $(EXAMPLES)



demos: $(DEMOS)



library_for_tests: $(LIBRARY_FOR_TESTS_NAME)



library: $(LIBRARY_NAME)



test_objects: $(TEST_OBJECTS)



tests: $(INDIVIDUAL_TEST_EXECUTABLES)



all_tests: $(TEST_OBJECTS) bin/run_all_tests



deps: $(DEPS)



docs:
ifeq ($(OS),Windows_NT)
	@echo "Skipping doc build because we're on Windows."
else
	@mkdir -p ./docs
	@ruby /Users/markoates/Repos/blast/scripts/build_documentation.rb
endif


debug:
	python3 /Users/markoates/Repos/blast/scripts/run_debug.py $(EXECUTABLE_TO_RUN)



source_release:
	$(SOURCE_RELEASER_EXECUTABLE) $(current_dir)



win64_release:
	# Note: these parameters are expected to be passed during execution time
	# $(WIN64_RELEASER_EXECUTABLE) $(EXPECTED_RELEASE_FOLDER_NAME) $(RELEASE_VERSION_NUMBER) $(RELEASE_FOLDER_NAME)
	@echo "NOTICE: This build proceedure has changed. Please see blast repos's scripts/build_win64_release.sh."



macos_release:
	# Note: these parameters are expected to be passed during execution time
	$(MACOS_RELEASER_EXECUTABLE) $(RELEASE_PROJECT_NAME) $(RELEASE_VERSION_NUMBER) $(RELEASE_FOLDER_NAME)



define output_pass_banner
	$(eval columns=$(shell tput cols))
	@echo
	@${OUTPUT_BANNER_EXECUTABLE} -c green -l $(columns) --pass
	@echo
endef

define output_fail_banner
	$(eval columns=$(shell tput cols))
	@echo
	@${OUTPUT_BANNER_EXECUTABLE} -c green -l $(columns) --fail
	@echo
endef

define output_component_built_banner
	$(eval columns=$(shell tput cols))
	@echo
	@${OUTPUT_BANNER_EXECUTABLE} -c green -l $(columns) --component_built
	@echo
endef

define output_debug_banner
	$(eval columns=$(shell tput cols))
	@echo
	@${OUTPUT_BANNER_EXECUTABLE} -c green -l $(columns) --debug
	@echo
endef

define output_built_banner
	$(eval columns=$(shell tput cols))
	@echo
	@${OUTPUT_BANNER_EXECUTABLE} -c green -l $(columns) --built
	@echo
endef



celebrate_debug_symbol_found:
	$(call output_debug_banner)


celebrate_passing_tests:
	$(call output_pass_banner)


celebrate_passing_tests_legacy:
	$(eval columns=$(shell tput cols))
	$(eval banner_width=103)
	$(eval hcolumns=$(shell expr $(columns) / 2 - $(banner_width) / 2))
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "$(TERMINAL_COLOR_GREEN)▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒$(TERMINAL_COLOR_RESET)"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "$(TERMINAL_COLOR_GREEN)▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒     █▀▀▀▀▄  █▀▀▀▀█  █▀▀▀▀▀  █▀▀▀▀▀    ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒$(TERMINAL_COLOR_RESET)"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "$(TERMINAL_COLOR_GREEN)▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒     █▄▄▄▄▀  █▄▄▄▄█  ▀▀▀▀▀█  ▀▀▀▀▀█    ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒$(TERMINAL_COLOR_RESET)"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "$(TERMINAL_COLOR_GREEN)▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒     ▀       ▀    ▀  ▀▀▀▀▀▀  ▀▀▀▀▀▀    ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒$(TERMINAL_COLOR_RESET)"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "$(TERMINAL_COLOR_GREEN)▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒$(TERMINAL_COLOR_RESET)"



signal_failing_tests:
	$(call output_fail_banner)



signal_failing_tests_legacy:
	$(eval columns=$(shell tput cols))
	$(eval banner_width=103)
	$(eval hcolumns=$(shell expr $(columns) / 2 - $(banner_width) / 2))
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[31m🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[31m🀫 🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫 🀫\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[31m🀫 🀫 🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫    FAIL   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫 🀫 🀫\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[31m🀫 🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫   🀫 🀫\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[31m🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"



celebrate_built_component:
	$(call output_component_built_banner)



celebrate_built_component_legacy:
	$(eval columns=$(shell tput cols))
	$(eval banner_width=105)
	$(eval hcolumns=$(shell expr $(columns) / 2 - $(banner_width) / 2))
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m$(TERMINAL_COLOR_BLUE)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m$(TERMINAL_COLOR_BLUE)🀫$(TERMINAL_COLOR_GREEN) 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_BLUE)🀫\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_BLUE)🀫$(TERMINAL_COLOR_GREEN) 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫  $(TERMINAL_COLOR_BLUE)   COMPONENT BUILT     $(TERMINAL_COLOR_GREEN)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_BLUE)🀫\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_BLUE)🀫$(TERMINAL_COLOR_GREEN) 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_BLUE)🀫\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m$(TERMINAL_COLOR_BLUE)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫\033[0m"



celebrate_everything_built:
	$(call output_built_banner)



celebrate_everything_built_legacy:
	$(eval columns=$(shell tput cols))
	$(eval banner_width=105)
	$(eval hcolumns=$(shell expr $(columns) / 2 - $(banner_width) / 2))
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_GREEN)████$(TERMINAL_COLOR_YELLOW)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_GREEN)████$(TERMINAL_COLOR_RESET)\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_GREEN)██$(TERMINAL_COLOR_GREEN)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_GREEN)██$(TERMINAL_COLOR_RESET)\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_YELLOW)🀫$(TERMINAL_COLOR_GREEN) 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫        BUILT      🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_YELLOW)🀫$(TERMINAL_COLOR_RESET)\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_GREEN)██$(TERMINAL_COLOR_GREEN)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_GREEN)██$(TERMINAL_COLOR_RESET)\033[0m"
	@printf ' %.0s' {1..$(hcolumns)}
	@echo "\033[1m\033[32m$(TERMINAL_COLOR_GREEN)████$(TERMINAL_COLOR_YELLOW)🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 🀫 $(TERMINAL_COLOR_GREEN)████$(TERMINAL_COLOR_RESET)\033[0m"



.deps/%.d: src/%.cpp
	@mkdir -p $(@D)
	@printf "Compiling dependency \e[1m\e[36m$@\033[0m\n"
	@g++ -std=c++17 -MM $< > $@ -I./include -I$(ASIO_INCLUDE_DIR) -I$(ALLEGRO_INCLUDE_DIR) -I$(ALLEGRO_PLATFORM_INCLUDE_DIR) $(ALLEGRO_FLARE_BUILD_ARGS) $(BULLET_PHYSICS_BUILD_ARGS) $(CURL_BUILD_ARGS) -I$(YAML_CPP_INCLUDE_DIR)
	@printf "Dependency at \033[1m\033[32m$@\033[0m created successfully.\n"



#### objects



obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	@printf "Compiling object file \e[1m\e[34m$@\033[0m\n"
	@g++ -g -c $(ERROR_LIMIT_FLAG) -std=c++17 $(DISABLE_UNUSED_LINK_ARGUMENTS_WARNING_FLAG) $(WARNINGS_PROMOTED_TO_ERRORS_FLAGS) -Wall $(DISABLE_UNUSED_WARNINGS_FLAG) $< -o $@ -I./include -I$(ASIO_INCLUDE_DIR) -I$(ALLEGRO_INCLUDE_DIR) -I$(BULLET_PHYSICS_INCLUDE_DIR) -I$(ALLEGRO_PLATFORM_INCLUDE_DIR) -I$(YAML_CPP_INCLUDE_DIR) -D_XOPEN_SOURCE_EXTENDED -I$(ALLEGRO_FLARE_INCLUDE_DIR) $(NCURSES_BUILD_ARGS)
	@printf "Object file at \033[1m\033[32m$@\033[0m compiled successfully.\n"


obj/tests/%.o: tests/%.cpp
	@mkdir -p $(@D)
	@printf "Compiling test object file \e[1m\e[36m$@\033[0m\n"
	@g++ -g -c -std=c++17 $(DISABLE_UNUSED_LINK_ARGUMENTS_WARNING_FLAG) $(WARNINGS_PROMOTED_TO_ERRORS_FLAGS) -Wall -Wuninitialized $(DISABLE_UNUSED_WARNINGS_FLAG) $< -o $@ -I./include -I$(ALLEGRO_INCLUDE_DIR) -I$(BULLET_PHYSICS_INCLUDE_DIR) -I$(ALLEGRO_PLATFORM_INCLUDE_DIR) -I$(ASIO_INCLUDE_DIR) -I$(GOOGLE_TEST_INCLUDE_DIR) -I$(GOOGLE_MOCK_INCLUDE_DIR) -I$(YAML_CPP_INCLUDE_DIR) $(ALLEGRO_FLARE_BUILD_ARGS) $(CURL_BUILD_ARGS) $(NCURSES_BUILD_ARGS)
	@printf "Test object file at \033[1m\033[32m$@\033[0m compiled successfully.\n"



obj/tests/$(TEST_RUNNER_PROGRAM_NAME).o: tests/$(TEST_RUNNER_PROGRAM_NAME).cpp
	@mkdir -p $(@D)
	@printf "Compiling test object for $(TEST_RUNNER_PROGRAM_NAME) \e[1m\e[36m$@\033[0m\n"
	@g++ -g -c -std=c++17 $(DISABLE_UNUSED_LINK_ARGUMENTS_WARNING_FLAG) $(WARNINGS_PROMOTED_TO_ERRORS_FLAGS) -Wall -Wuninitialized $(DISABLE_UNUSED_WARNINGS_FLAG) $< -o $@ -I$(ALLEGRO_INCLUDE_DIR) -I$(BULLET_PHYSICS_INCLUDE_DIR) -I$(ALLEGRO_PLATFORM_INCLUDE_DIR) -I$(GOOGLE_TEST_INCLUDE_DIR) -I$(GOOGLE_MOCK_INCLUDE_DIR) $(NCURSES_BUILD_ARGS)
	@printf "Object for $(TEST_RUNNER_PROGRAM_NAME) at \033[1m\033[32m$@\033[0m compiled successfully.\n"



#### libraries



$(LIBRARY_FOR_TESTS_NAME): $(OBJECTS) $(OBJECTS_RESPONSE_FILE) # NOTE: This response file here is not necessary on macos
	@printf "Compiling library-for-tests \e[1m\e[36m$@\033[0m\n"
ifeq ($(OBJECTS),)
	@printf "\033[1m\033[32mnothing to be done, there are no objects to build into a library-for-tests\033[0m."
else
ifeq ($(OS),Windows_NT)
	@ar rs $(LIBRARY_FOR_TESTS_NAME) @$(OBJECTS_RESPONSE_FILE)
else
	@ar rs $(LIBRARY_FOR_TESTS_NAME) $(OBJECTS)
endif
	@printf "done. Library-for-tests file at \033[1m\033[32m$@\033[0m\n"
endif



$(LIBRARY_NAME): $(OBJECTS) $(OBJECTS_RESPONSE_FILE)
	@printf "Compiling library \e[1m\e[36m$@\033[0m\n"
ifeq ($(OBJECTS),)
	@printf "\033[1m\033[32mnothing to be done, there are no objects to build into a library\033[0m."
else
ifeq ($(OS),Windows_NT)
	@ar rs $(LIBRARY_NAME) @$(OBJECTS_RESPONSE_FILE)
else
	@ar rs $(LIBRARY_NAME) $(OBJECTS)
endif
	@printf "done. Library file at \033[1m\033[32m$@\033[0m\n"
endif



### executables



BIGLINE=g++ -g -std=c++17 $(ERROR_LIMIT_FLAG) $(DISABLE_UNUSED_LINK_ARGUMENTS_WARNING_FLAG) -Wall $(WARNINGS_PROMOTED_TO_ERRORS_FLAGS) $(DISABLE_UNUSED_WARNINGS_FLAG) $< -o $@ $(NCURSES_BUILD_ARGS) -I./include -I$(ASIO_INCLUDE_DIR) -I$(ALLEGRO_INCLUDE_DIR) -I$(ALLEGRO_PLATFORM_INCLUDE_DIR) -I$(YAML_CPP_INCLUDE_DIR) $(REQUIRED_WINDOWS_NETWORK_FLAGS) $(ALLEGRO_FLARE_BUILD_ARGS) -L$(LIBRARY_DIR) -l$(LIBRARY_FOR_LINKING_NAME) $(ALLEGRO_FLARE_LINK_ARGS) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_LIBS_LINK_MAIN_ARGS) $(BULLET_PHYSICS_BUILD_ARGS) $(BULLET_PHYSICS_LINK_ARGS) $(CURL_BUILD_ARGS) $(CURL_LINK_ARGS) $(SQLITE_LINK_ARGS) -D_XOPEN_SOURCE_EXTENDED $(OPENGL_LIB) $(MIDI_AUDIO_LIB) -l$(GOOGLE_MOCK_LIBS) -l$(GOOGLE_TEST_LIBS) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) $(RPATH_STATEMENT) $(NCURSES_LINK_ARGS)


bin/tests/%: obj/tests/%.o obj/tests/$(TEST_RUNNER_PROGRAM_NAME).o
	@mkdir -p $(@D)
	@printf "Compiling standalone test executable at \e[1m\e[36m$@\033[0m\n"
	@g++ -g -std=c++17 $(ERROR_LIMIT_FLAG) $(DISABLE_UNUSED_LINK_ARGUMENTS_WARNING_FLAG) -Wall $(WARNINGS_PROMOTED_TO_ERRORS_FLAGS) $(DISABLE_UNUSED_WARNINGS_FLAG) $^ -o $@ -L./lib -l$(LIBRARY_FOR_TESTS_FOR_LINKING_NAME) $(NCURSES_BUILD_ARGS) -I./include -I$(ASIO_INCLUDE_DIR) -I$(ALLEGRO_INCLUDE_DIR) -I$(ALLEGRO_PLATFORM_INCLUDE_DIR) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_FLARE_BUILD_ARGS) $(ALLEGRO_FLARE_LINK_ARGS) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) $(ALLEGRO_LIBS_LINK_MAIN_ARGS) $(BULLET_PHYSICS_BUILD_ARGS) $(BULLET_PHYSICS_LINK_ARGS) $(CURL_BUILD_ARGS) $(CURL_LINK_ARGS) $(SQLITE_LINK_ARGS) -D_XOPEN_SOURCE_EXTENDED $(OPENGL_LIB) $(MIDI_AUDIO_LIB) $(REQUIRED_WINDOWS_NETWORK_FLAGS) -l$(GOOGLE_MOCK_LIBS) -l$(GOOGLE_TEST_LIBS) $(RPATH_STATEMENT) $(NCURSES_LINK_ARGS) 
	@printf "Standalone executable at \033[1m\033[32m$@\033[0m compiled successfully.\n"



bin/run_all_tests: $(TEST_OBJECTS) obj/tests/$(TEST_RUNNER_PROGRAM_NAME).o
	@mkdir -p $(@D)
	@printf "Compiling run_all_tests executable \e[1m\e[36m$@\033[0m\n"
	@echo "$^" > tmp/objects_for_run_all_tests.rsp
	g++ -g -std=c++17 $(ERROR_LIMIT_FLAG) $(DISABLE_UNUSED_LINK_ARGUMENTS_WARNING_FLAG) -Wall $(WARNINGS_PROMOTED_TO_ERRORS_FLAGS) $(DISABLE_UNUSED_WARNINGS_FLAG) @tmp/objects_for_run_all_tests.rsp -o $@ -L./lib -l$(LIBRARY_FOR_TESTS_FOR_LINKING_NAME) $(NCURSES_BUILD_ARGS) -I./include -I$(ASIO_INCLUDE_DIR) -I$(YAML_CPP_INCLUDE_DIR) -L$(YAML_CPP_LIB_DIR) -l$(YAML_CPP_LIBS) $(REQUIRED_WINDOWS_NETWORK_FLAGS) -L$(ALLEGRO_LIB_DIR) $(ALLEGRO_FLARE_BUILD_ARGS) $(ALLEGRO_FLARE_LINK_ARGS) $(BULLET_PHYSICS_BUILD_ARGS) $(BULLET_PHYSICS_LINK_ARGS) $(CURL_BUILD_ARGS) $(CURL_LINK_ARGS) $(SQLITE_LINK_ARGS) -l$(GOOGLE_MOCK_LIBS) -l$(GOOGLE_TEST_LIBS) -I$(ALLEGRO_INCLUDE_DIR) -I$(ALLEGRO_PLATFORM_INCLUDE_DIR) $(ALLEGRO_LIBS_LINK_MAIN_ARGS) -D_XOPEN_SOURCE_EXTENDED $(OPENGL_LIB) $(MIDI_AUDIO_LIB) $(RPATH_STATEMENT) $(NCURSES_LINK_ARGS) 
	@printf "run_all_tests executable at \e[1m\e[36m$@\033[0m compiled successfully.\n"



bin/programs/%: programs/%.cpp $(LIBRARY_NAME)
	@mkdir -p $(@D)
	@printf "Compiling program executable \e[1m\e[36m$@\033[0m\n"
	$(BIGLINE)
	@printf "Program executable at \033[1m\033[32m$@\033[0m compiled successfully.\n"



bin/examples/%: examples/%.cpp $(LIBRARY_NAME)
	@mkdir -p $(@D)
	@printf "Compiling example executable \e[1m\e[36m$@\033[0m\n"
	$(BIGLINE)
	@printf "Example executable at \033[1m\033[32m$@\033[0m compiled successfully.\n"



bin/demos/%: demos/%.cpp $(LIBRARY_NAME)
	@mkdir -p $(@D)
	@printf "Compiling demo executable at \e[1m\e[36m$@\033[0m\n"
	$(BIGLINE)
	@printf "Demo executable at \033[1m\033[32m$@\033[0m compiled successfully.\n"





list_quintessence_sources:
	@for item in $(QUINTESSENCE_SOURCES) ; do \
	   printf $$item ; \
  done



list_sources:
	@for item in $(SOURCES) ; do \
	   echo $$item ; \
  done


list_objects:
	@for item in $(OBJECTS) ; do \
	   echo $$item ; \
  done


list_test_objects:
	@for item in $(TEST_OBJECTS) ; do \
	   echo $$item ; \
  done


list_program_sources:
	@for item in $(PROGRAM_SOURCES) ; do \
	   echo $$item ; \
  done


list_test_executables:
	@for item in $(INDIVIDUAL_TEST_EXECUTABLES) ; do \
	   echo $$item ; \
	done



entire:
	# make clean && mkdir -p tmp && make 2>&1 | tee "tmp/$(PROJECT_LIB_NAME)-make_output-$\(date +'%I_%M_%p_%b_%d').log"
	make clean && mkdir -p tmp && make 2>&1 | tee "tmp/$(PROJECT_LIB_NAME)-make_output-$(date +'%I_%M_%p_%b_%d').log"

universe:
	# make blast
	(cd /Users/markoates/Repos/blast && git pull && make clean && make programs -j$(CORES) && make)
	# make allegro_flare
	(cd /Users/markoates/Repos/allegro_flare && git pull && make clean && make)
	# make hexagon
	(cd /Users/markoates/Repos/hexagon && git pull && make clean && make)



clean:
	-rm -rdf obj/
	-rm $(PROGRAMS)
	-rm $(EXAMPLES)
	-rm $(TEST_OBJECTS)
	-rm $(INDIVIDUAL_TEST_EXECUTABLES)
	-rm bin/run_all_tests
	-rm $(DEMOS)
	-rm $(ALL_COMPILED_EXECUTABLES_IN_BIN)
	-rm $(DEPS)
	-rm $(OBJECTS_RESPONSE_FILE)
	-rm $(LIBRARY_FOR_TESTS_NAME)
	-rm $(LIBRARY_NAME)


newlib:
	-rm lib/liballegro_flare-0.8.11wip.a
	make library


fresh:
	make clean
	make -j$(CORES)
	make bin/run_all_tests
