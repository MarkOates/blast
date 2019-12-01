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

   std::string source_project_raw_folder_name = args[1]; //"blast";
   std::string component_name = args[2]; //"Blast/ShellCommandExecutorWithCallback";
   std::string target_project_raw_folder_name = ".";

   Blast::TemplatedFile templated_file(COMMAND_TEMPLATE, {
      { "[[TARGET_PROJECT]]",             source_project_raw_folder_name },
      { "[[COMPONENT]]",                  component_name },
      { "[[TARGET_PROJECT_FOLDER_NAME]]", target_project_raw_folder_name },
   });

   std::string result_command = templated_file.generate_content();

   std::cout << "Notice: This program does not actually perform the symlink command, but generates it (for now).  Here is that command:" << std::endl << std::endl;
   std::cout << result_command << std::endl;
}


