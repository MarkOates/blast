

#include <Blast/ProjectComponentBasenameExtractor.hpp>


namespace Blast
{


ProjectComponentBasenameExtractor::ProjectComponentBasenameExtractor(std::string filename)
   : filename(filename)
{
}


ProjectComponentBasenameExtractor::~ProjectComponentBasenameExtractor()
{
}


void ProjectComponentBasenameExtractor::set_filename(std::string filename)
{
   this->filename = filename;
}


std::string ProjectComponentBasenameExtractor::get_filename()
{
   return filename;
}


std::pair<ProjectComponentFileTypes::project_file_type_t, std::string> ProjectComponentBasenameExtractor::extract_component()
{
   if (filename.compare(0, 4, "src/") == 0)
   {
      std::string extracted = filename.substr(4);
      std::size_t found = extracted.find_first_of(".");
      extracted = extracted.substr(0, found);
      return std::pair<ProjectComponentFileTypes::project_file_type_t, std::string>(ProjectComponentFileTypes::SOURCE_FILE, extracted);
   }
   else if (filename.compare(0, 8, "include/") == 0)
   {
      std::string extracted = filename.substr(8);
      std::size_t found = extracted.find_first_of(".");
      extracted = extracted.substr(0, found);
      return std::pair<ProjectComponentFileTypes::project_file_type_t, std::string>(ProjectComponentFileTypes::HEADER_FILE, extracted);
   }
   else if (filename.compare(0, 6, "tests/") == 0)
   {
      std::string extracted = filename.substr(6);
      std::size_t found = extracted.find_first_of(".");
      extracted = extracted.substr(0, found);
      found = extracted.rfind("Test");
      extracted = extracted.substr(0, found);
      found = extracted.rfind("_test");
      extracted = extracted.substr(0, found);
      return std::pair<ProjectComponentFileTypes::project_file_type_t, std::string>(ProjectComponentFileTypes::TEST_FILE, extracted);
   }
   else if (filename.compare(0, 9, "examples/") == 0)
   {
      std::string extracted = filename.substr(9);
      std::size_t found = extracted.find_first_of(".");
      extracted = extracted.substr(0, found);
      found = extracted.rfind("Example");
      extracted = extracted.substr(0, found);
      found = extracted.rfind("_example");
      extracted = extracted.substr(0, found);
      return std::pair<ProjectComponentFileTypes::project_file_type_t, std::string>(ProjectComponentFileTypes::EXAMPLE_FILE, extracted);
   }
   else if (filename.compare(0, 4, "obj/") == 0)
   {
      std::string extracted = filename.substr(4);
      std::size_t found = extracted.find_first_of(".");
      extracted = extracted.substr(0, found);
      return std::pair<ProjectComponentFileTypes::project_file_type_t, std::string>(ProjectComponentFileTypes::OBJECT_FILE, extracted);
   }
   else if (filename.compare(0, 10, "bin/tests/") == 0)
   {
      std::string extracted = filename.substr(10);
      std::size_t found = extracted.find_first_of(".");
      extracted = extracted.substr(0, found);
      found = extracted.rfind("Test");
      extracted = extracted.substr(0, found);
      found = extracted.rfind("_test");
      extracted = extracted.substr(0, found);
      return std::pair<ProjectComponentFileTypes::project_file_type_t, std::string>(ProjectComponentFileTypes::TEST_BINARY, extracted);
   }
   else if (filename.compare(0, 13, "bin/examples/") == 0)
   {
      std::string extracted = filename.substr(13);
      std::size_t found = extracted.find_first_of(".");
      extracted = extracted.substr(0, found);
      found = extracted.rfind("Example");
      extracted = extracted.substr(0, found);
      found = extracted.rfind("_example");
      extracted = extracted.substr(0, found);
      return std::pair<ProjectComponentFileTypes::project_file_type_t, std::string>(ProjectComponentFileTypes::EXAMPLE_BINARY, extracted);
   }
   else
   {
      return std::pair<ProjectComponentFileTypes::project_file_type_t, std::string>(ProjectComponentFileTypes::NOT_IDENTIFIABLE, "");
   }
}


ProjectComponentFileTypes::project_file_type_t ProjectComponentBasenameExtractor::get_project_file_type()
{
   return extract_component().first;
}


std::string ProjectComponentBasenameExtractor::get_component_basename()
{
   return extract_component().second;
}


} // namespace Blast


