

#include <Blast/ProjectComponentFileTypes.hpp>


namespace Blast
{


std::string ProjectComponentFileTypes::get_project_file_type_str(ProjectComponentFileTypes::project_file_type_t project_file_type)
{
   switch(project_file_type)
   {
   case QUINTESSENCE_FILE: return "quintessence file"; break;
   case SOURCE_FILE: return "source file"; break;
   case HEADER_FILE: return "header file"; break;
   case TEST_FILE: return "test file"; break;
   case EXAMPLE_FILE: return "example file"; break;
   case OBJECT_FILE: return "object file"; break;
   case TEST_BINARY: return "test binary"; break;
   case EXAMPLE_BINARY: return "example binary"; break;
   case DOCUMENTATION_FILE: return "documentation file"; break;
   case NOT_IDENTIFIABLE: return "not identifiable"; break;
   default: return "uknown file type definition"; break;
   }
}


} // namespace Blast


