


#include <Blast/Cpp/ClassGenerator.hpp>
#include <Blast/Cpp/Function.hpp>
#include <Blast/Cpp/FunctionArgument.hpp>
#include <Blast/DirectoryCreator.hpp>
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


class QuintessenceNamespacesFromYAMLFilenameInferer
{
private:
   std::string yaml_filename;

public:
   QuintessenceNamespacesFromYAMLFilenameInferer(std::string yaml_filename)
      : yaml_filename(yaml_filename)
   {}

   std::vector<std::string> infer_namespaces()
   {
      std::vector<std::string> tokens = Blast::StringSplitter(yaml_filename, '/').split();
      if (tokens.size() <= 1) throw std::runtime_error("Can't parse tokens as expected from the filename.  Expecting a \"quintessence/**/Component.q.yml\" type filename.");
      tokens.pop_back(); // remove the "Component.q.yml" element at the end
      tokens.erase(tokens.begin()); // remove first "quintessence" folder name element at the begining
      return tokens; // whatever is left is assumed to be valid TODO: consider validating the namespace naming convention
   }
};


std::string get_type_string(YAML::Node &node)
{
   switch (node.Type())
   {
   case YAML::NodeType::Null: return "Null"; break;
   case YAML::NodeType::Scalar: return "Scalar"; break;
   case YAML::NodeType::Sequence: return "Sequence"; break;
   case YAML::NodeType::Map: return "Map"; break;
   case YAML::NodeType::Undefined: return "Undefined"; break;
   }
   return "[NO_TYPE_DEFINED_ERROR]";
}



bool create_folders_for_file(std::string filepath)
{
   std::vector<std::string> directory_names = Blast::StringSplitter(filepath, '/').split();
   directory_names.pop_back();
   Blast::DirectoryCreator directory_creator(directory_names);
   if (!directory_creator.create())
   {
      std::stringstream error_message;
      error_message << "Could not create folders for \"" << filepath << "\".";
      explode("create_folders_for_file", error_message.str());
   }
   return true;
}


