#pragma once


#include <Blast/ProjectComponentFileTypes.hpp>
#include <string>


class ProjectComponentFilenameGenerator
{
private:
   std::string basename;
   project_file_type_t project_file_type;

public:
   ProjectComponentFilenameGenerator(std::string basename, project_file_type);
   ~ProjectComponentFilenameGenerator();

   void set_basename(std::string basename);
   void set_project_file_type(project_file_type_t project_file_type);
   std::string get_basename();
   project_file_type_t get_project_file_type();

   std::string generate_filename();
};


