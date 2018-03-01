

#include <Blast/QuintessenceLoader.hpp>

#include <Blast/CppSelectorPatternGenerator.hpp>
#include <iostream>
#include <fstream>


static void __replace(std::string &str, const std::string &find_str, const std::string &replace_str)
{
  std::string::size_type pos = 0u;

  while((pos = str.find(find_str, pos)) != std::string::npos)
  {
     str.replace(pos, find_str.length(), replace_str);
     pos += replace_str.length();
  }
}



static std::string selector_pattern_header_template = R"END(#pragma once


#include <vector>


NAMESPACE_OPENER
class CLASS_NAME;

class CLASS_NAMESelector
{
private:
   std::vector<CLASS_NAME *> *pool;

public:
   CLASS_NAMESelector(std::vector<CLASS_NAME *> *pool=nullptr);
   ~CLASS_NAMESelector();

SELECTOR_FUNCS
};
NAMESPACE_CLOSER


)END";


static std::string selector_pattern_source_template = R"END(

#include <SELECTOR_HEADER_PATH>

#include <CLASS_HEADER_PATH>


NAMESPACE_OPENER

CLASS_NAMESelector::CLASS_NAMESelector(std::vector<CLASS_NAME *> *pool)
   : pool(pool)
{
}


CLASS_NAMESelector::~CLASS_NAMESelector()
{
}


SELECTOR_FUNCS


NAMESPACE_CLOSER

)END";


static std::string pool_pattern_header_template = R"END(

#pragma once


#include <CLASS_INCLUDE_FILEPATH>
#include <string>
#include <vector>


NAMESPACE_OPENER
class CLASS_NAMEPool
{
public:
   enum find_option_t
   {
      FIND_OPTION_NONE = 0,
      FIND_OPTION_INCLUDE_NOT_FOUND,
      FIND_OPTION_RAISE_NOT_FOUND,
   };

   int const NO_RECORD = -1;

   CLASS_NAMEPool();
   ~CLASS_NAMEPool();

   std::vector<CLASS_NAME *> pool;
   int next_id;

   bool push_back(CLASS_NAME *element);
   bool remove(int id);
   int count();
   bool destroy(int id);
   bool destroy_all();
   CLASS_NAME *find(int id, find_option_t find_option=FIND_OPTION_NONE);
   std::vector<CLASS_NAME *> find(std::vector<int> ids, find_option_t find_option=FIND_OPTION_NONE);
};
NAMESPACE_CLOSER



)END";



static std::string pool_pattern_source_template = R"END(

#include <CLASS_FILENAME>

#include <sstream>


NAMESPACE_OPENER


CLASS_NAMEPool::CLASS_NAMEPool()
   : pool()
   , next_id(0)
{
}


bool CLASS_NAMEPool::push_back(CLASS_NAME *element)
{
   pool.push_back(element);
   return true;
}


int CLASS_NAMEPool::count()
{
   return pool.size();
}


CLASS_NAME *CLASS_NAMEPool::find(int id, find_option_t find_option)
{
   CLASS_NAME *found_element = nullptr;

   for (auto &element : pool)
      if (element->get_id() == id) { found_element = element; break; }

   if (find_option == FIND_OPTION_RAISE_NOT_FOUND && found_element == nullptr)
   {
      std::stringstream error_message;
      error_message << "Looking for element with id = " << id << " but does not exist";
      throw std::runtime_error(error_message.str());
   }

   return found_element;
}


std::vector<CLASS_NAME *> CLASS_NAMEPool::find(std::vector<int> ids, find_option_t find_option)
{
   std::vector<CLASS_NAME *> results = {};
   std::vector<int> not_found_ids = {};
   find_option_t element_find_option = (find_option == FIND_OPTION_RAISE_NOT_FOUND) ? FIND_OPTION_RAISE_NOT_FOUND : FIND_OPTION_NONE;

   for (unsigned i=0; i<ids.size(); i++)
   {
      try
      {
         CLASS_NAME *found_element = find(ids[i], element_find_option);
         if (found_element || (find_option == FIND_OPTION_INCLUDE_NOT_FOUND)) results.push_back(found_element);
      }
      catch (std::runtime_error const &e)
      {
         not_found_ids.push_back(ids[i]);
      }
   }

   if (!not_found_ids.empty())
   {
      std::stringstream error_message;
      error_message << "Looking for " << ids.size() << " elements but only " << results.size() << " elements found.";
      throw std::runtime_error(error_message.str());
   }

   return results;
}


bool CLASS_NAMEPool::remove(int id)
{
   for (unsigned i=0; i<pool.size(); i++)
      if (pool[i]->get_id() == id)
      {
         pool.erase(pool.begin() + i);
         return true;
      }
   return false;
}


