

#include <allegro5/allegro.h> // needed to compile with union/Makefile

#include <Blast/Cpp/ClassGenerator.hpp>
#include <Blast/Cpp/Function.hpp>
#include <Blast/Cpp/FunctionArgument.hpp>
#include <Blast/DirectoryCreator.hpp>
#include <Blast/CommandLineFlaggedArgumentsParser.hpp>
#include <Blast/StringSplitter.hpp>
#include <Blast/YamlCppValidator.hpp>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>


bool verbose_output = true;



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



std::string __replace(std::string str, std::string from, std::string to)
{
   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
   return str;
}



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



std::vector<std::string> extract_function_body_dependency_symbols(YAML::Node &source)
{
   const std::string DEPENDENCY_SYMBOLS = "body_dependency_symbols";
   std::vector<std::string> result;

   YAML::Node dependency_symbols = fetch_node(source, DEPENDENCY_SYMBOLS, YAML::NodeType::Sequence, YAML::Load("[]"));

   result = extract_sequence_as_string_array(dependency_symbols);

   return result;
}



std::vector<std::string> extract_default_argument_dependency_symbols(YAML::Node &source)
{
   const std::string DEPENDENCY_SYMBOLS = "default_argument_dependency_symbols";
   std::vector<std::string> result;

   YAML::Node dependency_symbols = fetch_node(source, DEPENDENCY_SYMBOLS, YAML::NodeType::Sequence, YAML::Load("[]"));

   result = extract_sequence_as_string_array(dependency_symbols);

   return result;
}



#include <Blast/TemplatedFile.hpp>
class GuardCodeCreator
{
public:
   static std::string guard(std::string condition, std::string class_name, std::string function_name, std::string message)
   {
      std::string template_content = R"END(if (!({{CONDITION}}))
{
   std::stringstream error_message;
   error_message << "[{{CLASS_NAME}}::{{FUNCTION_NAME}}]: error: {{MESSAGE}}.";
   std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
   throw std::runtime_error("{{CLASS_NAME}}::{{FUNCTION_NAME}}: error: {{MESSAGE}}");
})END";

      std::vector<std::pair<std::string, std::string>> insertion_variables = {
         { "{{CONDITION}}", condition },
         { "{{CLASS_NAME}}", class_name },
         { "{{FUNCTION_NAME}}", function_name },
         { "{{MESSAGE}}", message },
      };

      Blast::TemplatedFile templated_file(template_content, insertion_variables);

      return templated_file.generate_content();
   }

   static std::vector<std::string> good_enough_for_now_guards_dependency_symbols()
   {
      return { "std::runtime_error", "std::stringstream", "std::cerr" };
   }

   static std::string generate_guards_code(std::vector<std::string> guard_conditionals, std::string class_name, std::string function_name)
   {
      std::string result;

      for (auto &guard_conditional : guard_conditionals)
      {
         std::string guard_message = std::string("guard \\\"") + guard_conditional + "\\\" not met";
         result += guard(guard_conditional, class_name, function_name, guard_message) + "\n";
      }

      return result;
   }

   
};



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



#include <Blast/FileContentComparisonChecker.hpp>


