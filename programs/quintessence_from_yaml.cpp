


#include <Blast/Cpp/ClassGenerator.hpp>
#include <Blast/Cpp/Function.hpp>
#include <Blast/Cpp/FunctionArgument.hpp>
#include <Blast/StringSplitter.hpp>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>



void explode(std::string location, std::string error_message)
{
   std::stringstream ss;
   ss << "‼️ [" << location << "] " << error_message;
   throw std::runtime_error(ss.str());
}


void validate(bool value, std::string location, std::string error_message)
{
   if (!value) explode(location, error_message);
}


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


void create_folders_for_file(std::string filepath)
{
   std::stringstream error_message;
   error_message << "Could not create folders for \"" << filepath << "\", this convenience feature is not yet implemented.";
   explode("create_folders_for_file", error_message.str());
}


void write_to_files(Blast::Cpp::ClassGenerator &cpp_class_generator, bool automatically_create_folders=true)
{
   std::string header_filepath = cpp_class_generator.project_header_filepath();
   std::string source_filepath = cpp_class_generator.project_source_filepath();

   std::ofstream header_file(header_filepath, std::ofstream::out);
   if (header_file.fail())
   {
      if (!automatically_create_folders)
      {
         std::stringstream error_message;
         error_message << "Could not open header file \"" << header_filepath << "\" for writing.  Most likely the directories need to be created.";
         explode("write_to_files", error_message.str());
      }
      create_folders_for_file(header_filepath);
   }

   std::ofstream source_file(source_filepath, std::ofstream::out);
   if (source_file.fail())
   {
      if (!automatically_create_folders)
      {
         std::stringstream error_message;
         error_message << "Could not open source file \"" << source_filepath << "\" for writing.  Most likely the directories need to be created.";
         explode("write_to_files", error_message.str());
      }
      create_folders_for_file(source_filepath);
   }


   // obtain the output content

   std::string header_file_content = cpp_class_generator.generate_header_file_content();
   std::string source_file_content = cpp_class_generator.generate_source_file_content();


   // output the actual content

   header_file << header_file_content;
   source_file << source_file_content;

   // output success
   std::cout << "done. Files generated \033[1m\033[32m" << header_filepath << " and " << source_filepath << "\033[0m" << std::endl;
}



std::vector<std::string> extract_sequence_as_string_array(YAML::Node &source)
{
   std::string this_func_name = "extract_sequence_as_string_array";
   std::vector<std::string> result;

   for (YAML::const_iterator it=source.begin(); it!=source.end(); ++it)
   {
      validate(it->IsScalar(), this_func_name, "Unexpected sequence element, expected to be of a YAML Scalar.");
      result.push_back(it->as<std::string>());
   }

   return result;
}



std::vector<std::string> extract_namespaces(YAML::Node &source)
{
   std::string this_func_name = "extract_namespaces";
   const std::string NAMESPACES = "namespaces";
   std::vector<std::string> result;

   YAML::Node source_namespaces = source[NAMESPACES];

   validate(source_namespaces.IsSequence(), this_func_name, "Expected \"namespaces\" to be of a YAML Sequence type.");

   return extract_sequence_as_string_array(source_namespaces);
}



std::vector<Blast::Cpp::ParentClassProperties> extract_parent_classes_properties(YAML::Node &source)
{
   std::string this_func_name = "extract_parent_classes_properties";
   const std::string PARENT_CLASSES = "parent_classes";
   std::vector<Blast::Cpp::ParentClassProperties> result;

   YAML::Node source_parent_classes = source[PARENT_CLASSES];

   validate(source_parent_classes.IsSequence(), this_func_name, "Expected \"parent_classes\" to be of a YAML Sequence type.");

   for (YAML::const_iterator it=source_parent_classes.begin(); it!=source_parent_classes.end(); ++it)
   {
      const std::string CLASS = "class";
      const std::string SCOPE = "scope";
      const std::string INIT_WITH = "init_with";

      validate(it->IsMap(), this_func_name, "Unexpected sequence element in \"parent_classes\", expected to be of a YAML Map.");
      YAML::Node class_node = it->operator[](CLASS);
      YAML::Node scope_node = it->operator[](SCOPE);
      YAML::Node init_with_node = it->operator[](INIT_WITH);

      validate(class_node.IsScalar(), this_func_name, "Unexpected class_node, expected to be of YAML type Scalar.");
      validate(scope_node.IsScalar(), this_func_name, "Unexpected scope_node, expected to be of YAML type Scalar.");
      validate(init_with_node.IsScalar(), this_func_name, "Unexpected init_with_node, expected to be of YAML type Scalar.");

      Blast::Cpp::ParentClassProperties parent_class_properties(class_node.as<std::string>(), init_with_node.as<std::string>(), scope_node.as<std::string>());

      result.push_back(parent_class_properties);
   }

   return result;
}