void write_to_files(Blast::Cpp::ClassGenerator &cpp_class_generator, bool automatically_create_folders=true)
{
   std::string header_filepath = cpp_class_generator.project_header_filepath();
   std::string source_filepath = cpp_class_generator.project_source_filepath();

   std::ofstream header_file;
   header_file.open(header_filepath, std::ofstream::out);
   if (header_file.fail())
   {
      if (!automatically_create_folders)
      {
         std::stringstream error_message;
         error_message << "Could not open header file \"" << header_filepath << "\" for writing.  Most likely the directories need to be created.";
         explode("write_to_files", error_message.str());
      }
      create_folders_for_file(header_filepath);

      header_file.open(header_filepath, std::ofstream::out);
      if (header_file.fail())
      {
         std::stringstream error_message;
         error_message << "Could not open header file \"" << header_filepath << "\" for writing on a second attempt after (possibly) creating the necessary folders.";
         explode("write_to_files", error_message.str());
      }
   }

   std::ofstream source_file;
   source_file.open(source_filepath, std::ofstream::out);
   if (source_file.fail())
   {
      if (!automatically_create_folders)
      {
         std::stringstream error_message;
         error_message << "Could not open source file \"" << source_filepath << "\" for writing.  Most likely the directories need to be created.";
         explode("write_to_files", error_message.str());
      }
      create_folders_for_file(source_filepath);

      source_file.open(source_filepath, std::ofstream::out);
      if (source_file.fail())
      {
         std::stringstream error_message;
         error_message << "Could not open source file \"" << source_filepath << "\" for writing on a second attempt after (possibly) creating the necessary folders.";
         explode("write_to_files", error_message.str());
      }
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



YAML::Node default_dependencies()
{
   std::string default_deps = R"END(
- symbol: int
- symbol: void
- symbol: float
- symbol: double
- symbol: bool
- symbol: std::string
  headers: [ 'string' ]
- symbol: std::vector<std::string>
  headers: [ 'vector', 'string' ]
- symbol: std::cout
  headers: [ 'iostream' ]
- symbol: std::endl
  headers: [ 'iostream' ]
- symbol: std::stringstream
  headers: [ 'sstream' ]
   )END";

   return YAML::Load(default_deps);
}



bool fetch_bool(YAML::Node &node, std::string key, bool default_value)
{
   if (node[key])
   {
      if (node[key].IsScalar()) return node[key].as<bool>();
      else
      {
         std::stringstream error_message;
         error_message << "unexpected type expecting YAML::IsScalar() " << get_type_string(node) << " is present.";
         throw std::runtime_error(error_message.str());
      }
   }
   return default_value;
}



std::string fetch_string(YAML::Node &node, std::string key, std::string default_value)
{
   if (node[key])
   {
      if (node[key].IsScalar()) return node[key].as<std::string>();
      else
      {
         std::stringstream error_message;
         error_message << "unexpected type for key \"" << key << "\", expecting YAML::IsScalar() " << get_type_string(node) << " is present.";
         throw std::runtime_error(error_message.str());
      }
   }
   return default_value;
}



YAML::Node fetch_node(YAML::Node &node, std::string key, YAML::NodeType::value expected_type, YAML::Node default_value)
{
   if (node[key])
   {
      if (node[key].Type() == expected_type) return node[key];
      else
      {
         std::stringstream error_message;
         error_message << "unexpected type expecting YAML:: " << expected_type << ", is a " << get_type_string(node) << " is present.";
         throw std::runtime_error(error_message.str());
      }
   }
   return default_value;
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
   const std::string NAMESPACES = "namespaces";
   YAML::Node result = fetch_node(source, NAMESPACES, YAML::NodeType::Sequence, YAML::Load("[]"));
   return extract_sequence_as_string_array(result);
}



std::vector<std::string> extract_namespaces_from_quintessence_filename(std::string file_path)
{
   QuintessenceNamespacesFromYAMLFilenameInferer inferer(file_path);
   return inferer.infer_namespaces();
   //const std::string NAMESPACES = "namespaces";
   //YAML::Node result = fetch_node(source, NAMESPACES, YAML::NodeType::Sequence, YAML::Load("[]"));
   //return extract_sequence_as_string_array(result);
}



class ParentClassPropertiesExtractor
{
private:
   YAML::Node &source;
   std::string this_component_name;
   std::vector<std::tuple<std::string, YAML::NodeType::value, bool, std::string, std::string>> schema;

public:
   ParentClassPropertiesExtractor(YAML::Node &source)
      : source(source)
      , this_component_name("ParentClassPropertiesExtractor")
      , schema({
       //{ name,        type,                   required, default,        description },
          { "class",     YAML::NodeType::Scalar, true,     "UnnamedClass", "(description)"},
          { "scope",     YAML::NodeType::Scalar, false,    "public",       "(description)"},
          { "init_with", YAML::NodeType::Scalar, false,    "{}",           "(description)"},
        })
   {}
   ~ParentClassPropertiesExtractor() {}

   std::vector<std::string> required_elements_from_schema()
   {
      std::vector<std::string> result = {};
      for (auto &schema_element : schema)
      {
         bool schema_element_requirement = std::get<2>(schema_element);

         if (schema_element_requirement)
         {
            std::string schema_element_name = std::get<0>(schema_element);
            result.push_back(schema_element_name);
         }
      }
      return result;
   }

   std::vector<Blast::Cpp::ParentClassProperties> extract()
   {
      std::vector<Blast::Cpp::ParentClassProperties> result;
      validate(source.IsSequence(), this_component_name, "Expected \"parent_classes\" to be of a YAML Sequence type.");


      YAML::NodeType::value t = YAML::NodeType::Scalar;

      const std::string CLASS = "class";
      const std::string SCOPE = "scope";
      const std::string INIT_WITH = "init_with";

      //const std::vector<std::tuple<std::string, YAML::NodeType::value, bool, std::string, std::string>> schema = {
       ////{ name,        type,                   required, default,        description },
         //{ "class",     YAML::NodeType::Scalar, true,     "UnnamedClass", "(description)"},
         //{ "scope",     YAML::NodeType::Scalar, false,    "public",       "(description)"},
         //{ "init_with", YAML::NodeType::Scalar, false,    "{}",           "(description)"},
      //};



      /// good:

      // extract "required_elements" from schema:
      std::vector<std::string> required_elements = {};
      for (auto &schema_element : schema)
      {
         std::string schema_element_name = std::get<0>(schema_element);
         bool schema_element_requirement = std::get<2>(schema_element);

         if (schema_element_requirement) required_elements.push_back(schema_element_name);
      }


      required_elements = { CLASS };
      std::vector<std::string> optional_elements = { SCOPE, INIT_WITH };
      std::vector<std::string> known_elements = required_elements;
         known_elements.insert(known_elements.end(), optional_elements.begin(), optional_elements.end());

      std::vector<std::string> present_elements = {};


      // validate required elements are present
      std::vector<std::string> missing_required_elements = required_elements;
      for (auto &required_element : required_elements)
      {

      }


      // not going to implement for now: notify missing optional elements


      // raise unknown elements


      // validate present elements are of valid type



      for (YAML::const_iterator it=source.begin(); it!=source.end(); ++it)
      {
         validate(it->IsMap(), this_component_name, "Unexpected sequence element in \"parent_classes\", expected to be of a YAML Map.");
         YAML::Node class_node = it->operator[](CLASS);
         YAML::Node scope_node = it->operator[](SCOPE);
         YAML::Node init_with_node = it->operator[](INIT_WITH);

         validate(class_node.IsScalar(), this_component_name, "Unexpected class_node, expected to be of YAML type Scalar.");
         validate(scope_node.IsScalar(), this_component_name, "Unexpected scope_node, expected to be of YAML type Scalar.");
         validate(init_with_node.IsScalar(), this_component_name, "Unexpected init_with_node, expected to be of YAML type Scalar.");

         Blast::Cpp::ParentClassProperties parent_class_properties(class_node.as<std::string>(), init_with_node.as<std::string>(), scope_node.as<std::string>());

         result.push_back(parent_class_properties);
      }

      return result;
   }
};



std::vector<Blast::Cpp::ParentClassProperties> extract_parent_classes_properties(YAML::Node &source)
{
   std::string this_func_name = "extract_parent_classes_properties";

   const std::string PARENT_CLASSES = "parent_classes";

   YAML::Node source_parent_classes = fetch_node(source, PARENT_CLASSES, YAML::NodeType::Sequence, YAML::Load("[]"));

   ParentClassPropertiesExtractor extractor(source_parent_classes);
   return extractor.extract();
}



std::vector<Blast::Cpp::ClassAttributeProperties> extract_attribute_properties(YAML::Node &source)
{
   std::string this_func_name = "extract_attribute_properties";
   const std::string PROPERTIES = "properties";
   std::vector<Blast::Cpp::ClassAttributeProperties> result;

   YAML::Node source_attribute_properties = fetch_node(source, PROPERTIES, YAML::NodeType::Sequence, YAML::Load("[]"));

   validate(source_attribute_properties.IsSequence(), this_func_name, "Expected \"properties\" to be of a YAML Sequence type.");

   for (std::size_t i=0;i<source_attribute_properties.size();i++)
   {
      YAML::Node it = source_attribute_properties[i];

      const std::string TYPE = "type";
      const std::string NAME = "name";
      const std::string INIT_WITH = "init_with";
      const std::string CONSTRUCTOR_ARG = "constructor_arg";
      const std::string STATIC = "static";
      const std::string GETTER = "getter";
      const std::string GETTER_REF = "getter_ref";
      const std::string SETTER = "setter";

      validate(it.IsMap(), this_func_name, "Unexpected sequence element in \"properties\", expected to be of a YAML Map.");

      YAML::Node type_node = it.operator[](TYPE);
      YAML::Node name_node = it.operator[](NAME);
      YAML::Node init_with_node = it.operator[](INIT_WITH);
      //YAML::Node constructor_arg_node = it.operator[](CONSTRUCTOR_ARG);
      //YAML::Node static_node = it.operator[](STATIC);
      //YAML::Node getter_node = it.operator[](GETTER);
      //YAML::Node setter_node = it.operator[](SETTER);

      //validate(type_node.IsScalar(), this_func_name, "Unexpected type_node, expected to be of YAML type Scalar.");
      validate(name_node.IsScalar(), this_func_name, "Unexpected name_node, expected to be of YAML type Scalar.");
      //validate(init_with_node.IsScalar(), this_func_name, "Unexpected init_with_node, expected to be of YAML type Scalar.");
      //validate(constructor_arg_node.IsScalar(), this_func_name, "Unexpected constructor_arg_node, expected to be of YAML type Scalar.");
      //validate(static_node.IsScalar(), this_func_name, "Unexpected static_node, expected to be of YAML type Scalar.");
      //validate(getter_node.IsScalar(), this_func_name, "Unexpected getter_node, expected to be of YAML type Scalar.");
      //validate(setter_node.IsScalar(), this_func_name, "Unexpected setter_node, expected to be of YAML type Scalar.");

      std::string datatype = fetch_string(it, TYPE, "std::string");
      std::string variable_name = name_node.as<std::string>();
      std::string initialization_value = fetch_string(it, INIT_WITH, "\"\"");
      bool is_static = fetch_bool(it, STATIC, false);
      bool is_constructor_parameter = fetch_bool(it, CONSTRUCTOR_ARG, false);
      bool has_getter = fetch_bool(it, GETTER, false);
      bool has_getter_ref = fetch_bool(it, GETTER_REF, false);
      bool has_setter = fetch_bool(it, SETTER, false);
      //std::string initialization_value = init_with_node.as<std::string>();
      //bool is_static = static_node.as<bool>();
      //bool is_constructor_parameter = constructor_arg_node.as<bool>();
      //bool has_getter = getter_node.as<bool>();
      //bool has_getter_ref = false;
      //bool has_setter = setter_node.as<bool>();

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

   for (std::size_t i=0;i<source.size();i++)
   //for (YAML::const_iterator it=source.begin(); it!=source.end(); ++it)
   {
      YAML::Node node = source[i];

      const std::string TYPE = "type";
      const std::string NAME = "name";
      const std::string DEFAULT_ARGUMENT = "default_argument";

      validate(node.IsMap(), this_func_name, "Unexpected sequence element in \"parameters\", expected to be of a YAML Map.");

      YAML::Node type_node = node.operator[](TYPE);
      YAML::Node name_node = node.operator[](NAME);
      YAML::Node default_argument_node = node.operator[](DEFAULT_ARGUMENT);

      validate(type_node.IsScalar(), this_func_name, "Unexpected type_node, expected to be of YAML type Scalar.");
      validate(name_node.IsScalar(), this_func_name, "Unexpected name_node, expected to be of YAML type Scalar.");
      validate(default_argument_node.IsScalar(), this_func_name, "Unexpected default_argument_node, expected to be of YAML type Scalar.");

      Blast::Cpp::FunctionArgument function_argument(type_node.as<std::string>(), name_node.as<std::string>(), default_argument_node.as<std::string>());

      result.push_back(function_argument);
   }

   return result;
}


std::vector<std::string> extract_function_dependency_symbols(YAML::Node &source)
{
   const std::string DEPENDENCY_SYMBOLS = "body_dependency_symbols";
   std::vector<std::string> result;

   YAML::Node dependency_symbols = fetch_node(source, DEPENDENCY_SYMBOLS, YAML::NodeType::Sequence, YAML::Load("[]"));

   result = extract_sequence_as_string_array(dependency_symbols);

   return result;
}



std::vector<std::pair<Blast::Cpp::Function, std::vector<std::string>>> extract_functions(YAML::Node &source)
{
   std::string this_func_name = "extract_functions";
   const std::string FUNCTIONS = "functions";
   std::vector<std::pair<Blast::Cpp::Function, std::vector<std::string>>> result;

   YAML::Node source_functions = fetch_node(source, FUNCTIONS, YAML::NodeType::Sequence, YAML::Load("[]"));

   for (std::size_t i=0; i<source_functions.size(); i++)
   //for (YAML::const_iterator it=source_functions.begin(); it!=source_functions.end(); ++it)
   {
      YAML::Node it = source_functions[i];

      const std::string TYPE = "type";
      const std::string NAME = "name";
      const std::string PARAMETERS = "parameters";
      const std::string BODY = "body";
      const std::string STATIC = "static";
      const std::string CONST = "const";
      const std::string OVERRIDE = "override";
      const std::string VIRTUAL = "virtual";
      const std::string PURE_VIRTUAL = "pure_virtual";
      //const std::string DEPENDENCY_SYMBOLS = "dependency_symbols";

      validate(it.IsMap(), this_func_name, "Unexpected sequence element in \"functions\", expected to be of a YAML Map.");

      //YAML::Node type_node = it.operator[](TYPE);
      YAML::Node name_node = it.operator[](NAME);
      YAML::Node parameters_node = fetch_node(it, PARAMETERS, YAML::NodeType::Sequence, YAML::Load("[]"));
        // TODO it's happening here somewhere::
      //YAML::Node dependency_symbols_node = fetch_node(it, DEPENDENCY_SYMBOLS, YAML::NodeType::Sequence, YAML::Load("[]"));
      YAML::Node body_node = it.operator[](BODY);
      //YAML::Node dependency_symbols_node = fetch_node(it, DEPENDENCY_SYMBOLS, YAML::NodeType::Sequence, YAML::Load("[]"));

      //validate(type_node.IsScalar(), this_func_name, "Unexpected type for node \"type\", expected to be of YAML type Scalar.");
      validate(name_node.IsScalar(), this_func_name, "Unexpected type for node \"name\", expected to be of YAML type Scalar.");
      //validate(parameters_node.IsSequence(), this_func_name, "Unexpected parameters_node, expected to be of YAML type Sequence.");
      validate(body_node.IsScalar(), this_func_name, "Unexpected type for node \"body\", expected to be of YAML type Scalar.");
      //validate(body_node.IsScalar(), this_func_name, "Unexpected type for node \"dependency_symbols\", expected to be of YAML type Scalar.");

      std::string type = fetch_string(it, TYPE, "void");
      std::string name = name_node.as<std::string>();
      std::vector<Blast::Cpp::FunctionArgument> signature = convert_function_arguments(parameters_node);
      std::string body = body_node.as<std::string>();
      bool is_static = fetch_bool(it, STATIC, false);
      bool is_const = fetch_bool(it, CONST, false);
      bool is_override = fetch_bool(it, OVERRIDE, false);
      bool is_virtual = fetch_bool(it, VIRTUAL, false);
      bool is_pure_virtual = fetch_bool(it, PURE_VIRTUAL, false);

      Blast::Cpp::Function function(type, name, signature, body, is_static, is_const, is_override, is_virtual, is_pure_virtual);

      std::vector<std::string> dependency_symbols = extract_function_dependency_symbols(it);

      result.push_back({function, dependency_symbols});
   }

   return result;
}



std::vector<Blast::Cpp::SymbolDependencies> extract_symbol_dependencies(YAML::Node &source)
{
   std::string this_func_name = "extract_symbol_dependencies";
   const std::string DEPENDENCIES = "dependencies";
   std::vector<Blast::Cpp::SymbolDependencies> result;

   YAML::Node source_symbol_dependencies = fetch_node(source, DEPENDENCIES, YAML::NodeType::Sequence, YAML::Load("[]"));
   YAML::Node default_deps = default_dependencies();

   // postfix default deps
   for (std::size_t i=0;i<default_deps.size();i++)
   {
      source_symbol_dependencies.push_back(default_deps[i]);
   }

   validate(source_symbol_dependencies.IsSequence(), this_func_name, "Expected \"dependencies\" to be of a YAML Sequence type.");

   for (std::size_t i=0;i<source_symbol_dependencies.size();i++)
   //for (YAML::const_iterator it=source_symbol_dependencies.begin(); it!=source_symbol_dependencies.end(); ++it)
   {
      YAML::Node node = source_symbol_dependencies[i];

      const std::string SYMBOL = "symbol";
      const std::string HEADERS = "headers";
      const std::string INCLUDE_DIRECTORIES = "include_directories";
      const std::string LINKED_LIBRARIES = "linked_libraries";

      validate(node.IsMap(), this_func_name, "Unexpected sequence element in \"parent_classes\", expected to be of a YAML Map.");
      YAML::Node symbol_node = node[SYMBOL];//it->operator[](SYMBOL);
      //YAML::Node headers_node = node[HEADERS];//it->operator[](HEADERS);
      //YAML::Node include_directories_node = it->operator[](INCLUDE_DIRECTORIES);
      //YAML::Node linked_libraries_node = it->operator[](LINKED_LIBRARIES);

      validate(symbol_node.IsScalar(), this_func_name, "Unexpected symbol_node, expected to be of YAML type Scalar.");
      //validate(headers_node.IsSequence(), this_func_name, "Unexpected headers_node, expected to be of YAML type Sequence.");
      //validate(include_directories_node.IsSequence(), this_func_name, "Unexpected include_directories_node, expected to be of YAML type Sequence.");

      YAML::Node headers_node = fetch_node(node, HEADERS, YAML::NodeType::Sequence, YAML::Load("[]"));
      YAML::Node include_directories_node = fetch_node(node, INCLUDE_DIRECTORIES, YAML::NodeType::Sequence, YAML::Load("[]"));
      YAML::Node linked_libraries_node = fetch_node(node, LINKED_LIBRARIES, YAML::NodeType::Sequence, YAML::Load("[]"));
      //validate(linked_libraries_node.IsSequence(), this_func_name, "Unexpected linked_libraries_node, expected to be of YAML type Sequence.");

      std::string symbol = symbol_node.as<std::string>();
      std::vector<std::string> headers = extract_sequence_as_string_array(headers_node);
      std::vector<std::string> include_directories = extract_sequence_as_string_array(include_directories_node);
      std::vector<std::string> linked_libraries = extract_sequence_as_string_array(linked_libraries_node);

      Blast::Cpp::SymbolDependencies symbol_dependencies(symbol, headers, include_directories, linked_libraries);

      result.push_back(symbol_dependencies);
   }

   return result;
}



std::vector<std::string> extract_function_body_symbol_dependency_symbols(YAML::Node &source)
{
   const std::string DEPENDENCIES = "function_body_symbol_dependencies";
   std::vector<std::string> result;

   YAML::Node function_body_symbol_dependencies = fetch_node(source, DEPENDENCIES, YAML::NodeType::Sequence, YAML::Load("[]"));

   return extract_sequence_as_string_array(function_body_symbol_dependencies);
}



std::vector<Blast::Cpp::SymbolDependencies> consolidate_function_body_symbol_dependencies(std::vector<std::string> dependency_symbols, std::vector<Blast::Cpp::SymbolDependencies> &known_listed_dependencies)
{
   std::vector<Blast::Cpp::SymbolDependencies> result;

   for (auto &dependency_symbol : dependency_symbols)
   {
      bool found = false;
      for (auto &known_listed_dependency : known_listed_dependencies)
      {
         if (known_listed_dependency.get_symbol() == dependency_symbol)
         {
            result.push_back(known_listed_dependency);
            found = true;
            break;
         }
      }
      if (!found)
      {
         std::stringstream error_message;
         error_message << "Could not find " << dependency_symbol << " dependency from dependency_symbols";
         explode("consolidate_function_body_symbol_dependencies", error_message.str());
      }
   }

   return result;
}



Blast::Cpp::Class convert_yaml_to_class(std::string class_name, YAML::Node &source, std::string quintessence_filename)
{
   // declare variables

   std::vector<std::string> namespaces = extract_namespaces_from_quintessence_filename(quintessence_filename);
   std::vector<Blast::Cpp::ParentClassProperties> parent_classes_properties = extract_parent_classes_properties(source);
   std::vector<Blast::Cpp::ClassAttributeProperties> attribute_properties = extract_attribute_properties(source);
   std::vector<std::pair<Blast::Cpp::Function, std::vector<std::string>>> functions_and_dependencies = extract_functions(source);
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = extract_symbol_dependencies(source);
   std::vector<std::string> function_body_symbol_dependency_symbols = extract_function_body_symbol_dependency_symbols(source);

   
   // consolidate functions and their dependencies

   std::vector<Blast::Cpp::Function> functions = {};
   std::vector<std::string> per_function_dependency_symbols = {};
   for (auto &function_and_dependency : functions_and_dependencies)
   {
      functions.push_back(function_and_dependency.first);
      for (auto &dependency_symbol : function_and_dependency.second)
      {
         per_function_dependency_symbols.push_back(dependency_symbol);
      }
   }


   // consolidate dependencies

   std::vector<std::string> function_body_symbol_dependencies__and__per_function_dependency_symbols = {};
   function_body_symbol_dependencies__and__per_function_dependency_symbols = function_body_symbol_dependency_symbols;
   for (auto &per_function_dependency_symbol : per_function_dependency_symbols)
   {
      function_body_symbol_dependencies__and__per_function_dependency_symbols.push_back(per_function_dependency_symbol);
   }



   std::vector<Blast::Cpp::SymbolDependencies> function_body_symbol_dependencies = consolidate_function_body_symbol_dependencies(
         function_body_symbol_dependencies__and__per_function_dependency_symbols,
         symbol_dependencies
      );


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
      std::cout << "Initiating fetching, loading, and parsing of component file \"" << quintessence_filename << "\"" << std::endl;
      YAML::Node source = YAML::LoadFile(quintessence_filename);


      // infer the class name from the filename

      QuintessenceClassNameFromYAMLFilenameInferer class_name_inferer(argv[i]);
      std::string class_name = class_name_inferer.infer_class_name();


      // convert the yaml structure to the class

      Blast::Cpp::Class klass = convert_yaml_to_class(class_name, source, quintessence_filename);


      //// generate and write the files

      Blast::Cpp::ClassGenerator cpp_class_generator(klass);
      write_to_files(cpp_class_generator);
   }

   return 0;
}