void write_to_files(Blast::Cpp::ClassGenerator &cpp_class_generator, bool automatically_create_folders=true)
{
   std::string header_filepath = cpp_class_generator.project_header_filepath();
   std::string source_filepath = cpp_class_generator.project_source_filepath();
   std::string header_file_content = cpp_class_generator.generate_header_file_content();
   std::string source_file_content = cpp_class_generator.generate_source_file_content();

   bool content_for_header_is_unchanged = false;
   bool content_for_source_is_unchanged = false;

   if (Blast::FileContentComparisonChecker(header_filepath, header_file_content).is_equal()) content_for_header_is_unchanged = true;
   if (Blast::FileContentComparisonChecker(source_filepath, source_file_content).is_equal()) content_for_source_is_unchanged = true;

   if (!content_for_header_is_unchanged)
   {
      std::ofstream header_file;
      header_file.open(header_filepath, std::ios::binary);
      if (header_file.fail())
      {
         if (!automatically_create_folders)
         {
            std::stringstream error_message;
            error_message << "Could not open header file \"" << header_filepath << "\" for writing.  Most likely the directories need to be created.";
            explode("write_to_files", error_message.str());
         }
         create_folders_for_file(header_filepath);

         header_file.open(header_filepath, std::ios::binary);
         if (header_file.fail())
         {
            std::stringstream error_message;
            error_message << "Could not open header file \"" << header_filepath << "\" for writing on a second attempt after (possibly) creating the necessary folders.";
            explode("write_to_files", error_message.str());
         }
      }

      header_file << header_file_content;
   }

   if (!content_for_source_is_unchanged)
   {
      std::ofstream source_file;
      source_file.open(source_filepath, std::ios::binary);
      if (source_file.fail())
      {
         if (!automatically_create_folders)
         {
            std::stringstream error_message;
            error_message << "Could not open source file \"" << source_filepath << "\" for writing.  Most likely the directories need to be created.";
            explode("write_to_files", error_message.str());
         }
         create_folders_for_file(source_filepath);

         source_file.open(source_filepath, std::ios::binary);
         if (source_file.fail())
         {
            std::stringstream error_message;
            error_message << "Could not open source file \"" << source_filepath << "\" for writing on a second attempt after (possibly) creating the necessary folders.";
            explode("write_to_files", error_message.str());
         }
      }

      source_file << source_file_content;
   }

   // output success
   if (content_for_header_is_unchanged && content_for_source_is_unchanged)
   {
      if (verbose_output) std::cout << "🔹 content is unchanged for \033[1m\033[32m" << header_filepath << " and " << source_filepath << "\033[0m" << std::endl;
   }
   else
   {
      std::cout << "✅ done. Files generated \033[1m\033[32m" << header_filepath << " and " << source_filepath << "\033[0m" << std::endl;
   }
}



YAML::Node default_dependencies()
{
// Consider Adding
// - symbol: std::count
//   headers: [ algorithm ]
// std::min: algorithm
// std::max: algorithm


   std::string default_deps = R"END(
- symbol: int
- symbol: intptr_t
- symbol: void
- symbol: float
- symbol: double
- symbol: bool
- symbol: char
- symbol: std::pair
  headers: [ 'utility' ]
- symbol: std::tuple
  headers: [ 'tuple' ]
- symbol: std::vector
  headers: [ 'vector' ]
- symbol: std::map
  headers: [ 'map' ]
- symbol: std::unordered_map
  headers: [ 'unordered_map' ]
- symbol: std::unordered_set
  headers: [ 'unordered_set' ]
- symbol: std::set
  headers: [ 'set' ]
- symbol: std::string
  headers: [ 'string' ]
- symbol: int32_t
  headers: [ 'cstdint' ]
- symbol: uint32_t
  headers: [ 'cstdint' ]
- symbol: std::cout
  headers: [ 'iostream' ]
- symbol: std::cerr
  headers: [ 'iostream' ]
- symbol: std::endl
  headers: [ 'iostream' ]
- symbol: std::runtime_error
  headers: [ 'stdexcept' ]
- symbol: std::stringstream
  headers: [ 'sstream' ]
- symbol: std::function
  headers: [ functional ]
- symbol: std::size_t
  headers: [ cstddef ]
- symbol: std::max
  headers: [ algorithm ]
- symbol: std::min
  headers: [ algorithm ]
   )END";

// The following have been removed now that dependency atomization is in effect:
//- symbol: std::vector<std::string>
  //headers: [ 'vector', 'string' ]
//- symbol: std::map<std::string, std::string>
  //headers: [ 'map', 'string' ]
//- symbol: std::map<int, std::string>
  //headers: [ 'map', 'string' ]
//- symbol: std::map<std::string, int>
  //headers: [ 'map', 'string' ]
//- symbol: std::vector<int>
  //headers: [ 'vector', ]
