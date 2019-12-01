#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>



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



std::string QUINTESSENCE_FOLDER_NAME = "quintessence";
std::string TEST_FOLDER_NAME = "tests";



std::string const QUINTESSENCE_FILE_CONTENT = R"END(functions:
  - name: run
    type: std::string
    body: return "Hello World!";
)END";



std::string TEST_FILE_CONTENT = R"END(
#include <gtest/gtest.h>

#include <[[COMPONENT_HEADER_INCLUDE_FILE_PATH]]>

TEST([[COMPONENT_TEST_DESCRIPTION_NAME]], run__returns_the_expected_response)
{
   [[COMPONENT_CLASS_NAME]] program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
)END";



static void ___replace(std::string& str, std::string from, std::string to)
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


std::string generate_make_folder_command(std::string dir)
{
   std::stringstream command;
   command << "mkdir \"" << dir << "\"";
   return command.str();
}



#include <Blast/DirectoryCreator.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/Quintessence/ComponentGenerator.hpp>



bool create_directory(std::string dir)
{
   std::vector<std::string> directory_components = Blast::StringSplitter(dir, '/').split();
   Blast::DirectoryCreator directory_creator(directory_components);
   return directory_creator.create();
}



int main(int argc, char **argv)
{
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   if (args.size() <= 1) throw std::runtime_error("You must pass a component name.  This component name should include its nested folders like \"Foobar/Bar/Bazz\" where \"Foobar/Bar\" are the folders and \"Bazz\" is the name of the component.");

   ComponentGenerator generator(argv[1]);
   ConsoleOutputter console_output;

   // make the quintessence file

   std::cout << "Making sure necessary folders are present...";
   create_directory(generator.get_quintessence_foldername());
   create_directory(generator.get_test_foldername());
   std::cout << "...component folders created.";

   std::cout << "Generating component files..." << std::endl;
   std::ofstream outfile4(generator.get_quintessence_filename());
   std::ofstream outfile7(generator.get_test_filename());

   std::map<std::string, std::ofstream *> outfiles = {
      { generator.get_quintessence_filename(), &outfile4 },
      { generator.get_test_filename(), &outfile7 },
   };

   bool outfiles_can_be_opened = true;
   std::stringstream outfiles_that_cannot_be_opened;

   for (auto &outfile : outfiles)
      if (!outfile.second->is_open())
      {
         outfiles_can_be_opened = false;
         outfiles_that_cannot_be_opened << outfile.first << ", ";
         break;
      }

   if (!outfiles_can_be_opened)
   {
      std::stringstream error_message;
      error_message << "The following files could not be created: ";
      error_message << outfiles_that_cannot_be_opened.str();
      throw std::runtime_error(error_message.str());
   }

   outfile4 << QUINTESSENCE_FILE_CONTENT;
   outfile4.close();

   std::string COMPONENT_HEADER_INCLUDE_FILE_PATH = generator.get_header_filename();
   std::string COMPONENT_TEST_DESCRIPTION_NAME = generator.get_google_test_description_prefix();
   std::string COMPONENT_CLASS_NAME = generator.get_program_body_class_name();

   std::string test_file_content = TEST_FILE_CONTENT;
   ___replace(test_file_content, "[[COMPONENT_HEADER_INCLUDE_FILE_PATH]]", COMPONENT_HEADER_INCLUDE_FILE_PATH);
   ___replace(test_file_content, "[[COMPONENT_TEST_DESCRIPTION_NAME]]", COMPONENT_TEST_DESCRIPTION_NAME);
   ___replace(test_file_content, "[[COMPONENT_CLASS_NAME]]", COMPONENT_CLASS_NAME);
   outfile7 << test_file_content;
   outfile7.close();

   std::stringstream finish_message;
   finish_message << "✅ Component files generated:" << std::endl;
   finish_message << "* " << generator.get_quintessence_filename() << std::endl
                  << "* " << generator.get_test_filename() << std::endl
                  << "generated." << std::endl;

   console_output.output_line(finish_message.str());

   std::runtime_error("You must pass a project name");

   return 0;
}
