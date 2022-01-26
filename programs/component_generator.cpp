#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>



std::string QUINTESSENCE_FOLDER_NAME = "quintessence";
std::string TEST_FOLDER_NAME = "tests";




//////////////////////////////
////   TYPICAL COMPONENT
//////////////////////////////


std::string const QUINTESSENCE_FILE_CONTENT = R"END(functions:
  - name: run
    type: std::string
    body: return "Hello World!";
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







//////////////////////////////
////   STAGE
//////////////////////////////


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








//////////////////////////////
////   RENDERER
//////////////////////////////


std::string const RENDERER_QUINTESSENCE_FILE_CONTENT = R"END(properties:


  - name: font_bin
    type: AllegroFlare::FontBin*
    init_with: nullptr
    constructor_arg: true

  - name: quote
    type: std::string
    init_with: '{}'


functions:


  - name: render
    type: void
    guards: [ al_is_system_installed(), al_is_font_addon_initialized() ]
    body: |
      return;

  - name: obtain_font
    private: true
    type: ALLEGRO_FONT*
    guards: [ font_bin ]
    body: |
      return font_bin->auto_get("Purista Medium.otf -32");


dependencies:


  - symbol: AllegroFlare::FontBin*
    headers: [ AllegroFlare/FontBin.hpp ]
  - symbol: ALLEGRO_FONT*
    headers: [ allegro5/allegro_font.h ]

)END";


std::string const RENDERER_TEST_FILE_CONTENT = R"END(
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_Elements_QuoteRendererTestWithEmptyFixture : public ::testing::Test
{};

class Hexagon_Elements_QuoteRendererTestWithAllegroRenderingFixture : public Testing::WithAllegroRenderingFixture
{};


#include <Hexagon/Elements/QuoteRenderer.hpp>


TEST_F(Hexagon_Elements_QuoteRendererTestWithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
}


TEST_F(Hexagon_Elements_QuoteRendererTestWithEmptyFixture, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
   std::string expected_error_message =
      "QuoteRenderer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(quote_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(Hexagon_Elements_QuoteRendererTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   Hexagon::Elements::QuoteRenderer quote_renderer;
   quote_renderer.render();
   SUCCEED();
}

)END";






std::vector<std::string> args;


#include <Blast/DirectoryCreator.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/Quintessence/ComponentGenerator.hpp>
#include <Blast/TemplatedFile.hpp>



class QuintessenceTestTemplatePair
{
public:
   std::string quintessence_template_content;
   std::string test_template_content;

   QuintessenceTestTemplatePair(std::string quintessence_template_content="", std::string test_template_content="")
      : quintessence_template_content(quintessence_template_content)
      , test_template_content(test_template_content)
   {}
};



bool create_directory(std::string dir)
{
   std::vector<std::string> directory_components = Blast::StringSplitter(dir, '/').split();
   Blast::DirectoryCreator directory_creator(directory_components);
   return directory_creator.create();
}



class OutputSet
{
public:
   ComponentGenerator generator;
   std::string template_text;
   std::ofstream *output_stream;

   OutputSet(std::string component_name, std::string template_text)
      : generator(component_name)
      , template_text(template_text)
      , output_stream(nullptr)
   {}
};



int main(int argc, char **argv)
{
   std::map<std::string, QuintessenceTestTemplatePair> dictionary = {
      { "standard_component", QuintessenceTestTemplatePair(QUINTESSENCE_FILE_CONTENT, TEST_FILE_CONTENT) },
      { "stage", QuintessenceTestTemplatePair(STAGE_QUINTESSENCE_FILE_CONTENT, STAGE_TEST_FILE_CONTENT) },
      { "renderer", QuintessenceTestTemplatePair(RENDERER_QUINTESSENCE_FILE_CONTENT, RENDERER_TEST_FILE_CONTENT) },
   };

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
   std::string quintessence_template_content = dictionary["standard_component"].quintessence_template_content;
   std::string test_template_content = dictionary["standard_component"].test_template_content;

   std::map<std::string, std::pair<std::string, std::ofstream *>> outfiles = {
      { generator.get_quintessence_filename(), std::pair<std::string, std::ofstream *>(quintessence_template_content, nullptr) },
      { generator.get_test_filename(), std::pair<std::string, std::ofstream *>(test_template_content, nullptr) },
   };

   // create the pointers to the ofstreams
   for (auto &outfile : outfiles)
   {
      std::string filename = outfile.first;
      std::ofstream *outfile_stream = new std::ofstream();
      outfile.second.second = outfile_stream;
      outfile.second.second->open(filename, std::ios::binary);
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
   }

   // delete the outfiles
   for (auto &outfile : outfiles)
   {
      std::ofstream *outfile_stream = outfile.second.second;
      outfile_stream->close();
      delete outfile_stream;
      outfile.second.second = nullptr;
   }

   // output success
   std::stringstream finish_message;
   finish_message << "✅ Component files generated:" << std::endl;
   for (auto &outfile : outfiles)
   {
      std::string filename = outfile.first;
      finish_message << "  - " << filename << std::endl;
   }
   finish_message << "generated." << std::endl;
   std::cout << finish_message.str() << std::endl;

   return 0;
}