//- symbol: std::set<std::string>
  //headers: [ 'set', 'string', ]

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
        //{ name,        yaml-cpp type,          required, default,        description },
          { "class",     YAML::NodeType::Scalar, true,     "UnnamedClass", "(description)"},
          { "scope",     YAML::NodeType::Scalar, false,    "public",       "(description)"},
          { "init_with", YAML::NodeType::Scalar, false,    "{}",           "(description)"},
        })
   {}
   ~ParentClassPropertiesExtractor() {}

   std::vector<std::string> all_elements_from_schema()
   {
      std::vector<std::string> result = {};
      for (auto &schema_element : schema)
      {
         std::string schema_element_name = std::get<0>(schema_element);
         result.push_back(schema_element_name);
      }
      return result;
   }

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

   std::vector<std::string> optional_elements_from_schema()
   {
      std::vector<std::string> result = {};
      for (auto &schema_element : schema)
      {
         bool schema_element_requirement = std::get<2>(schema_element);

         if (!schema_element_requirement)
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


      //YAML::NodeType::value t = YAML::NodeType::Scalar;

      const std::string CLASS = "class";
      const std::string SCOPE = "scope";
      const std::string INIT_WITH = "init_with";



      /// good:

      // extract required, optional, and known elements from schema:
      std::vector<std::string> required_elements = required_elements_from_schema();
      std::vector<std::string> optional_elements = optional_elements_from_schema();
      std::vector<std::string> all_elements = all_elements_from_schema();



      std::vector<std::string> present_elements = {};


      // validate required elements are present
      //std::vector<std::string> missing_required_elements = required_elements;
      //for (auto &required_element : required_elements)
      //{

      //}


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


#include <Blast/Cpp/EnumClass.hpp>
#include <Blast/Quinetessence/YAMLParsing/EnumClassParser.hpp>
std::vector<Blast::Cpp::EnumClass> extract_enum_classes(YAML::Node &node, std::string filename)
   // NOTE: This function expects the node to be the root object, and will look within it for the "enums:" node
{
   // extract and validate root node:
   std::string this_func_name = "extract_enum_classes";
   const std::string ENUMS = "enums";
   YAML::Node enum_classes_node = fetch_node(node, ENUMS, YAML::NodeType::Sequence, YAML::Load("[]"));
   validate(enum_classes_node.IsSequence(), this_func_name, "Expected \"enums\" to be of a YAML Sequence type.");

   // extract elements from node
   std::vector<Blast::Cpp::EnumClass> result;
   for (std::size_t i=0; i<enum_classes_node.size(); i++)
   {
      YAML::Node it = enum_classes_node[i];
      Blast::Quinetessence::YAMLParsing::EnumClassParser enum_class_parser(it);
      Blast::Cpp::EnumClass extracted_enum_class = enum_class_parser.parse(); // TODO: consider try..catch here with nice error messages
      result.push_back(extracted_enum_class);
   }
   return result;
}


std::vector<Blast::Cpp::ClassAttributes> extract_attribute_properties(YAML::Node &source, std::string filename)
{
   // NOTE "filename" currently unused

   std::string this_func_name = "extract_attribute_properties";
   const std::string PROPERTIES = "properties";
   std::vector<Blast::Cpp::ClassAttributes> result;

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
      const std::string EXPLICIT_GETTER = "explicit_getter";
      const std::string GETTER_REF = "getter_ref";
      const std::string SETTER = "setter";
      const std::string CONSTEXPR = "constexpr";

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
      std::string has_getter_AS_STR = fetch_string(it, GETTER, "false");
      bool has_getter = (has_getter_AS_STR == "true") ? true : false;
      //bool has_getter = fetch_bool(it, GETTER, false);
      bool has_explicit_getter = fetch_bool(it, EXPLICIT_GETTER, false);
      bool has_getter_ref = fetch_bool(it, GETTER_REF, false);
      bool has_setter = fetch_bool(it, SETTER, false);
      bool is_constexpr = fetch_bool(it, CONSTEXPR, false);
      //std::string initialization_value = init_with_node.as<std::string>();
      //bool is_static = static_node.as<bool>();
      //bool is_constructor_parameter = constructor_arg_node.as<bool>();
      //bool has_getter = getter_node.as<bool>();
      //bool has_getter_ref = false;
      //bool has_setter = setter_node.as<bool>();

      // TODO: test these conditions
      validate((!(is_constexpr && has_setter)), this_func_name, "Attribute property \"constexpr\" can not also exist when \"setter\" is anything but false.");
      validate((!(is_constexpr && !is_static)), this_func_name, "Attribute property \"constexpr\" must also be \"static\".");
      validate((!(is_constexpr && is_constructor_parameter)), this_func_name, "Attribute property \"constexpr\" can not be included with \"constructor_arg\".");
      validate((!(is_constexpr && has_getter_ref)), this_func_name, "Attribute property \"constexpr\" can not be combined with \"getter_ref\". You must access the property directly.");
      validate((!(is_constexpr && has_getter)), this_func_name, "Attribute property \"constexpr\" can not be combined with \"getter\". You must access the property directly.");

      validate((has_getter_AS_STR=="true" || has_getter_AS_STR=="false" || has_getter_AS_STR=="explicit"), this_func_name, "Attribute property \"getter\" can only be one of [\"true\", \"false\", or \"explicit\"].");

      validate(!(has_getter && has_explicit_getter), this_func_name, "Attribute property cannot have both \"getter: true\" and \"explicit_getter: true\".");

      if (has_getter_AS_STR == "explicit") has_explicit_getter = true;

      Blast::Cpp::ClassAttributes class_attribute_properties(datatype, variable_name, initialization_value, is_static, is_constructor_parameter, has_getter, has_explicit_getter, has_getter_ref, has_setter, is_constexpr);

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

   for (std::size_t i=0; i<source.size();i++)
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
      std::vector<std::string> default_value_dependency_symbols = extract_default_argument_dependency_symbols(node);

      Blast::Cpp::FunctionArgument function_argument(
            type_node.as<std::string>(),
            name_node.as<std::string>(),
            default_argument_node.as<std::string>(),
            default_value_dependency_symbols
      );

      result.push_back(function_argument);
   }

   return result;
}



                      // function            // internal deps          // default arg deps
std::vector<std::tuple<Blast::Cpp::Function, std::vector<std::string>, std::vector<std::string>>> extract_functions_and_dependency_info(YAML::Node &source, std::string this_class_name="UnknownClass")
{
   std::string this_func_name = "extract_functions_and_dependency_info";
   const std::string FUNCTIONS = "functions";
                         // function            // internal deps          // default arg deps
   std::vector<std::tuple<Blast::Cpp::Function, std::vector<std::string>, std::vector<std::string>>> result;

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
      const std::string FINAL_OVERRIDE = "final_override";
      const std::string PURE_VIRTUAL = "pure_virtual";
      const std::string GUARDS = "guards";
      const std::string PRIVATE = "private";
      const std::string PROTECTED = "protected";
      //const std::string DEPENDENCY_SYMBOLS = "dependency_symbols";

      validate(it.IsMap(), this_func_name, "Unexpected sequence element in \"functions\", expected to be of a YAML Map.");

      //YAML::Node type_node = it.operator[](TYPE);
      YAML::Node name_node = it.operator[](NAME);
      YAML::Node parameters_node = fetch_node(it, PARAMETERS, YAML::NodeType::Sequence, YAML::Load("[]"));
      YAML::Node guards_node = fetch_node(it, GUARDS, YAML::NodeType::Sequence, YAML::Load("[]"));
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
      bool is_final_override = fetch_bool(it, FINAL_OVERRIDE, false);
      bool is_pure_virtual = fetch_bool(it, PURE_VIRTUAL, false);
      bool is_private = fetch_bool(it, PRIVATE, false);
      bool is_protected = fetch_bool(it, PROTECTED, false);

      validate(!(is_protected && is_protected), this_func_name, "Function properties \"private\" and \"protected\" cannot both be true.");

      std::vector<std::string> guards_conditionals = extract_sequence_as_string_array(guards_node);
      std::string guards_code = GuardCodeCreator::generate_guards_code(guards_conditionals, this_class_name, name);

      std::string body_with_guard_code = guards_code + body;

      Blast::Cpp::Function function(type, name, signature, body_with_guard_code, is_static, is_const, is_override, is_virtual, is_pure_virtual, is_final_override, is_private, is_protected);

      // get the body dependency symbols
      std::vector<std::string> body_dependency_symbols = extract_function_body_dependency_symbols(it);
      if (!guards_conditionals.empty())
      {
         std::vector<std::string> guards_dependency_symbols = GuardCodeCreator::good_enough_for_now_guards_dependency_symbols();
         body_dependency_symbols.insert(body_dependency_symbols.end(), guards_dependency_symbols.begin(), guards_dependency_symbols.end());
      }

      // get the dependency symbols that are the result of default arguments (and need to be public)
      std::vector<std::string> default_argument_dependency_symbols = extract_default_argument_dependency_symbols(it);

      result.push_back({ function, body_dependency_symbols, default_argument_dependency_symbols });
   }

   return result;
}



