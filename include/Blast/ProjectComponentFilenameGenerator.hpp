#pragma once


#include <Blast/ProjectComponentFileTypes.hpp>
#include <string>


namespace Blast
{
   class ProjectComponentFilenameGenerator
   {
   private:
      std::string basename;
      ProjectComponentFileTypes::project_file_type_t project_file_type;
      bool use_underscores;

   public:
      ProjectComponentFilenameGenerator(
            std::string basename="",
            ProjectComponentFileTypes::project_file_type_t=ProjectComponentFileTypes::SOURCE_FILE,
            bool use_underscores=false
         );
      ~ProjectComponentFilenameGenerator();

      void set_basename(std::string basename);
      void set_use_underscores(bool use_underscores);
      void set_project_file_type(ProjectComponentFileTypes::project_file_type_t project_file_type);

      std::string get_basename();
      bool get_use_underscores();
      ProjectComponentFileTypes::project_file_type_t get_project_file_type();

      std::string generate_filename();
   };
}