bool CLASS_NAMEPool::destroy(int id)
{
   for (unsigned i=0; i<pool.size(); i++)
      if (pool[i]->get_id() == id)
      {
         delete pool[i];
         return true;
      }
   return false;
}


bool CLASS_NAMEPool::destroy_all()
{
   for (unsigned i=0; i<pool.size(); i++) delete pool[i];
   pool.clear();
   return true;
}


NAMESPACE_CLOSER


)END";


namespace Blast
{


QuintessenceLoader::QuintessenceLoader()
   : cpp_class_generator()
   , cpp_google_test_suite_generator()
   , json()
{
}


QuintessenceLoader::~QuintessenceLoader()
{
}


nlohmann::json QuintessenceLoader::get_json()
{
   return json;
}


CppClassGenerator QuintessenceLoader::get_cpp_class_generator()
{
   return cpp_class_generator;
}


CppGoogleTestSuiteGenerator QuintessenceLoader::get_cpp_google_test_suite_generator()
{
   return cpp_google_test_suite_generator;
}


void QuintessenceLoader::parse(std::string json)
{
   throw std::runtime_error("QuintessenceLoader::parse not implemented");
}


void QuintessenceLoader::load(std::string filename)
{
   std::vector<std::string> warnings;

   std::ifstream quintessence_file(filename);
   if (quintessence_file.fail())
   {
      std::stringstream error_message;
      error_message << "File \"" << filename << "\" not found.";
      throw std::runtime_error(error_message.str());
   }

   quintessence_file >> json;



   bool has_pool_pattern = false;
   bool has_selector_pattern = false;
   nlohmann::json *selector_patterns = nullptr;
   for (auto &pattern : json["patterns"]) {
      if (pattern["type"] == "pool") has_pool_pattern = true;
      if (pattern["type"] == "selectors")
      {
         has_selector_pattern = true;
         selector_patterns = &pattern;
      }
   }



   std::vector<Blast::ClassAttributeProperties> properties;

   if (json["properties"].empty()) throw std::runtime_error("\"properties\" is empty");
   nlohmann::json &j = json["properties"];

   if (has_pool_pattern)
   {
      std::cout << "Pool Pattern detected" << std::endl;
      j.insert(j.begin(),
         nlohmann::json{
            { "name", "type" },
            { "type", "std::string" },
            { "init_with", "\"[Untyped]\"" },
            { "constructor_arg", true },
            { "getter", true }
         }
      );
      j.insert(j.begin(),
         nlohmann::json{
           { "name", "id" },
           { "type", "int" },
           { "init_with", "last_id++" }
         }
      );
      j.insert(j.begin(),
         nlohmann::json{
            { "name", "last_id" },
            { "type", "int" },
            { "static", true },
            { "init_with", "0" }
         }
      );
   }

   std::cout << "AAAAAAAAAA" << std::endl;

   for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it)
   {
      if ((*it)["name"].empty()) throw std::runtime_error("required \"name\" missing from property");

      std::string name = (*it)["name"];

      if ((*it)["type"].empty()) warnings.push_back(std::string("\"type\" missing on ") + name + " using default type \"std::string\"");
      if ((*it)["init_with"].empty()) warnings.push_back(std::string("\"init_with\" missing on ") + name + " using default \"\" (blank)");
      if ((*it)["static"].empty()) warnings.push_back(std::string("\"static\" missing on ") + name + " using default \"false\"");
      else if (!(*it)["static"].is_boolean()) throw std::runtime_error("\"static\" must be a boolean");
      if ((*it)["constructor_arg"].empty()) warnings.push_back(std::string("\"constructor_arg\" missing on ") + name + " using default \"false\"");
      if ((*it)["getter"].empty()) warnings.push_back(std::string("\"getter\" missing on ") + name + " using default \"true\"");
      if ((*it)["setter"].empty()) warnings.push_back(std::string("\"setter\" missing on ") + name + " using default \"false\"");

      //CppClassGenerator(std::string class_name="UnnamedClass", std::vector<std::string> namespaces={}, std::vector<Blast::ParentClassProperties> parent_classes_properties={}, std::vector<ClassAttributeProperties> attribute_properties={}, std::vector<Blast::SymbolDependencies> symbol_dependencies={});

      //ClassAttributeProperties(std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_parameter, bool has_getter, bool has_setter);

      properties.push_back(Blast::ClassAttributeProperties(
         (*it)["type"].empty() ? "std::string" : (*it)["type"].get<std::string>(),
         (*it)["name"],
         (*it)["init_with"].empty() ? "" : (*it)["init_with"].get<std::string>(),
         (*it)["static"].empty() ? false : (*it)["static"].get<bool>(),
         (*it)["constructor_arg"].empty() ? false : (*it)["constructor_arg"].get<bool>(),
         (*it)["getter"].empty() ? true : (*it)["getter"].get<bool>(),
         (*it)["setter"].empty() ? false : (*it)["setter"].get<bool>()
      ));

      std::cout << (*it) << std::endl;
   }

