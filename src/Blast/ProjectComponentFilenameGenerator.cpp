

#include <Blast/ProjectComponentFilenameGenerator.hpp>
#include <string>


namespace Blast
{


ProjectComponentFilenameGenerator::ProjectComponentFilenameGenerator(std::string basename, ProjectComponentFileTypes::project_file_type_t project_file_type, bool use_underscores)
   : basename(basename)
   , project_file_type(project_file_type)
   , use_underscores(use_underscores)
{
}


ProjectComponentFilenameGenerator::~ProjectComponentFilenameGenerator()
{
}


void ProjectComponentFilenameGenerator::set_basename(std::string basename)
{
   this->basename = basename;
}


void ProjectComponentFilenameGenerator::set_use_underscores(bool use_underscores)
{
   this->use_underscores = use_underscores;
}


void ProjectComponentFilenameGenerator::set_project_file_type(ProjectComponentFileTypes::project_file_type_t project_file_type)
{
   this->project_file_type = project_file_type;
}


std::string ProjectComponentFilenameGenerator::get_basename()
{
   return basename;
}


bool ProjectComponentFilenameGenerator::get_use_underscores()
{
   return use_underscores;
}


ProjectComponentFileTypes::project_file_type_t ProjectComponentFilenameGenerator::get_project_file_type()
{
   return project_file_type;
}


std::string ProjectComponentFilenameGenerator::generate_filename()
{
   switch (project_file_type)
   {
   case ProjectComponentFileTypes::SOURCE_FILE:
      return std::string("src/") + basename + ".cpp";
      break;
   case ProjectComponentFileTypes::HEADER_FILE:
      return std::string("include/") + basename + ".hpp";
      break;
   case ProjectComponentFileTypes::TEST_FILE:
      return std::string("tests/") + basename + (use_underscores ? "_test.cpp" : "Test.cpp");
      break;
   case ProjectComponentFileTypes::EXAMPLE_FILE:
      return std::string("examples/") + basename + (use_underscores ? "_example.cpp" : "Example.cpp");
      break;
   case ProjectComponentFileTypes::OBJECT_FILE:
      return std::string("obj/") + basename + ".o";
      break;
   case ProjectComponentFileTypes::TEST_BINARY:
      return std::string("bin/tests/") + basename + (use_underscores ? "_test" : "Test");
      break;
   case ProjectComponentFileTypes::EXAMPLE_BINARY:
      return std::string("bin/examples/") + basename + (use_underscores ? "_example" : "Example");
      break;
   default:
      return "";
      break;
   };
}


} // namespace Blast


