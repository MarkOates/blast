

#include <Blast/ProjectComponentBasenameExtractor.hpp>

#include <iostream>
#include <vector>


int main(int argc, char **argv)
{
   std::cout << "This example program has been disabled because the code is obsolete and does not demonstrate the latest constants for Blast::ProjectComponentFileTypes." << std::endl;

   // TODO: this example program

   //std::vector<std::pair<Blast::ProjectComponentFileTypes::project_file_type_t, std::string>> example_files = {
      //{ Blast::ProjectComponentFileTypes::SOURCE_FILE, "src/models/Foobar.cpp" },
      //{ Blast::ProjectComponentFileTypes::HEADER_FILE, "include/models/Foobar.hpp" },
      //{ Blast::ProjectComponentFileTypes::TEST_SOURCE_FILE, "tests/models/FoobarTest.cpp" },
      //{ Blast::ProjectComponentFileTypes::EXAMPLE_SOURCE_FILE, "examples/models/FoobarExample.cpp" },
      //{ Blast::ProjectComponentFileTypes::OBJECT_FILE, "obj/models/Foobar.o" },
      //{ Blast::ProjectComponentFileTypes::TEST_EXECUTABLE, "bin/tests/models/FoobarTest" },
      //{ Blast::ProjectComponentFileTypes::EXAMPLE_BINARY, "bin/examples/models/FoobarExample" },
      //{ Blast::ProjectComponentFileTypes::NOT_IDENTIFIABLE, "not_project_file.txt" },
   //};

   //for (auto example_file : example_files)
   //{
      //Blast::ProjectComponentBasenameExtractor project_component_basename_extractor(example_file.second);

      //std::string type_str = Blast::ProjectComponentFileTypes::get_project_file_type_str(project_component_basename_extractor.get_project_file_type());

      //std::cout << "filename: " << project_component_basename_extractor.get_filename() << std::endl;
      //std::cout << "  type: " << type_str << std::endl;
      //std::cout << "  basename: " << project_component_basename_extractor.get_component_basename() << std::endl;
   //}

   //return 0;
}


