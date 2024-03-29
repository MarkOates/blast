#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile


#include <iostream>
#include <sstream>
#include <algorithm> // for std::count
#include <Blast/TemplatedFile.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/StringJoiner.hpp>


std::vector<std::string> args;

#include <string>
std::string repeat(std::string s, int n)
{
   std::string s1 = s;
   for (int i=1; i<n;i++) s += s1;
   return s;
}

std::string directory_to(std::string component_name)
{
   const char COMPONENT_FRAGMENT_DELIMITER = '/';
   std::string directory_delimiter = "/";

   std::string::size_type pos = component_name.find_first_of(COMPONENT_FRAGMENT_DELIMITER);
   if (pos == std::string::npos) return ".";

   std::vector<std::string> component_name_fragments = Blast::StringSplitter(component_name, COMPONENT_FRAGMENT_DELIMITER).split();
   if (component_name_fragments.empty())
   {
      std::string error_message = "Unexpected path to this error.  The Delimiter '/' has resulted in " \
                                  "no tokens, though at least 2 are expected.";
      throw std::runtime_error(error_message);
   }

   component_name_fragments.pop_back();

   std::string result = Blast::StringJoiner(component_name_fragments, directory_delimiter).join();

   return result;
}

int main(int argc, char **argv)
{
   for (int i=0; i<argc; i++) args.push_back(argv[i]);
   if (args.size() != 3) throw std::runtime_error("You must pass a target project name, followed by a component name.");

   std::stringstream COMMAND_TEMPLATE;
   COMMAND_TEMPLATE << "TARGET_PROJECT=[[TARGET_PROJECT]]; COMPONENT=[[COMPONENT]]; "
                    << "mkdir -p [[TARGET_PROJECT_FOLDER_NAME]]/quintessence/[[DIRECTORY_TO_COMPONENT]] && "
                    << "ln -s [[UP_DIRECTORY_PARENT_TOKENS]]${TARGET_PROJECT}/quintessence/${COMPONENT}.q.yml "
                    << "[[TARGET_PROJECT_FOLDER_NAME]]/quintessence/${COMPONENT}.q.yml; "
                    << "unset COMPONENT; unset TARGET_PROJECT";

   std::stringstream TEST_FILE_COMMAND_TEMPLATE;
   TEST_FILE_COMMAND_TEMPLATE << "TARGET_PROJECT=[[TARGET_PROJECT]]; COMPONENT=[[COMPONENT]]; "
                              << "mkdir -p [[TARGET_PROJECT_FOLDER_NAME]]/tests/[[DIRECTORY_TO_COMPONENT]] && "
                              << "ln -s [[UP_DIRECTORY_PARENT_TOKENS]]${TARGET_PROJECT}/tests/${COMPONENT}Test.cpp "
                              << "[[TARGET_PROJECT_FOLDER_NAME]]/tests/${COMPONENT}Test.cpp; "
                              << "unset COMPONENT; unset TARGET_PROJECT";

   std::stringstream SOURCE_HEADER_COMMAND_TEMPLATE;
   SOURCE_HEADER_COMMAND_TEMPLATE << "TARGET_PROJECT=[[TARGET_PROJECT]]; COMPONENT=[[COMPONENT]]; "
                                  << "mkdir -p [[TARGET_PROJECT_FOLDER_NAME]]/src/[[DIRECTORY_TO_COMPONENT]] && "
                                  << "ln -s [[UP_DIRECTORY_PARENT_TOKENS]]${TARGET_PROJECT}/src/${COMPONENT}.cpp "
                                  << "[[TARGET_PROJECT_FOLDER_NAME]]/src/${COMPONENT}.cpp; "
                                  << "mkdir -p [[TARGET_PROJECT_FOLDER_NAME]]/include/[[DIRECTORY_TO_COMPONENT]] && "
                                  << "ln -s [[UP_DIRECTORY_PARENT_TOKENS]]${TARGET_PROJECT}/include/${COMPONENT}.hpp "
                                  << "[[TARGET_PROJECT_FOLDER_NAME]]/include/${COMPONENT}.hpp; "
                                  << "unset COMPONENT; unset TARGET_PROJECT";

   std::string source_project_raw_folder_name = args[1]; //"blast";
   std::string component_name = args[2]; //"Blast/ShellCommandExecutorWithCallback";
   std::string target_project_raw_folder_name = ".";
   std::string directory_to_component = directory_to(component_name);

   int component_directory_depth = (int)std::count(component_name.begin(), component_name.end(), '/') + 2;
   std::string up_directory_parent_tokens = repeat("../", component_directory_depth);

   Blast::TemplatedFile templated_file(COMMAND_TEMPLATE.str(), {
      { "[[TARGET_PROJECT]]",             source_project_raw_folder_name },
      { "[[COMPONENT]]",                  component_name },
      { "[[DIRECTORY_TO_COMPONENT]]",     directory_to_component },
      { "[[TARGET_PROJECT_FOLDER_NAME]]", target_project_raw_folder_name },
      { "[[UP_DIRECTORY_PARENT_TOKENS]]", up_directory_parent_tokens },
   });

   Blast::TemplatedFile templated_test_command(TEST_FILE_COMMAND_TEMPLATE.str(), {
      { "[[TARGET_PROJECT]]",             source_project_raw_folder_name },
      { "[[COMPONENT]]",                  component_name },
      { "[[DIRECTORY_TO_COMPONENT]]",     directory_to_component },
      { "[[TARGET_PROJECT_FOLDER_NAME]]", target_project_raw_folder_name },
      { "[[UP_DIRECTORY_PARENT_TOKENS]]", up_directory_parent_tokens },
   });

   Blast::TemplatedFile templated_source_header_command(SOURCE_HEADER_COMMAND_TEMPLATE.str(), {
      { "[[TARGET_PROJECT]]",             source_project_raw_folder_name },
      { "[[COMPONENT]]",                  component_name },
      { "[[DIRECTORY_TO_COMPONENT]]",     directory_to_component },
      { "[[TARGET_PROJECT_FOLDER_NAME]]", target_project_raw_folder_name },
      { "[[UP_DIRECTORY_PARENT_TOKENS]]", up_directory_parent_tokens },
   });

   std::string result_command = templated_file.generate_content();
   std::string result_test_file_command = templated_test_command.generate_content();
   std::string result_source_header_file_command = templated_source_header_command.generate_content();

   std::cout << "Notice: This program does not actually perform the symlink command, but generates it (for now).  Here is that command:" << std::endl << std::endl;
   std::cout << "==== QUINTESSENCE FILE ====" << std::endl;
   std::cout << result_command << std::endl;
   std::cout << std::endl;
   std::cout << "==== TEST FILE ====" << std::endl;
   std::cout << result_test_file_command << std::endl;
   std::cout << std::endl;
   std::cout << "==== SOURCE AND HEADER FILE ====" << std::endl;
   std::cout << result_source_header_file_command << std::endl;
   std::cout << std::endl;
   std::cout << "==== SOURCE, HEADER, AND TEST FILE ====" << std::endl;
   std::cout << result_test_file_command << std::endl;
   std::cout << result_source_header_file_command << std::endl;
   std::cout << std::endl;
   std::cout << "==== SYMLINK ALL ====" << std::endl;
   std::cout << result_command << std::endl;
   std::cout << result_test_file_command << std::endl;
   std::cout << result_source_header_file_command << std::endl;
   std::cout << std::endl;

   return 0;
}