std::vector<Blast::Cpp::SymbolDependencies> extract_symbol_dependencies(YAML::Node &source, std::string filename)
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

   std::stringstream error_message;
   error_message << "In " << filename << ": error: " << "Expected \"dependencies\" to be of a YAML Sequence type.";
   validate(source_symbol_dependencies.IsSequence(), this_func_name, error_message.str());

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


#include <Blast/DependencySymbolAtomizer.hpp>
#include <Blast/StringJoiner.hpp>
#include <Blast/DependencyHeadersSuggester.hpp>

std::vector<Blast::Cpp::SymbolDependencies> consolidate_function_body_symbol_dependencies(
      std::vector<std::string> dependency_symbols,
      std::vector<Blast::Cpp::SymbolDependencies> &known_listed_dependencies,
      std::string filename
   )
{
   std::vector<Blast::Cpp::SymbolDependencies> result;

   Blast::DependencySymbolAtomizer atomizer;
   std::vector<std::string> atomic_dependency_symbols;
   for (auto &dependency_symbol : dependency_symbols)
   {
      std::vector<std::string> atomized_dependency_atoms = Blast::DependencySymbolAtomizer(dependency_symbol).atomize();
      for (auto &atomized_dependency_atom : atomized_dependency_atoms)
      {
         atomic_dependency_symbols.push_back(atomized_dependency_atom);
      }
   }
   

   //for (auto &dependency_symbol : dependency_symbols)
   std::vector<std::string> not_found_dependencies;
   for (auto &dependency_symbol : atomic_dependency_symbols)
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
         not_found_dependencies.push_back(dependency_symbol);
      }
   }

   if (not_found_dependencies.size() >= 1)
   {
      std::stringstream error_message;
      error_message << std::endl
                    << "In:\n"
                    << "\n"
                    << filename << "\n"
                    << "\n"
                    << "===============================\n\n"
                    << " error: Could not find [ " << Blast::StringJoiner(not_found_dependencies, ", ").join() << "] dependency(s) from dependency_symbols.\n"
                    << "===============================\n\n";
       for (auto &not_found_dependency : not_found_dependencies)
      {
         Blast::DependencyHeadersSuggester dependency_headers_suggester;

         std::string dependency = not_found_dependency;
         std::string headers = dependency_headers_suggester.find_suggested_headers_csv(dependency);

         //std::string dependency = not_found_dependency;
         //std::string headers = __replace(not_found_dependency, "::", "/") + ".hpp";

         //if (dependency == "ALLEGRO_BITMAP") headers = "allegro5/allegro.h";
         //if (dependency == "ALLEGRO_FONT") headers = "allegro5/allegro_font.h";
         //if (dependency == "ALLEGRO_DISPLAY") headers = "allegro5/allegro_display.h";
         //if (dependency == "ALLEGRO_COLOR") headers = "allegro5/allegro.h";
         //if (dependency == "StageInterface") headers = "Hexagon/StageInterface.hpp";
         //if (dependency == "std::function") headers = "functional";
         //if (dependency == "std::min") headers = "algorithm";
         //if (dependency == "std::max") headers = "algorithm";
         //if (dependency == "fmod") headers = "cmath";
         //if (dependency == "AllegroFlare::interpolator")
         //{
            //dependency = "'AllegroFlare::interpolator'";
            //headers = "AllegroFlare/Interpolators.hpp";
         //}
         //if (dependency == "AllegroFlare::interpolator::")
         //{
            //dependency = "'AllegroFlare::interpolator::'";
            //headers = "AllegroFlare/Interpolators.hpp";
         //}
         //if (dependency == "AllegroFlare::Color::")
         //{
            //dependency = "'AllegroFlare::Color::'";
            //headers = "AllegroFlare/Color.hpp";
         //}
         //if (dependency == "AllegroFlare::Interpolators::")
         //{
            //dependency = "'AllegroFlare::Interpolators::'";
            //headers = "AllegroFlare/Interpolators.hpp";
         //}

         error_message
            << "  - symbol: " << dependency << "\n"
            << "    headers: [ " << headers << " ]\n";
      }

      explode("consolidate_function_body_symbol_dependencies", error_message.str());
   }


   return result;
}



