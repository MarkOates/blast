#include <allegro5/allegro.h> // temporary fix for compatibility with union/Makefile


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>




static std::string file_get_contents(std::string filename);

std::string file_get_contents(std::string filename)
{
   std::ifstream file(filename.c_str());
   std::string input = "";
   if (!file) return "";
   char ch;
   while (file.get(ch)) input.append(1, ch);
   if (!file.eof()) return ""; // strange error
   file.close();
   return input;
}





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
      placement3d &place = get_place();
      place.start_transform();

      //This::Component::Renderer renderer;
      //renderer.render();

      place.restore_transform();
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
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
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

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class [[COMPONENT_TEST_DESCRIPTION_NAME]] : public ::testing::Test
{};

class [[COMPONENT_TEST_DESCRIPTION_NAME]]WithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <[[COMPONENT_HEADER_INCLUDE_FILE_PATH]]>


TEST_F([[COMPONENT_TEST_DESCRIPTION_NAME]], can_be_created_without_blowing_up)
{
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
}


TEST_F([[COMPONENT_TEST_DESCRIPTION_NAME]], render__without_allegro_initialized__raises_an_error)
{
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
   std::string expected_error_message =
      "[[COMPONENT_NAME_LAST_FRAGMENT]]::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE([[COMPONENT_BASENAME_SNAKE_CASE]].render(), std::runtime_error, expected_error_message);
}


TEST_F([[COMPONENT_TEST_DESCRIPTION_NAME]]WithAllegroRenderingFixture, render__will_not_blow_up)
{
   [[COMPONENT_CLASS_NAME]] [[COMPONENT_BASENAME_SNAKE_CASE]];
   [[COMPONENT_BASENAME_SNAKE_CASE]].render();
   SUCCEED();
}

)END";






std::vector<std::string> args;


#include <Blast/DirectoryCreator.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/Quintessence/ComponentGenerator.hpp>
#include <Blast/TemplatedFile.hpp>



class TemplateSetBase
{
public:
   std::string type;
   static const std::string TYPE;
   TemplateSetBase(std::string type=TYPE) : type(type) {}
   virtual ~TemplateSetBase() {}
   bool is_type(std::string type) { return this->type == type; }
};
const std::string TemplateSetBase::TYPE = "TemplateSetBase";



class QuintessenceTestTemplatePair : public TemplateSetBase
{
public:
   static const std::string TYPE;
   std::string quintessence_template_content;
   std::string test_template_content;

   QuintessenceTestTemplatePair(std::string quintessence_template_content="", std::string test_template_content="")
      : TemplateSetBase(TYPE)
      , quintessence_template_content(quintessence_template_content)
      , test_template_content(test_template_content)
   {}
};
const std::string QuintessenceTestTemplatePair::TYPE = "QuintessenceTestTemplatePair";



class HeaderSourceTestTemplatePair : public TemplateSetBase
{
public:
   static const std::string TYPE;
   std::string header_template_content;
   std::string source_template_content;
   std::string test_template_content;

