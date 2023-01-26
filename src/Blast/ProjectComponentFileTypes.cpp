

#include <Blast/ProjectComponentFileTypes.hpp>


namespace Blast
{


std::string ProjectComponentFileTypes::get_project_file_type_str(ProjectComponentFileTypes::project_file_type_t project_file_type)
{
   switch(project_file_type)
   {

   case UNDEF: return "undefined"; break;
   case NOT_IDENTIFIABLE: return "not identifiable"; break;
   case QUINTESSENCE_FILE: return "quintessence file"; break;
   case SOURCE_FILE: return "source file"; break;
   case HEADER_FILE: return "header file"; break;
   case OBJECT_FILE: return "object file"; break;
   case TEST_SOURCE_FILE: return "test source file"; break;
   case TEST_OBJECT_FILE: return "test object file"; break;
   case TEST_EXECUTABLE_FILE: return "test executable file"; break;

   case EXAMPLE_SOURCE_FILE: return "example source file"; break;
   case EXAMPLE_OBJECT_FILE: return "example object file"; break;
   case EXAMPLE_EXECUTABLE_FILE: return "example executable file"; break;
   //case OBJECT_FILE: return "object file"; break;
   //case TEST_BINARY: return "test binary"; break;
   //case EXAMPLE_BINARY: return "example binary"; break;
   case DOCUMENTATION_FILE: return "documentation file"; break;
   //case NOT_IDENTIFIABLE: return "not identifiable"; break;
   default:
      throw std::runtime_error("[Blast::ProjectComponentFileTypes::get_project_file_type_str] error: invalid type");
      return "uknown file type definition";
   break;
   }
}


} // namespace Blast


