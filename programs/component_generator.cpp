#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>



std::string QUINTESSENCE_FOLDER_NAME = "quintessence";
std::string TEST_FOLDER_NAME = "tests";



std::string const QUINTESSENCE_FILE_CONTENT = R"END(functions:
  - name: run
    type: std::string
    body: return "Hello World!";
)END";



std::string const STAGE_QUINTESSENCE_FILE_CONTENT = R"END(parent_classes:


  - class: 'StageInterface'
    scope: public
    init_with: "StageInterface::[[COMPONENT_AS_ALL_CAPS_CONSTANT]]"


properties:


  - name: a_default_empty_event
    static: true
    type: ALLEGRO_EVENT
    init_with: "{}"
    getter_ref: true


functions:


  - name: render
    virtual: true
    override: true
    body: |
      return;
    body_dependency_symbols: []


  - name: process_local_event
    virtual: true
    override: true
    parameters:
      - name: event_name
        type: std::string
        default_argument: '""'
      - name: action_data
        type: ActionData
        default_argument: "ActionData()"
    body: |
      return;


  - name: process_event
    virtual: true
    override: true
    parameters:
      - name: event
        type: ALLEGRO_EVENT&
        default_argument: "get_a_default_empty_event_ref()"
    body: |
      return;


dependencies:


  - symbol: StageInterface
    headers: [ Hexagon/StageInterface.hpp ]
  - symbol: ALLEGRO_EVENT
    headers: [ allegro5/allegro.h ]
  - symbol: ALLEGRO_EVENT&
    headers: [ allegro5/allegro.h ]
  - symbol: ActionData
    headers: [ Hexagon/ActionData.hpp ]

)END";



std::string STAGE_TEST_FILE_CONTENT = R"END(
#include <gtest/gtest.h>

#include <[[COMPONENT_HEADER_INCLUDE_FILE_PATH]]>

TEST([[COMPONENT_TEST_DESCRIPTION_NAME]], can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
}

TEST([[COMPONENT_TEST_DESCRIPTION_NAME]], render__does_not_blow_up)
{
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
   [[COMPONENT_BASENAME_SNAKE_CASE]].render();
   SUCCEED();
}

TEST([[COMPONENT_TEST_DESCRIPTION_NAME]], process_local_event__does_not_blow_up)
{
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
   [[COMPONENT_BASENAME_SNAKE_CASE]].process_local_event();
   SUCCEED();
}

TEST([[COMPONENT_TEST_DESCRIPTION_NAME]], process_event__does_not_blow_up)
{
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
   [[COMPONENT_BASENAME_SNAKE_CASE]].process_event();
   SUCCEED();
}
)END";



std::string TEST_FILE_CONTENT = R"END(
#include <gtest/gtest.h>

#include <[[COMPONENT_HEADER_INCLUDE_FILE_PATH]]>

TEST([[COMPONENT_TEST_DESCRIPTION_NAME]], can_be_created_without_blowing_up)
{
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
}

TEST([[COMPONENT_TEST_DESCRIPTION_NAME]], run__returns_the_expected_response)
{
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, [[COMPONENT_BASENAME_SNAKE_CASE]].run());
}
)END";



std::vector<std::string> args;


#include <Blast/DirectoryCreator.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/Quintessence/ComponentGenerator.hpp>
#include <Blast/TemplatedFile.hpp>



bool create_directory(std::string dir)
{
   std::vector<std::string> directory_components = Blast::StringSplitter(dir, '/').split();
   Blast::DirectoryCreator directory_creator(directory_components);
   return directory_creator.create();
}



int main(int argc, char **argv)
{
   // parse the args into args
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   // validate invalid number of args
   if (args.size() <= 1)
   {
      std::stringstream error_message;
      error_message << "You must pass a component name.  This component name should include its nested folders "
                    << "like \"Foobar/Bar/Bazz\" where \"Foobar/Bar\" are the folders and \"Bazz\" is the name "
                    << "of the component.";
      throw std::runtime_error(error_message.str());
   }

   // create the component generator
   ComponentGenerator generator(argv[1]);

   // create the template variable and eplacement set
   std::vector<std::pair<std::string, std::string>> template_var_and_replacement_set = {
      { "[[COMPONENT_HEADER_INCLUDE_FILE_PATH]]", generator.get_header_filename() },
      { "[[COMPONENT_TEST_DESCRIPTION_NAME]]", generator.get_google_test_description_prefix() },
      { "[[COMPONENT_CLASS_NAME]]", generator.get_program_body_class_name() },
      { "[[COMPONENT_BASENAME_SNAKE_CASE]]", generator.get_component_tail_snakecase() },
      { "[[COMPONENT_AS_ALL_CAPS_CONSTANT]]", generator.get_component_tail_all_caps_constant() },
   };

   // create the folders for the components
   std::cout << "Making sure necessary folders are present...";
   create_directory(generator.get_quintessence_foldername());
   create_directory(generator.get_test_foldername());
   std::cout << "...component folders created.";

   // open the files for dumping
   std::cout << "Generating component files..." << std::endl;

   // create a list of files to be generated
   // filename, template_text, outfile stream
   std::map<std::string, std::pair<std::string, std::ofstream *>> outfiles = {
      { generator.get_quintessence_filename(), std::pair<std::string, std::ofstream *>(QUINTESSENCE_FILE_CONTENT, nullptr) },
      { generator.get_test_filename(), std::pair<std::string, std::ofstream *>(TEST_FILE_CONTENT, nullptr) },
   };

   // create the pointers to the ofstreams
   for (auto &outfile : outfiles)
   {
      std::ofstream *outfile_stream = new std::ofstream();
      outfile.second.second = outfile_stream;
   }

   // validate that the created files have been opened and are ready for writing
   bool outfiles_can_be_opened = true;
   std::stringstream outfiles_that_cannot_be_opened;
   for (auto &outfile : outfiles)
   {
      if (!outfile.second.second->is_open())
      {
         outfiles_can_be_opened = false;
         outfiles_that_cannot_be_opened << outfile.first << ", ";
         break;
      }
   }
   if (!outfiles_can_be_opened)
   {
      std::stringstream error_message;
      error_message << "The following files could not be created: ";
      error_message << outfiles_that_cannot_be_opened.str();
      throw std::runtime_error(error_message.str());
   }

   for (auto &outfile : outfiles)
   {
      std::string template_text = outfile.second.first;
      std::ofstream *outfile_stream = outfile.second.second;
      Blast::TemplatedFile templated_file(template_text, template_var_and_replacement_set);
      (*outfile_stream) << templated_file.generate_content();
      outfile_stream->close();
   }

   // output success
   std::stringstream finish_message;
   finish_message << "✅ Component files generated:" << std::endl;
   finish_message << "* " << generator.get_quintessence_filename() << std::endl
                  << "* " << generator.get_test_filename() << std::endl
                  << "generated." << std::endl;

   std::cout << finish_message.str() << std::endl;

   return 0;
}
