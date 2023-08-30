


#include <Blast/Quintessence/ComponentGenerator.hpp>

#include <Blast/CamelCaseToUnderscoreConverter.hpp>
#include <Blast/CamelCaseToConstantConverter.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/StringJoiner.hpp>
#include <Blast/Errors.hpp>


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



#include <iostream>
#include <string>

static std::pair<std::string, std::string> ___extract_strings(const std::string& inputString)
{
    std::string searchString = "/Testing/Comparison/";

    // Find the position of the searchString in the inputString
    size_t foundPos = inputString.find(searchString);

    if (foundPos == std::string::npos) {
        // searchString not found in inputString
        return std::make_pair("", "");
    }

    // Calculate the position of the string preceding searchString
    size_t prefixStart = foundPos;
    size_t prefixLength = searchString.length();
    size_t prefixEnd = prefixStart;

    // Calculate the position of the string following searchString
    size_t suffixStart = foundPos + prefixLength;
    size_t suffixEnd = inputString.length() - 1;

    // Extract the strings
    std::string prefix = inputString.substr(prefixStart, prefixEnd);
    std::string suffix = inputString.substr(suffixStart, suffixEnd);

    return std::make_pair(prefix, suffix);
}



#include <regex>

std::vector<std::string> __validate_component_name(const std::string& inputString)
{
   // TODO: Move this class to a Blast/StringFormatValidator
   // TODO: Include validation that each token does not start with a number character

   std::vector<std::string> error_messages = {};

   // Check if the string contains only allowed characters
   std::regex allowedCharsRegex("^[a-zA-Z0-9_/]+$");
   if (!std::regex_match(inputString, allowedCharsRegex))
   {
      error_messages.push_back("cannot contain invalid characters");
   }

   // Check if the string starts with a number
   if (isdigit(inputString[0]))
   {
      error_messages.push_back("cannot start with a number");
   }

   // Check if the string starts or ends with the '/' character
   if (inputString.front() == '/' || inputString.back() == '/')
   {
      error_messages.push_back("cannot start or end with sashes");
   }

   // Check if the string has successive '/' characters
   std::regex successiveSlashRegex("//");
   if (std::regex_search(inputString, successiveSlashRegex))
   {
      error_messages.push_back("cannot contain successive sashes");
   }

   return error_messages;
}



ComponentGenerator::ComponentGenerator(std::string component_name)
   : component_name(component_name)
{}



std::string ComponentGenerator::get_component_name()
{
   return component_name;
}



std::string ComponentGenerator::get_component_name_first_fragment()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_component_name(), '/').split();
   if (tokens.empty()) throw std::runtime_error("error extracting get_component_name_first_fragment; extracted tokens appear to be empty");
   std::string component_tail = tokens.front();
   return component_tail;
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


std::string ComponentGenerator::get_component_name_preceeding_fragment()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_component_name(), '/').split();
   if (tokens.size() < 2) throw std::runtime_error("error extracting get_component_name_preceeding_fragment; extracted tokens "
                                                   "appear to have fewer than 2 token. At least 2 are needed.");
   return tokens[tokens.size()-2];
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



std::string ComponentGenerator::get_test_path_and_filename()
{
   std::stringstream ss;
   ss << TEST_FOLDER_NAME << "/" << get_component_name() << "Test.cpp";
   return ss.str();
}



std::string ComponentGenerator::get_quintessence_foldername()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_quintessence_path_and_filename(), '/').split();
   if (!tokens.empty()) tokens.pop_back();
   std::string result = Blast::StringJoiner(tokens, "/").join();
   return result;
}



std::string ComponentGenerator::get_test_foldername()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_test_path_and_filename(), '/').split();
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



std::string ComponentGenerator::build_command_to_make_parent_directories_for(std::string path_with_filename)
{
   // TODO: Consider sanitizing filename
   std::stringstream command;
   command << "mkdir -p \"$(dirname '" << path_with_filename << "')\""
           //<< " && echo \"Directory created: $(dirname '" << path_with_filename << "')\""
           ;
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



bool ComponentGenerator::has_valid_comparison_operand_class_name()
{
   // TODO: Add tests for this function
   std::vector<std::string> validation_error_messages = __validate_component_name(component_name);
   if (validation_error_messages.empty()) return true;
   return false;
}



std::string ComponentGenerator::infer_comparison_operand_class_name()
{
   // TODO: Add tests
   bool is_valid = has_valid_comparison_operand_class_name();
   if (!is_valid)
   {
      Blast::Errors::throw_error(
         "Blast::Quintessence::ComponentGenerator::infer_comparison_operand_class_name",
         "The component name \"" + component_name + "\" does not appear to be a valid component name."
      );
   }

   // TODO: Find a better name for this variable
   std::pair<std::string, std::string> front_and_back_strings = ___extract_strings(component_name);
   if (front_and_back_strings.first == "" && front_and_back_strings.second == "")
   {
      Blast::Errors::throw_error(
         "Blast::Quintessence::ComponentGenerator::infer_comparison_operand_class_name",
         "The component name \"" + component_name + "\" does not appear to be a valid comparison class (contains \"" +
            "/Testing/Comparison/\"), and as such a comparison operand class name cannot be inferred."
      );
   }

   return front_and_back_strings.second;
}



bool ComponentGenerator::has_valid_json_loader_operand_component_name()
{
   // TODO: Add tests for this function
   std::vector<std::string> validation_error_messages = __validate_component_name(component_name);
   if (validation_error_messages.empty()) return true;
   return false;
}



std::string ComponentGenerator::infer_json_loader_operand_component_name()
{
   std::vector<std::string> tokens = Blast::StringSplitter(get_component_name(), '/').split();
   std::vector<std::string> operand_component_name_tokens;
   bool special_token_found = false;
   const std::string SPECIAL_JSON_LOADER_NAMESPACE_TOKEN = "JSONLoaders";
   for (auto &token : tokens)
   {
      if (special_token_found)
      {
         operand_component_name_tokens.push_back(token);
      }
      else
      {
         if (token == SPECIAL_JSON_LOADER_NAMESPACE_TOKEN)
         {
            special_token_found = true;
            continue;
         }
      }
   }
   std::string result = Blast::StringJoiner(operand_component_name_tokens, "/").join();
   return result;
}



bool ComponentGenerator::generate()
{
   return false;
}



