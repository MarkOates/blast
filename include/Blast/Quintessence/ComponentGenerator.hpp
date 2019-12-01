#pragma once



#include <string>



class ComponentGenerator
{
private:
   std::string component_name;

public:
   ComponentGenerator(std::string component_name="Foo/Bar");

   std::string get_component_name();
   std::string get_quintessence_filename();
   std::string get_test_filename();
   std::string get_quintessence_foldername();
   std::string get_test_foldername();
   std::string get_header_filename();
   std::string get_google_test_description_prefix();
   std::string get_program_body_class_name();
   std::string get_command_for_make_dir();
};



