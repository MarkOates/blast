
#include <Blast/CppClassGenerator.hpp>
#include <Blast/libraries/json.hpp>
using json = nlohmann::json;
#include <fstream>
#include <iostream>

void explode(std::string message)
{
   throw std::runtime_error(message);
}

json &get_or_explode(json &j, std::string key)
{
   if (j[key].empty()) explode(std::string(key) + " is required");

   return j[key];
}

bool get_or_fallback(json &j, std::string key, bool fallback)
{
   if (j[key].empty()) return fallback;

   return j[key];
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

      std::ifstream quintessence_file(quintessence_filename);
      if (quintessence_file.fail()) throw std::runtime_error("File not found.");

      std::cout << "+ Writing " << argv[i] << std::endl;

      json quintessence_json;
      quintessence_file >> quintessence_json;


      if (quintessence_json["format"] != "verbose") throw std::runtime_error("\"format\" : \"verbose\" string not present");

      // properties

      std::vector<Blast::ClassAttributeProperties> properties;

      if (quintessence_json["properties"].empty()) explode("properties is required");

      json &j = quintessence_json["properties"];

      for (json::iterator it = j.begin(); it != j.end(); ++it)
      {
         properties.push_back(Blast::ClassAttributeProperties(
            get_or_explode((*it), "type"),
            get_or_explode((*it), "name"),
            get_or_explode((*it), "init_with"),
            get_or_explode((*it), "static"),
            get_or_fallback((*it), "constructor_arg", false),
            get_or_explode((*it), "getter"),
            get_or_explode((*it), "setter")
         ));

         std::cout << (*it) << std::endl;
      }


      // dependencies

      std::vector<Blast::SymbolDependencies> dependencies;

      json &d = get_or_explode(quintessence_json, "dependencies");

      for (json::iterator it = d.begin(); it != d.end(); ++it)
      {
         dependencies.push_back(Blast::SymbolDependencies(
            get_or_explode((*it), "symbol"),
            get_or_explode((*it), "headers"),
            get_or_explode((*it), "include_directories"),
            get_or_explode((*it), "linked_libraries")
         ));

         std::cout << (*it) << std::endl;
      }


      // parent classes

      std::vector<Blast::ParentClassProperties> parent_classes;
      json &p = get_or_explode(quintessence_json, "parent_classes");

      for (json::iterator it = p.begin(); it != p.end(); ++it)
      {
         parent_classes.push_back(Blast::ParentClassProperties(
            get_or_explode((*it), "class"),
            get_or_explode((*it), "init_with"),
            get_or_explode((*it), "scope")
         ));

         std::cout << (*it) << std::endl;
      }


      // generator

      json &klass = get_or_explode(quintessence_json, "class");
      json &namespaces = get_or_explode(quintessence_json, "namespaces");

      Blast::CppClassGenerator cpp_class_generator(klass, namespaces, parent_classes, properties, dependencies);

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

   return 0;
}