   std::cout << "AAAAAAAAAA" << std::endl;

   // dependencies

   std::vector<Blast::SymbolDependencies> dependencies;

   if (json["dependencies"].empty()) throw std::runtime_error("\"dependencies\" is empty");
   nlohmann::json &d = json["dependencies"];

   for (nlohmann::json::iterator it = d.begin(); it != d.end(); ++it)
   {
      dependencies.push_back(Blast::SymbolDependencies(
         (*it)["symbol"],
         (*it)["headers"],
         (*it)["include_directories"],
         (*it)["linked_libraries"]
      ));

      std::cout << (*it) << std::endl;
   }


   std::cout << "AAAAAAAAAA" << std::endl;
   // parent classes

   std::vector<Blast::ParentClassProperties> parent_classes;
   if (json["parent_classes"].empty()) warnings.push_back("\"parent_classes\" is empty");
   nlohmann::json &p = json["parent_classes"];
   for (nlohmann::json::iterator it = p.begin(); it != p.end(); ++it)
   {
      parent_classes.push_back(Blast::ParentClassProperties(
         (*it)["class"],
         (*it)["init_with"],
         (*it)["scope"]
      ));

      std::cout << (*it) << std::endl;
   }

   std::cout << "BBBBBBBB" << std::endl;

   // generator

   bool namespaces_present = true;
   std::vector<std::string> namespaces;

   if (json["class"].empty()) throw std::runtime_error("\"class\" is empty");
   if (json["namespaces"].empty())
   {
      warnings.push_back("\"namespaces\" is empty");
   }
   else // namespaces = std::vector<std::string>(json["namespaces"]);
   {
      for (auto& element : json["namespaces"])
      {
         // todo validate element is string
         namespaces.push_back(element);
         //std::cout << element << '\n';
      }
   }

   cpp_class_generator = Blast::CppClassGenerator(json["class"], namespaces, parent_classes, properties, dependencies);

   std::string header_filepath = cpp_class_generator.project_header_filepath();
   std::cout << "CCCCCCCCC" << std::endl;

   std::ofstream header_file(header_filepath, std::ofstream::out);
   if (header_file.fail())
   {
      std::stringstream error_message;
      error_message << "Could not open header file \"" << header_filepath << "\" for writing.";
      throw std::runtime_error(error_message.str());
   }
   header_file << cpp_class_generator.generate_header_file_content();

   std::cout << "DDDDDDDDDDD" << std::endl;
   std::string source_filepath = cpp_class_generator.project_source_filepath();
   std::ofstream source_file(source_filepath, std::ofstream::out);
   if (source_file.fail()) throw std::runtime_error("Could not open source file for writing.");
   source_file << cpp_class_generator.generate_source_file_content();

   std::cout << "AAAAAAAAAA" << std::endl;
   // output success
   std::cout << "done. Files generated \033[1m\033[32m" << header_filepath << " and " << source_filepath << "\033[0m" << std::endl;


   std::cout << "AAAAAAAAAA" << std::endl;


   /// create the test file
   std::vector<CppGoogleTestGenerator> test_generators;
   test_generators.push_back(CppGoogleTestGenerator(json["class"], "", "can be created without arguments"));

   CppGoogleTestSuiteGenerator test_suite_generator(json["class"], namespaces, test_generators);

   std::string test_filepath = test_suite_generator.test_filepath();
   std::ofstream test_file(test_filepath, std::ofstream::out);
   std::cout << "FILEFILEFILE: " << test_filepath << std::endl;
   if (test_file.fail()) throw std::runtime_error("Could not open test file for writing.");
   test_file << test_suite_generator.render();
   test_file.close();


   /// create the pool pattern classes:
   // header:

   //std::vector<auto> patterns = json["patterns"];


   std::string class_name = json["class"];
   std::string class_header_include_filepath = std::string("RegionProject/") + class_name + ".hpp";

