


#include <Blast/Quintessence/ComponentGenerator.hpp>


#include <sstream>
#include <filesystem>



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
   std::filesystem::path p = get_quintessence_filename();
   return p.parent_path();
}



std::string ComponentGenerator::get_test_foldername()
{
   std::filesystem::path p = get_test_filename();
   return p.parent_path();
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



