
#include <Blast/CppClassGenerator.hpp>
#include <Blast/libraries/json.hpp>
using json = nlohmann::json;
#include <fstream>
#include <iostream>

void explode(std::string message)
{
   throw std::runtime_error(message);
}


std::ostream & operator<< (std::ostream &out, std::vector<std::string> const &object)
{
   out << "{ ";
   for (auto &object_piece : object)
   {
      out << "\"" << object_piece << "\"";
   }
   out << " }";

   return out;
}



class Tabber
{
private:
   int tab_level;

public:
   Tabber(int tab_level=0) : tab_level(0) {}
   void indent() { tab_level++; }
   void unindent() { tab_level--; }
   int get_tab_level() { return tab_level; }
   std::string get_string_tab() { return std::string(tab_level * 3, ' '); }
};


Tabber tabber;


json &get_or_explode(json &j, std::string key)
{
   if (j.count(key) == 0)
   {
      std::cout << tabber.get_string_tab() << "🛑 \"" << key << "\" not present and is required." << std::endl;
      explode(std::string(key) + " is required");
   }

   std::cout << tabber.get_string_tab() << "✅ \"" << key << "\" found" << std::endl;

   return j[key];
}

template <class T>
T get_or_fallback(json &j, std::string key, T fallback)
{
   if (j.count(key) == 0)
   {
      std::cout << tabber.get_string_tab() << "⚠️ \"" << key << "\" not present, default of \"" << fallback << "\" will be used." << std::endl;
      return fallback;
   }

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


      //if (quintessence_json["format"] != "verbose") throw std::runtime_error("\"format\" : \"verbose\" string not present");

      // properties

      std::vector<Blast::ClassAttributeProperties> properties;

      if (quintessence_json["properties"].empty()) explode("properties is required");

      json &j = quintessence_json["properties"];

      tabber.indent();
      for (json::iterator it = j.begin(); it != j.end(); ++it)
      {
         properties.push_back(Blast::ClassAttributeProperties(
            get_or_fallback((*it), "type", std::string("")),
            get_or_explode((*it), "name"),
            get_or_fallback((*it), "init_with", std::string("")),
            get_or_fallback((*it), "static", false),
            get_or_fallback((*it), "constructor_arg", false),
            get_or_fallback((*it), "getter", false),
            get_or_fallback((*it), "setter", false)
         ));

         std::cout << (*it) << std::endl;
      }
      tabber.unindent();


      // dependencies

      std::vector<Blast::SymbolDependencies> dependencies;

      json &d = get_or_explode(quintessence_json, "dependencies");

      tabber.indent();
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
      tabber.unindent();


      // parent classes

      //std::vector<std::string> fallback;
      std::vector<Blast::ParentClassProperties> parent_classes;
      json &p = get_or_explode(quintessence_json, "parent_classes");

      tabber.indent();
      for (json::iterator it = p.begin(); it != p.end(); ++it)
      {
         parent_classes.push_back(Blast::ParentClassProperties(
            get_or_explode((*it), "class"),
            get_or_explode((*it), "init_with"),
            get_or_explode((*it), "scope")
         ));

         std::cout << (*it) << std::endl;
      }
      tabber.unindent();


      // generator

      json &klass = get_or_explode(quintessence_json, "class");
      json &namespaces = get_or_explode(quintessence_json, "namespaces");

      Blast::CppClass cpp_class(klass, namespaces, parent_classes, properties, dependencies);
      Blast::CppClassGenerator cpp_class_generator(cpp_class);

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