Blast::Cpp::Class convert_yaml_to_class(std::string class_name, YAML::Node &source, std::string quintessence_filename)
{
   // declare variables

   std::vector<std::string> namespaces = extract_namespaces_from_quintessence_filename(quintessence_filename);
   std::vector<Blast::Cpp::ParentClassProperties> parent_classes_properties = extract_parent_classes_properties(source);
   std::vector<Blast::Cpp::ClassAttributes> attribute_properties = extract_attribute_properties(source, quintessence_filename);
   std::vector<Blast::Cpp::EnumClass> enum_classes = extract_enum_classes(source, quintessence_filename);
   std::vector<std::tuple<Blast::Cpp::Function, std::vector<std::string>, std::vector<std::string>>> functions_and_dependencies = extract_functions_and_dependency_info(source, class_name);
   std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies = extract_symbol_dependencies(source, quintessence_filename);
   std::vector<std::string> function_body_symbol_dependency_symbols = extract_function_body_symbol_dependency_symbols(source);



   // validate that for any <ClassAttribtes> that have explicit_getters, there is a get_[attribute_name] function that has been declared
   
   std::vector<std::string> expected_explicit_getter_function_names;
   for (auto &attribute_property : attribute_properties)
   {
      if (attribute_property.has_explicit_getter == true)
      {
         std::string expected_explicit_getter_function_name = "get_" + attribute_property.variable_name; // TODO: use a helper to generate the getter function name
         expected_explicit_getter_function_names.push_back(expected_explicit_getter_function_name);
      }
   }

   std::vector<std::string> explicit_getter_function_names_that_do_not_exist;
   // TODO: validate the function names exist
   for (auto &expected_explicit_getter_function_name : expected_explicit_getter_function_names)
   {
      bool function_has_been_explicitly_declared = false;
      for (auto &function_and_dependency : functions_and_dependencies)
      {
         std::string this_function_name = std::get<0>(function_and_dependency).get_name();
         if (this_function_name == expected_explicit_getter_function_name)
         {
            function_has_been_explicitly_declared = true;
            break;
         }
      }

      if (!function_has_been_explicitly_declared) explicit_getter_function_names_that_do_not_exist.push_back(expected_explicit_getter_function_name);
   }

   // throw error if explicit_getter functions are missing
   if (!explicit_getter_function_names_that_do_not_exist.empty())
   {
      std::stringstream error_message;
      error_message << "quintessence_from_yaml error: in \"" << quintessence_filename << "\", explicit getters have been "
         "set on some properties, yet the expected function declarations for [";
         for (auto &explicit_getter_function_name_that_does_not_exist : explicit_getter_function_names_that_do_not_exist)
         {
            error_message << "\"" << explicit_getter_function_name_that_does_not_exist << "\", ";
         }
         error_message << "] are not present.";

         // TODO: validate the return type of the function matches the return type of the property, and, possibly that there are no parameters on the function

      throw std::runtime_error(error_message.str());
   }


   
   // consolidate functions and their dependencies

   std::vector<Blast::Cpp::Function> functions = {};
   std::vector<std::string> per_function_dependency_symbols = {};
   for (auto &function_and_dependency : functions_and_dependencies)
   {
      functions.push_back(std::get<0>(function_and_dependency));
      for (auto &dependency_symbol : std::get<1>(function_and_dependency))
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
         symbol_dependencies,
         quintessence_filename
      );


   // build the actual class

   Blast::Cpp::Class klass(class_name, namespaces, parent_classes_properties, attribute_properties, enum_classes, functions, symbol_dependencies, function_body_symbol_dependencies);

   return klass;
}



