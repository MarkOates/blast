


#include <Blast/Quintessence/ComponentGenerator.hpp>
#include <Blast/CamelCaseToUnderscoreConverter.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/StringJoiner.hpp>


#include <sstream>
//#include <filesystem>
#include <vector>



static const std::string QUINTESSENCE_FOLDER_NAME = "quintessence";
static const std::string TEST_FOLDER_NAME = "tests";



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



ComponentGenerator::ComponentGenerator(std::string component_name)
   : component_name(component_name)
{}



std::string ComponentGenerator::get_component_name()
{
   return component_name;
}



std::string ComponentGenerator::get_quintessence_filename()
{
   std::stringstream ss;
   ss << QUINTESSENCE_FOLDER_NAME << "/" << get_component_name() << ".q.yml";
   return ss.str();
}



std::string ComponentGenerator::get_test_filename()
{
   std::stringstream ss;
   ss << TEST_FOLDER_NAME << "/" << get_component_name() << "Test.cpp";
   return ss.str();
}



std::string ComponentGenerator::get_quintessence_foldername()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_quintessence_filename(), '/').split();
   if (!tokens.empty()) tokens.pop_back();
   std::string result = Blast::StringJoiner(tokens, "/").join();
   return result;

   //this impl is preferible, but does not work with systems that do not have <filesystem>:
   //std::filesystem::path p = get_quintessence_filename();
   //return p.parent_path();
}



std::string ComponentGenerator::get_test_foldername()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_test_filename(), '/').split();
   if (!tokens.empty()) tokens.pop_back();
   std::string result = Blast::StringJoiner(tokens, "/").join();
   return result;

   //this impl is preferible, but does not work with systems that do not have <filesystem>:
   //std::filesystem::path p = get_test_filename();
   //return p.parent_path();
}



std::string ComponentGenerator::get_header_filename()
{
   std::stringstream ss;
   ss << get_component_name() << ".hpp";
   return ss.str();
}



std::string ComponentGenerator::get_google_test_description_prefix()
{
   std::string result = get_component_name();
   ___replace(result, "/", "_");
   result = result + "Test";
   std::stringstream ss;
   ss << "google_test_description_prefix(): " << result << std::endl;
   return result;
}



std::string ComponentGenerator::get_program_body_class_name()
{
   std::string result = get_component_name();
   ___replace(result, "/", "::");
   std::stringstream ss;
   ss << "get_program_body_class_name(): " << result << std::endl;
   return result;
}



std::string ComponentGenerator::get_command_for_make_dir()
{
   std::stringstream command;
   command << "mkdir \"" << component_name << "\"";
   return command.str();
}



std::string ComponentGenerator::get_component_tail_snakecase()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_component_name(), '/').split();
   if (tokens.empty()) throw std::runtime_error("error extracting component_basemane_tail; extracted tokens appear to be empty");
   std::string component_tail = tokens.back();
   return Blast::CamelCaseToUnderscoreConverter(component_tail).convert_to_underscores();
}



bool ComponentGenerator::generate()
{
   return false;
}



