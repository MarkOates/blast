


#include <Blast/Quintessence/ComponentGenerator.hpp>
#include <Blast/CamelCaseToUnderscoreConverter.hpp>
#include <Blast/CamelCaseToConstantConverter.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/StringJoiner.hpp>


#include <sstream>
#include <vector>
#include <iostream>



static const std::string QUINTESSENCE_FOLDER_NAME = "quintessence";
static const std::string TEST_FOLDER_NAME = "tests";
static const std::string DOCUMENTATION_FOLDER_NAME = "docs";



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



std::string ComponentGenerator::get_component_name_last_fragment()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_component_name(), '/').split();
   if (tokens.empty()) throw std::runtime_error("error extracting get_last_component_name_fragment; extracted tokens appear to be empty");
   std::string component_tail = tokens.back();
   return component_tail;
}



std::string ComponentGenerator::get_component_name_up_to_last_fragment()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_component_name(), '/').split();
   if (tokens.empty()) throw std::runtime_error("error extracting get_last_component_name_fragment; extracted tokens "
                                                "appear to be empty");
   tokens.pop_back(); // remove the last fragment
   std::string result = Blast::StringJoiner(tokens, "/").join();
   return result;
}



std::string ComponentGenerator::get_class_name()
{
   std::string result = get_component_name();
   ___replace(result, "/", "::");
   return result;
}



std::string ComponentGenerator::get_class_name_up_to_last_fragment()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_component_name(), '/').split();
   if (tokens.empty()) return "";

   tokens.pop_back(); // remove the last fragment
   std::string result = Blast::StringJoiner(tokens, "::").join();

   return result;
}



std::string ComponentGenerator::get_quintessence_filename()
{
   // TODO fix instances of this to use get_quintessence_path_and_filename() instead
   std::cout << "WARNING: ComponentGenerator::get_quintessence_filename is depreciated, use ComponentGenerator::get_quintessence_path_and_filename() instead (it's the same, but the prior function will change return value in the future.)" << std::endl;
   std::stringstream ss;
   ss << QUINTESSENCE_FOLDER_NAME << "/" << get_component_name() << ".q.yml";
   return ss.str();
}


std::string ComponentGenerator::get_quintessence_path_and_filename()
{
   std::stringstream ss;
   ss << QUINTESSENCE_FOLDER_NAME << "/" << get_component_name() << ".q.yml";
   return ss.str();
}



std::string ComponentGenerator::get_documentation_path_and_filename()
{
   std::stringstream ss;
   ss << DOCUMENTATION_FOLDER_NAME << "/" << get_component_name() << ".md";
   return ss.str();
}




std::string ComponentGenerator::get_test_filename()
{
   // TODO fix instances of this to use get_quintessence_path_and_filename() instead
   std::cout << "WARNING: ComponentGenerator::get_test_filename is depreciated, use ComponentGenerator::get_test_path_and_filename() instead (it's the same, but the prior function will change return value in the future.)" << std::endl;
   std::stringstream ss;
   ss << TEST_FOLDER_NAME << "/" << get_component_name() << "Test.cpp";
   return ss.str();
}


std::string ComponentGenerator::get_test_path_and_filename()
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
}



std::string ComponentGenerator::get_test_foldername()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_test_filename(), '/').split();
   if (!tokens.empty()) tokens.pop_back();
   std::string result = Blast::StringJoiner(tokens, "/").join();
   return result;
}



std::string ComponentGenerator::get_header_foldername()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_header_path_and_filename(), '/').split();
   if (!tokens.empty()) tokens.pop_back();
   std::string result = Blast::StringJoiner(tokens, "/").join();
   return result;
}



std::string ComponentGenerator::get_source_foldername()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_source_path_and_filename(), '/').split();
   if (!tokens.empty()) tokens.pop_back();
   std::string result = Blast::StringJoiner(tokens, "/").join();
   return result;
}



std::string ComponentGenerator::get_header_filename()
{
   std::stringstream ss;
   ss << get_component_name() << ".hpp";
   return ss.str();
}



std::string ComponentGenerator::get_header_path_and_filename()
{
   std::stringstream ss;
   ss << "include/" << get_header_filename();
   return ss.str();
}




std::string ComponentGenerator::get_source_filename()
{
   std::stringstream ss;
   ss << get_component_name() << ".cpp";
   return ss.str();
}



std::string ComponentGenerator::get_source_path_and_filename()
{
   std::stringstream ss;
   ss << "src/" << get_source_filename();
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



std::string ComponentGenerator::get_component_tail_all_caps_constant()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_component_name(), '/').split();
   if (tokens.empty()) throw std::runtime_error("error extracting component_basemane_tail; extracted tokens appear to be empty");
   std::string component_tail = tokens.back();
   return Blast::CamelCaseToConstantConverter(component_tail).convert_to_constant();
}



bool ComponentGenerator::generate()
{
   return false;
}