int main(int argc, char **argv)
{
   Blast::CommandLineFlaggedArgumentsParser command_line_arguments(argc, argv);
   if (command_line_arguments.has_flag("--less_verbose")) verbose_output = false;

   std::vector<std::vector<std::string>> filename_arg_args = command_line_arguments.get_flagged_args("-f");

   std::vector<std::string> filename_args = {};
   for (auto &filename_arg_arg : filename_arg_args)
   {
      filename_args.insert(filename_args.end(), filename_arg_arg.begin(), filename_arg_arg.end());
   }


   if (filename_args.size() <= 0)
   {
      std::cout << "No quintessence filenames passed, Expecting pass a quintessence filename or filenames as an argument (after the -f flag). Skipping." << std::endl;
      return 0;
   }

   for (unsigned int i=0; i<filename_args.size(); i++)
   {
      std::string quintessence_filename = filename_args[i];
      if (verbose_output) std::cout << "Assessing genesis for \"" << quintessence_filename << "\"" << std::endl;
      YAML::Node source; // = YAML::LoadFile(quintessence_filename);

      try
      {
         source = YAML::LoadFile(quintessence_filename);
      }
      catch (const std::exception& e)
      {
         std::stringstream revised_error_message;
         revised_error_message << "ERROR: YAML Parse Failure on file \"" << quintessence_filename << "\" with the following message: \""
                               << e.what() << "\".";
         // TODO: output the error message to std::err or std::cout in red
         throw std::runtime_error(revised_error_message.str());
      }


      // infer the class name from the filename

      QuintessenceClassNameFromYAMLFilenameInferer class_name_inferer(filename_args[i]);
      std::string class_name = class_name_inferer.infer_class_name();


      // convert the yaml structure to the class

      Blast::Cpp::Class klass = convert_yaml_to_class(class_name, source, quintessence_filename);


      //// generate and write the files

      Blast::Cpp::ClassGenerator cpp_class_generator(klass);
      write_to_files(cpp_class_generator);
   }

   return 0;
}



