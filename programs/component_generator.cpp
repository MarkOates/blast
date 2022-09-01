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

   std::map<std::string, TemplateSetBase*> dictionary = {
      { "standard_component", new QuintessenceTestTemplatePair(file_get_contents(TEMPLATES_PATH + "standard.q.txt"), file_get_contents(TEMPLATES_PATH + "standard_test.txt")) },
      { "hexagon_stage", new QuintessenceTestTemplatePair(file_get_contents(TEMPLATES_PATH + "Hexagon/stage.q.txt"), file_get_contents(TEMPLATES_PATH + "Hexagon/stage_test.txt")) },
      { "renderer", new QuintessenceTestTemplatePair(file_get_contents(TEMPLATES_PATH + "renderer.q.txt"), file_get_contents(TEMPLATES_PATH + "renderer_test.txt")) },
      { "base", new QuintessenceTestTemplatePair(file_get_contents(TEMPLATES_PATH + "base.q.txt"), file_get_contents(TEMPLATES_PATH + "base_test.txt")) },
      { "derived", new QuintessenceTestTemplatePair(file_get_contents(TEMPLATES_PATH + "derived.q.txt"), file_get_contents(TEMPLATES_PATH + "derived_test.txt")) },
      { "comparison", new HeaderSourceTestTemplatePair(file_get_contents(TEMPLATES_PATH + "comparison.hpp.txt"), file_get_contents(TEMPLATES_PATH + "comparison.cpp.txt"), file_get_contents(TEMPLATES_PATH + "comparison_test.txt")) },
      { "json_loader", new HeaderSourceTestTemplatePair(file_get_contents(TEMPLATES_PATH + "json_loader.hpp.txt"), file_get_contents(TEMPLATES_PATH + "json_loader.cpp.txt"), file_get_contents(TEMPLATES_PATH + "json_loader_test.txt")) },
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
      error_message << "Optionally you can also pass a second argument, representing a template to use when generating your component.  The available templates arguments are:"
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
         std::map<std::string, TemplateSetBase*>::iterator it = dictionary.find(dictionary_identifier_to_use);
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
      { "[[COMPONENT_CLASS_NAME]]", generator.get_class_name() },
      { "[[COMPONENT_CLASS_NAME_UP_TO_LAST_FRAGMENT]]", generator.get_class_name_up_to_last_fragment() },
      { "[[COMPONENT_BASENAME_SNAKE_CASE]]", generator.get_component_tail_snakecase() },
      { "[[COMPONENT_AS_ALL_CAPS_CONSTANT]]", generator.get_component_tail_all_caps_constant() },
      { "[[COMPONENT_NAME]]", generator.get_component_name() },
      { "[[COMPONENT_NAME_LAST_FRAGMENT]]", generator.get_component_name_last_fragment() },
      { "[[COMPONENT_NAME_LAST_TWO_FRAGMENTS]]", generator.get_component_name_last_fragment() }, // TODO: create a function that will return this value
      { "[[COMPONENT_NAME_UP_TO_LAST_FRAGMENT]]", generator.get_component_name_up_to_last_fragment() },
      { "[[COMPONENT_NAME_PRECEEDING_FRAGMENT]]", generator.get_component_name_preceeding_fragment() },
      { "[[COMPONENT_NAME_FROM_THIRD_FRAGMENT_UP_TO_LAST_FRAGMENT]]", generator.get_component_name_up_to_last_fragment() }, // TODO: create a function that will return this
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
            { generator.get_header_path_and_filename(), std::pair<std::string, std::ofstream *>(header_template_content, nullptr) },
            { generator.get_source_path_and_filename(), std::pair<std::string, std::ofstream *>(source_template_content, nullptr) },
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
