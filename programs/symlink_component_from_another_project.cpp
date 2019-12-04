#include <iostream>
#include <Blast/TemplatedFile.hpp>


std::vector<std::string> args;


int main(int argc, char **argv)
{
   for (int i=0; i<argc; i++) args.push_back(argv[i]);
   if (args.size() != 3) throw std::runtime_error("You must pass a target project name, follwed by a component name");

   const std::string COMMAND_TEMPLATE = "TARGET_PROJECT=[[TARGET_PROJECT]]; COMPONENT=[[COMPONENT]]; " \
                                        "ln -s /Users/markoates/Repos/${TARGET_PROJECT}/quintessence/${COMPONENT}.q.yml " \
                                        "[[TARGET_PROJECT_FOLDER_NAME]]/quintessence/${COMPONENT}.q.yml; " \
                                        "unset COMPONENT; unset TARGET_PROJECT";

   const std::string TEST_FILE_COMMAND_TEMPLATE = "TARGET_PROJECT=[[TARGET_PROJECT]]; COMPONENT=[[COMPONENT]]; " \
                                                  "ln -s /Users/markoates/Repos/${TARGET_PROJECT}/tests/${COMPONENT}Test.cpp " \
                                                  "[[TARGET_PROJECT_FOLDER_NAME]]/tests/${COMPONENT}Test.cpp; " \
                                                  "unset COMPONENT; unset TARGET_PROJECT";

   const std::string SOURCE_HEADER_COMMAND_TEMPLATE = "TARGET_PROJECT=[[TARGET_PROJECT]]; COMPONENT=[[COMPONENT]]; " \
                                                      "ln -s /Users/markoates/Repos/${TARGET_PROJECT}/src/${COMPONENT}.cpp " \
                                                      "[[TARGET_PROJECT_FOLDER_NAME]]/src/${COMPONENT}.cpp; " \
                                                      "ln -s /Users/markoates/Repos/${TARGET_PROJECT}/include/${COMPONENT}.hpp " \
                                                      "[[TARGET_PROJECT_FOLDER_NAME]]/include/${COMPONENT}.hpp; " \
                                                      "unset COMPONENT; unset TARGET_PROJECT";

   std::string source_project_raw_folder_name = args[1]; //"blast";
   std::string component_name = args[2]; //"Blast/ShellCommandExecutorWithCallback";
   std::string target_project_raw_folder_name = ".";

   Blast::TemplatedFile templated_file(COMMAND_TEMPLATE, {
      { "[[TARGET_PROJECT]]",             source_project_raw_folder_name },
      { "[[COMPONENT]]",                  component_name },
      { "[[TARGET_PROJECT_FOLDER_NAME]]", target_project_raw_folder_name },
   });

   Blast::TemplatedFile templated_test_command(TEST_FILE_COMMAND_TEMPLATE, {
      { "[[TARGET_PROJECT]]",             source_project_raw_folder_name },
      { "[[COMPONENT]]",                  component_name },
      { "[[TARGET_PROJECT_FOLDER_NAME]]", target_project_raw_folder_name },
   });

   Blast::TemplatedFile templated_source_header_command(SOURCE_HEADER_COMMAND_TEMPLATE, {
      { "[[TARGET_PROJECT]]",             source_project_raw_folder_name },
      { "[[COMPONENT]]",                  component_name },
      { "[[TARGET_PROJECT_FOLDER_NAME]]", target_project_raw_folder_name },
   });

   std::string result_command = templated_file.generate_content();
   std::string result_test_file_command = templated_test_command.generate_content();
   std::string result_source_header_file_command = templated_source_header_command.generate_content();

   std::cout << "Notice: This program does not actually perform the symlink command, but generates it (for now).  Here is that command:" << std::endl << std::endl;
   std::cout << result_command << std::endl;
   std::cout << result_test_file_command << std::endl;
   std::cout << result_source_header_file_command << std::endl;
}


