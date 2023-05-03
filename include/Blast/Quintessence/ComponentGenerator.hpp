#pragma once



#include <string>



class ComponentGenerator
{
private:
   std::string component_name;

public:
   ComponentGenerator(std::string component_name="Foo/Bar");

   std::string get_component_name();
   std::string get_component_name_first_fragment();
   std::string get_component_name_last_fragment();
   std::string get_component_name_up_to_last_fragment();
   std::string get_component_name_preceeding_fragment();

   std::string get_class_name();
   std::string get_class_name_up_to_last_fragment();

   std::string get_quintessence_path_and_filename();
   std::string get_documentation_path_and_filename();
   std::string get_test_path_and_filename();
   std::string get_quintessence_foldername();
   std::string get_test_foldername();
   std::string get_header_foldername();
   std::string get_source_foldername();
   std::string get_header_filename();
   std::string get_header_path_and_filename();
   std::string get_source_filename();
   std::string get_source_path_and_filename();
   std::string get_google_test_description_prefix();
   std::string get_program_body_class_name();
   static std::string build_command_to_make_parent_directories_for(std::string path_with_filename);
   std::string get_component_tail_snakecase();
   std::string get_component_tail_all_caps_constant();

   bool generate();
};



