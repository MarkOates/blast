


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



std::vector<std::string> extract_namespaces(YAML::Node &source)
{
   std::string this_func_name = "extract_namespaces";
   const std::string NAMESPACES = "namespaces";
   std::vector<std::string> result;

   YAML::Node source_namespaces = source[NAMESPACES];

   validate(source_namespaces.IsSequence(), this_func_name, "Expected \"namespaces\" to be of a YAML Sequence type.");

   for (YAML::const_iterator it=source_namespaces.begin(); it!=source_namespaces.end(); ++it)
   {
      validate(it->IsScalar(), this_func_name, "Unexpected sequence element in \"namespaces\", expected to be of a YAML Scalar.");
      result.push_back(it->as<std::string>());
   }

   return result;
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
   std::vector<Blast::Cpp::SymbolDependencies> result;
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