std::vector<Blast::Cpp::ClassAttributeProperties> extract_attribute_properties(YAML::Node &source)
{
   std::vector<Blast::Cpp::ClassAttributeProperties> result;
   return result;
}



std::vector<Blast::Cpp::Function> extract_functions(YAML::Node &source)
{
   std::vector<Blast::Cpp::Function> result;
   return result;
}



std::vector<Blast::Cpp::SymbolDependencies> extract_symbol_dependencies(YAML::Node &source)
{
   std::string this_func_name = "extract_symbol_dependencies";
   const std::string DEPENDENCIES = "dependencies";
   std::vector<Blast::Cpp::SymbolDependencies> result;

   YAML::Node source_symbol_dependencies = source[DEPENDENCIES];

   validate(source_symbol_dependencies.IsSequence(), this_func_name, "Expected \"dependencies\" to be of a YAML Sequence type.");

   for (YAML::const_iterator it=source_symbol_dependencies.begin(); it!=source_symbol_dependencies.end(); ++it)
   {
      const std::string SYMBOL = "symbol";
      const std::string HEADERS = "headers";
      const std::string INCLUDE_DIRECTORIES = "include_directories";
      const std::string LINKED_LIBRARIES = "linked_libraries";

      validate(it->IsMap(), this_func_name, "Unexpected sequence element in \"parent_classes\", expected to be of a YAML Map.");
      YAML::Node symbol_node = it->operator[](SYMBOL);
      YAML::Node headers_node = it->operator[](HEADERS);
      YAML::Node include_directories_node = it->operator[](INCLUDE_DIRECTORIES);
      YAML::Node linked_libraries_node = it->operator[](LINKED_LIBRARIES);

      validate(symbol_node.IsScalar(), this_func_name, "Unexpected symbol_node, expected to be of YAML type Scalar.");
      validate(headers_node.IsSequence(), this_func_name, "Unexpected headers_node, expected to be of YAML type Sequence.");
      validate(include_directories_node.IsSequence(), this_func_name, "Unexpected include_directories_node, expected to be of YAML type Sequence.");
      validate(linked_libraries_node.IsSequence(), this_func_name, "Unexpected linked_libraries_node, expected to be of YAML type Sequence.");

      std::string symbol = symbol_node.as<std::string>();
      std::vector<std::string> headers = extract_sequence_as_string_array(headers_node);
      std::vector<std::string> include_directories = extract_sequence_as_string_array(include_directories_node);
      std::vector<std::string> linked_libraries = extract_sequence_as_string_array(linked_libraries_node);

      Blast::Cpp::SymbolDependencies symbol_dependencies(symbol, headers, include_directories, linked_libraries);

      result.push_back(symbol_dependencies);
   }

   return result;
}



std::vector<Blast::Cpp::SymbolDependencies> extract_function_body_symbol_dependencies(YAML::Node &source)
{
   std::vector<Blast::Cpp::SymbolDependencies> result;
   return result;
}



Blast::Cpp::Class convert_yaml_to_class(std::string class_name, YAML::Node &source)
{
   // declare variables

   std::vector<std::string> namespaces = extract_namespaces(source);
   std::vector<Blast::Cpp::ParentClassProperties> parent_classes_properties = extract_parent_classes_properties(source);
   std::vector<Blast::Cpp::ClassAttributeProperties> attribute_properties = extract_attribute_properties(source);
   std::vector<Blast::Cpp::Function> functions = extract_functions(source);
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = extract_symbol_dependencies(source);
   std::vector<Blast::Cpp::SymbolDependencies> function_body_symbol_dependencies = extract_function_body_symbol_dependencies(source);


   // build the actual class

   Blast::Cpp::Class klass(class_name, namespaces, parent_classes_properties, attribute_properties, functions, symbol_dependencies, function_body_symbol_dependencies);

   return klass;
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


      // infer the class name from the filename

      QuintessenceClassNameFromYAMLFilenameInferer class_name_inferer(argv[i]);
      std::string class_name = class_name_inferer.infer_class_name();


      // convert the yaml structure to the class

      Blast::Cpp::Class klass = convert_yaml_to_class(class_name, source);


      //// generate and write the files

      Blast::Cpp::ClassGenerator cpp_class_generator(klass);
      write_to_files(cpp_class_generator);
   }

   return 0;
}



