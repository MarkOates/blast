#pragma once


#include <Blast/ProjectComponentFileTypes.hpp>
#include <iostream>
#include <string>


namespace Blast
{
   class ProjectComponentBasenameExtractor
   {
   private:
      std::string filename;

   public:
      ProjectComponentBasenameExtractor(std::string filename="");
      ~ProjectComponentBasenameExtractor();

      void set_filename(std::string filename);
      std::string get_filename();

      std::pair<ProjectComponentFileTypes::project_file_type_t, std::string> extract_component();
      ProjectComponentFileTypes::project_file_type_t get_project_file_type();
      std::string get_component_basename();
   };
}