   if (has_pool_pattern)
   {
      std::string pool_pattern_header_content = pool_pattern_header_template;
      __replace(pool_pattern_header_content, "CLASS_NAME", json["class"]);
      __replace(pool_pattern_header_content, "CLASS_INCLUDE_FILEPATH", class_header_include_filepath);
      __replace(pool_pattern_header_content, "NAMESPACE_OPENER", "namespace RegionProject\n{\n");
      __replace(pool_pattern_header_content, "NAMESPACE_CLOSER", "} // namespace RegionProject");
      std::string pool_header_filepath = std::string("include/RegionProject/") + class_name + "Pool.hpp";
      std::ofstream pool_header_file(pool_header_filepath, std::ofstream::out);
      std::cout << "FILEFILEFILE: " << pool_header_filepath << std::endl;
      if (pool_header_file.fail()) throw std::runtime_error("Could not open pool header file for writing.");
      pool_header_file << pool_pattern_header_content;
      test_file.close();

      // source:

      std::string pool_pattern_source_content = pool_pattern_source_template;
      __replace(pool_pattern_source_content, "CLASS_NAME", json["class"]);
      std::string pool_source_header_include_filepath = std::string("RegionProject/") + class_name + "Pool.hpp";
      __replace(pool_pattern_source_content, "CLASS_FILENAME", pool_source_header_include_filepath);
      __replace(pool_pattern_source_content, "NAMESPACE_OPENER", "namespace RegionProject\n{\n");
      __replace(pool_pattern_source_content, "NAMESPACE_CLOSER", "} // namespace RegionProject");
      std::string pool_source_filepath = std::string("src/RegionProject/") + class_name + "Pool.cpp";
      std::ofstream pool_source_file(pool_source_filepath, std::ofstream::out);
      std::cout << "FILEFILEFILE: " << pool_source_filepath << std::endl;
      if (pool_source_file.fail()) throw std::runtime_error("Could not open pool source file for writing.");
      pool_source_file << pool_pattern_source_content;
      test_file.close();
   }


   if (has_selector_pattern)
   {
      std::vector<Blast::CppSelectorPatternGenerator> selector_functions;

      std::stringstream selector_func_declarations;
      std::stringstream selector_func_definitions;

      std::cout << "=================================" << std::endl;
      for (auto &selector_pattern : (*selector_patterns)["selectors"])
      {
         std::cout << "***************************";
         std::cout << selector_pattern;
         //std::string function_name = "function_name";
         //std::string selection_condition = "selection_condition";
         //std::string casted_type = "CastedType";
         std::string function_name = selector_pattern["function_name"];
         std::string selection_condition = selector_pattern["selection_condition"];
         std::string casted_type = selector_pattern["type"];

         Blast::CppSelectorPatternGenerator cpp_selector_pattern_generator(class_name, function_name, selection_condition, casted_type);
         selector_functions.push_back(cpp_selector_pattern_generator);
         selector_func_declarations << cpp_selector_pattern_generator.render_declaration() << "\n";
         selector_func_definitions << cpp_selector_pattern_generator.render_definition() << "\n\n";
      }
      std::cout << "=================================" << std::endl;

      std::string selector_pattern_header_content = selector_pattern_header_template;
      __replace(selector_pattern_header_content, "CLASS_NAME", class_name);
      __replace(selector_pattern_header_content, "NAMESPACE_OPENER", "namespace RegionProject\n{\n");
      __replace(selector_pattern_header_content, "NAMESPACE_CLOSER", "} // namespace RegionProject");
      __replace(selector_pattern_header_content, "SELECTOR_FUNCS", selector_func_declarations.str());

      std::string selector_header_filepath = std::string("include/RegionProject/") + class_name + "Selector.hpp";
      std::ofstream selector_header_file(selector_header_filepath, std::ofstream::out);
      std::cout << "FILEFILEFILE: " << selector_header_filepath << std::endl;
      if (selector_header_file.fail()) throw std::runtime_error("Could not open selector header file for writing.");
      selector_header_file << selector_pattern_header_content;
      test_file.close();

      std::string selector_pattern_source_content = selector_pattern_source_template;
      __replace(selector_pattern_source_content, "CLASS_NAME", class_name);
      std::string selector_header_include_filepath = std::string("RegionProject/") + class_name + "Selector.hpp";
      __replace(selector_pattern_source_content, "CLASS_HEADER_PATH", class_header_include_filepath);
      __replace(selector_pattern_source_content, "SELECTOR_HEADER_PATH", selector_header_include_filepath);
      __replace(selector_pattern_source_content, "NAMESPACE_OPENER", "namespace RegionProject\n{\n");
      __replace(selector_pattern_source_content, "NAMESPACE_CLOSER", "} // namespace RegionProject");
      __replace(selector_pattern_source_content, "SELECTOR_FUNCS", selector_func_definitions.str());

      std::string selector_source_filepath = std::string("src/RegionProject/") + class_name + "Selector.cpp";
      std::ofstream selector_source_file(selector_source_filepath, std::ofstream::out);
      std::cout << "FILEFILEFILE: " << selector_source_filepath << std::endl;
      if (selector_source_file.fail()) throw std::runtime_error("Could not open selector source file for writing.");
      selector_source_file << selector_pattern_source_content;
      test_file.close();
   }
}


} // namespace Blast
