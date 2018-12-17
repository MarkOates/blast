


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
   std::string this_func_name = "extract_attribute_properties";
   const std::string PROPERTIES = "properties";
   std::vector<Blast::Cpp::ClassAttributeProperties> result;

   YAML::Node source_attribute_properties = source[PROPERTIES];

   validate(source_attribute_properties.IsSequence(), this_func_name, "Expected \"properties\" to be of a YAML Sequence type.");

   for (YAML::const_iterator it=source_attribute_properties.begin(); it!=source_attribute_properties.end(); ++it)
   {
      const std::string TYPE = "type";
      const std::string NAME = "name";
      const std::string INIT_WITH = "init_with";
      const std::string CONSTRUCTOR_ARG = "constructor_arg";
      const std::string STATIC = "static";
      const std::string GETTER = "getter";
      const std::string SETTER = "setter";

      validate(it->IsMap(), this_func_name, "Unexpected sequence element in \"properties\", expected to be of a YAML Map.");

      YAML::Node type_node = it->operator[](TYPE);
      YAML::Node name_node = it->operator[](NAME);
      YAML::Node init_with_node = it->operator[](INIT_WITH);
      YAML::Node constructor_arg_node = it->operator[](CONSTRUCTOR_ARG);
      YAML::Node static_node = it->operator[](STATIC);
      YAML::Node getter_node = it->operator[](GETTER);
      YAML::Node setter_node = it->operator[](SETTER);

      validate(type_node.IsScalar(), this_func_name, "Unexpected type_node, expected to be of YAML type Scalar.");
      validate(name_node.IsScalar(), this_func_name, "Unexpected name_node, expected to be of YAML type Scalar.");
      validate(init_with_node.IsScalar(), this_func_name, "Unexpected init_with_node, expected to be of YAML type Scalar.");
      validate(constructor_arg_node.IsScalar(), this_func_name, "Unexpected constructor_arg_node, expected to be of YAML type Scalar.");
      validate(static_node.IsScalar(), this_func_name, "Unexpected static_node, expected to be of YAML type Scalar.");
      validate(getter_node.IsScalar(), this_func_name, "Unexpected getter_node, expected to be of YAML type Scalar.");
      validate(setter_node.IsScalar(), this_func_name, "Unexpected setter_node, expected to be of YAML type Scalar.");

      std::string datatype = type_node.as<std::string>();
      std::string variable_name = name_node.as<std::string>();
      std::string initialization_value = init_with_node.as<std::string>();
      bool is_static = static_node.as<bool>();
      bool is_constructor_parameter = constructor_arg_node.as<bool>();
      bool has_getter = getter_node.as<bool>();
      bool has_getter_ref = false;
      bool has_setter = setter_node.as<bool>();

      Blast::Cpp::ClassAttributeProperties class_attribute_properties(datatype, variable_name, initialization_value, is_static, is_constructor_parameter, has_getter, has_getter_ref, has_setter);

      result.push_back(class_attribute_properties);
   }

   return result;
}


std::vector<Blast::Cpp::FunctionArgument> convert_function_arguments(YAML::Node &source)
{
   std::string this_func_name = "convert_function_arguments";
   //const std::string PARAMETERS = "parameters";
   std::vector<Blast::Cpp::FunctionArgument> result;

   //YAML::Node source_function_arguments = source[PARAMETERS];

   validate(source.IsSequence(), this_func_name, "Expected \"parameters\" to be of a YAML Sequence type.");

   for (YAML::const_iterator it=source.begin(); it!=source.end(); ++it)
   {
      const std::string TYPE = "type";
      const std::string NAME = "name";
      const std::string DEFAULT_ARGUMENT = "default_argument";

      validate(it->IsMap(), this_func_name, "Unexpected sequence element in \"parameters\", expected to be of a YAML Map.");

      YAML::Node type_node = it->operator[](TYPE);
      YAML::Node name_node = it->operator[](NAME);
      YAML::Node default_argument_node = it->operator[](DEFAULT_ARGUMENT);

      validate(type_node.IsScalar(), this_func_name, "Unexpected type_node, expected to be of YAML type Scalar.");
      validate(name_node.IsScalar(), this_func_name, "Unexpected name_node, expected to be of YAML type Scalar.");
      validate(default_argument_node.IsScalar(), this_func_name, "Unexpected default_argument_node, expected to be of YAML type Scalar.");

      Blast::Cpp::FunctionArgument function_argument(type_node.as<std::string>(), name_node.as<std::string>(), default_argument_node.as<std::string>());

      result.push_back(function_argument);
   }

   return result;
}


std::vector<Blast::Cpp::Function> extract_functions(YAML::Node &source)
{
   std::string this_func_name = "extract_functions";
   const std::string FUNCTIONS = "functions";
   std::vector<Blast::Cpp::Function> result;

   YAML::Node source_functions = source[FUNCTIONS];

   validate(source_functions.IsSequence(), this_func_name, "Expected \"functions\" to be of a YAML Sequence type.");

   for (YAML::const_iterator it=source_functions.begin(); it!=source_functions.end(); ++it)
   {
      const std::string TYPE = "type";
      const std::string NAME = "name";
      const std::string PARAMETERS = "parameters";
      const std::string BODY = "body";
      const std::string STATIC = "static";
      const std::string CONST = "const";
      const std::string OVERRIDE = "override";

      validate(it->IsMap(), this_func_name, "Unexpected sequence element in \"functions\", expected to be of a YAML Map.");

      YAML::Node type_node = it->operator[](TYPE);
      YAML::Node name_node = it->operator[](NAME);
      YAML::Node parameters_node = it->operator[](PARAMETERS);
      YAML::Node body_node = it->operator[](BODY);
      YAML::Node static_node = it->operator[](STATIC);
      YAML::Node const_node = it->operator[](CONST);
      YAML::Node override_node = it->operator[](OVERRIDE);

      validate(type_node.IsScalar(), this_func_name, "Unexpected type_node, expected to be of YAML type Scalar.");
      validate(name_node.IsScalar(), this_func_name, "Unexpected name_node, expected to be of YAML type Scalar.");
      validate(parameters_node.IsSequence(), this_func_name, "Unexpected parameters_node, expected to be of YAML type Scalar.");
      validate(body_node.IsScalar(), this_func_name, "Unexpected body_node, expected to be of YAML type Scalar.");
      validate(static_node.IsScalar(), this_func_name, "Unexpected static_node, expected to be of YAML type Scalar.");
      validate(const_node.IsScalar(), this_func_name, "Unexpected const_node, expected to be of YAML type Scalar.");
      validate(override_node.IsScalar(), this_func_name, "Unexpected override_node, expected to be of YAML type Scalar.");

      std::string type = type_node.as<std::string>();
      std::string name = name_node.as<std::string>();
      std::vector<Blast::Cpp::FunctionArgument> signature = convert_function_arguments(parameters_node);
      std::string body = body_node.as<std::string>();
      bool is_static = static_node.as<bool>();
      bool is_const = const_node.as<bool>();
      bool is_override = override_node.as<bool>();

      Blast::Cpp::Function function(type, name, signature, body, is_static, is_const, is_override);

      result.push_back(function);
   }

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



