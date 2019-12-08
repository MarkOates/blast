#pragma once


#include <string>


namespace Blast
{
   class ProjectComponentFileTypes
   {
   public:
      enum project_file_type_t
      {
         NOT_IDENTIFIABLE,
         QUINTESSENCE_FILE,
         SOURCE_FILE,
         HEADER_FILE,
         TEST_FILE,
         EXAMPLE_FILE,
         OBJECT_FILE,
         TEST_BINARY,
         EXAMPLE_BINARY
      };

      static std::string get_project_file_type_str(ProjectComponentFileTypes::project_file_type_t project_file_type);
   };
}