   HeaderSourceTestTemplatePair(std::string header_template_content="", std::string source_template_content="", std::string test_template_content="")
      : TemplateSetBase(TYPE)
      , header_template_content(header_template_content)
      , source_template_content(source_template_content)
      , test_template_content(test_template_content)
   {}
};
const std::string HeaderSourceTestTemplatePair::TYPE = "HeaderSourceTestTemplatePair";




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
   // todo: ensure files exist
   std::string TEMPLATES_PATH = "/Users/markoates/Repos/blast/programs/templates/";

   std::map<std::string, QuintessenceTestTemplatePair*> dictionary = {
      { "standard_component", new QuintessenceTestTemplatePair(QUINTESSENCE_FILE_CONTENT, TEST_FILE_CONTENT) },
      { "stage", new QuintessenceTestTemplatePair(STAGE_QUINTESSENCE_FILE_CONTENT, STAGE_TEST_FILE_CONTENT) },
      { "renderer", new QuintessenceTestTemplatePair(RENDERER_QUINTESSENCE_FILE_CONTENT, RENDERER_TEST_FILE_CONTENT) },
      { "base", new QuintessenceTestTemplatePair(file_get_contents(TEMPLATES_PATH + "base.q.txt"), file_get_contents(TEMPLATES_PATH + "base_test.txt")) },
   };

   std::string dictionary_identifier_to_use = "standard_component";

   // parse the args into args
   for (int i=0; i<argc; i++) args.push_back(argv[i]);

   // validate invalid number of args
   if (args.size() <= 1)
   {
      std::stringstream error_message;
      error_message << std::endl;
      error_message << "You must pass a component name.  This component name should include its nested folders "
                    << "like \"Foobar/Bar/Bazz\" where \"Foobar/Bar\" are the folders and \"Bazz\" is the name "
                    << "of the component.";
      error_message << std::endl;
      error_message << "Optionally, you can also pass as a second argument for a template set to use when generating your component.  The options are:"
                    << std::endl;
      for (auto &dictionary_listing : dictionary)
      {
         error_message << "   - \"" << dictionary_listing.first << "\"" << std::endl;
      }
      error_message << std::endl;
      throw std::runtime_error(error_message.str());
   }

   // snag the second arg, and set it to the "dictionary_identifier_to_use"
   if (args.size() >= 3)
   {
      dictionary_identifier_to_use = args[2];
   }

         // validate "dictionary_identifier_to_use" is in the dictionary
         std::map<std::string, QuintessenceTestTemplatePair*>::iterator it = dictionary.find(dictionary_identifier_to_use);
         if (it == dictionary.end())
         {
            std::stringstream error_message;
            error_message << "As your second argument, you passed in an invalid template name \"" << dictionary_identifier_to_use << "\""
                          << std::endl;
            error_message << "The valid options are:"
                          << std::endl;
            for (auto &dictionary_listing : dictionary)
            {
               error_message << "   - \"" << dictionary_listing.first << "\"" << std::endl;
            }
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
      { "[[COMPONENT_NAME_LAST_FRAGMENT]]", generator.get_component_name_last_fragment() },
   };




   TemplateSetBase *template_set = dictionary[dictionary_identifier_to_use];
   std::map<std::string, std::pair<std::string, std::ofstream *>> outfiles;

   if (!template_set)
   {
      // Throw weird error
   }
   else
   {
      if (template_set->is_type(QuintessenceTestTemplatePair::TYPE))
      {
         QuintessenceTestTemplatePair* quintessence_test_template_pair = dynamic_cast<QuintessenceTestTemplatePair*>(template_set);

         // create the folders for the components
         std::cout << "Making sure necessary folders are present...";
         create_directory(generator.get_quintessence_foldername()),
         create_directory(generator.get_test_foldername());
         std::cout << "...component folders created.";

         // open the files for dumping
         std::cout << "Generating component files..." << std::endl;


         // create a list of files to be generated
         // filename, template_text, outfile stream
         std::string quintessence_template_content = quintessence_test_template_pair->quintessence_template_content;
         std::string test_template_content = quintessence_test_template_pair->test_template_content;

         outfiles = {
            { generator.get_quintessence_filename(), std::pair<std::string, std::ofstream *>(quintessence_template_content, nullptr) },
            { generator.get_test_filename(), std::pair<std::string, std::ofstream *>(test_template_content, nullptr) },
         };
      }
      else if (template_set->is_type(HeaderSourceTestTemplatePair::TYPE))
      {
         HeaderSourceTestTemplatePair* header_source_test_template_pair = dynamic_cast<HeaderSourceTestTemplatePair*>(template_set);

         // create the folders for the components
         std::cout << "Making sure necessary folders are present...";
         create_directory(generator.get_header_foldername()),
         create_directory(generator.get_source_foldername());
         create_directory(generator.get_test_foldername());
         std::cout << "...component folders created.";

         // open the files for dumping
         std::cout << "Generating component files..." << std::endl;


         // create a list of files to be generated
         // filename, template_text, outfile stream
         std::string header_template_content = header_source_test_template_pair->header_template_content;
         std::string source_template_content = header_source_test_template_pair->source_template_content;
         std::string test_template_content = header_source_test_template_pair->test_template_content;

         outfiles = {
            { generator.get_header_filename(), std::pair<std::string, std::ofstream *>(header_template_content, nullptr) },
            { generator.get_source_filename(), std::pair<std::string, std::ofstream *>(source_template_content, nullptr) },
            { generator.get_test_filename(), std::pair<std::string, std::ofstream *>(test_template_content, nullptr) },
         };
      }
   }




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



   // destroy the dictionary items
   for (auto &dictionary_listing : dictionary) delete dictionary_listing.second;
   dictionary.clear();


   return 0;
}
