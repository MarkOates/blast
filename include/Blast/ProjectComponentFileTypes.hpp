#pragma once


#include <string>


namespace Blast
{
   class ProjectComponentFileTypes
   {
   public:
      enum project_file_type_t
      {
         UNDEF,
         NOT_IDENTIFIABLE,
         QUINTESSENCE_FILE,
         SOURCE_FILE,
         HEADER_FILE,
         OBJECT_FILE,
         TEST_SOURCE_FILE,
         TEST_OBJECT_FILE,
         TEST_EXECUTABLE_FILE,
         EXAMPLE_SOURCE_FILE,
         EXAMPLE_OBJECT_FILE,
         EXAMPLE_EXECUTABLE_FILE,
         DOCUMENTATION_FILE,
      };

      static std::string get_project_file_type_str(ProjectComponentFileTypes::project_file_type_t project_file_type);
   };
}


