


#include <Blast/Cpp/ClassGenerator.hpp>
#include <Blast/Cpp/Function.hpp>
#include <Blast/Cpp/FunctionArgument.hpp>
#include <Blast/StringSplitter.hpp>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>



class QuintessenceClassNameFromYAMLFilenameInferer
{
private:
   std::string yaml_filename;

public:
   QuintessenceClassNameFromYAMLFilenameInferer(std::string yaml_filename)
      : yaml_filename(yaml_filename)
   {}

   std::string infer_class_name()
   {
      std::vector<std::string> tokens = Blast::StringSplitter(yaml_filename, '/').split();
      if (tokens.empty()) throw std::runtime_error("Can't parse tokens as expected from the filename");
      std::string basename_and_extension = tokens[tokens.size()-1];
      std::vector<std::string> basename_and_extension_components = Blast::StringSplitter(basename_and_extension, '.').split();
      if (basename_and_extension_components.empty()) throw std::runtime_error("Can't parse basename and extensions");
      return basename_and_extension_components[0];
   }
};



void write_to_files(Blast::Cpp::ClassGenerator &cpp_class_generator)
{
   std::string header_filepath = cpp_class_generator.project_header_filepath();

   std::ofstream header_file(header_filepath, std::ofstream::out);
   if (header_file.fail())
   {
      std::stringstream error_message;
      error_message << "Could not open header file \"" << header_filepath << "\" for writing.";
      throw std::runtime_error(error_message.str());
   }
   header_file << cpp_class_generator.generate_header_file_content();

   std::string source_filepath = cpp_class_generator.project_source_filepath();
   std::ofstream source_file(source_filepath, std::ofstream::out);
   if (source_file.fail()) throw std::runtime_error("Could not open source file for writing.");
   source_file << cpp_class_generator.generate_source_file_content();

   // output success
   std::cout << "done. Files generated \033[1m\033[32m" << header_filepath << " and " << source_filepath << "\033[0m" << std::endl;
}



int main(int argc, char **argv)
{
   if (argc <= 1)
   {
      std::cout << "You must pass a quintessence filename as an argument" << std::endl;
      return 1;
   }

   for (int i=1; i<argc; i++)
   {
      std::string quintessence_filename = argv[i];
      YAML::Node source = YAML::LoadFile(quintessence_filename);

      QuintessenceClassNameFromYAMLFilenameInferer class_name_inferer(argv[i]);
      std::string class_name = class_name_inferer.infer_class_name();

      Blast::Cpp::Class klass(class_name);

      //// generate and write the files

      Blast::Cpp::ClassGenerator cpp_class_generator(klass);
      write_to_files(cpp_class_generator);
   }

   return 0;
}



