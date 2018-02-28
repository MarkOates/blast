

#include <Blast/QuintessenceLoader.hpp>

#include <iostream>
#include <fstream>

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


   std::vector<Blast::ClassAttributeProperties> properties;

   if (json["properties"].empty()) throw std::runtime_error("\"properties\" is empty");
   nlohmann::json &j = json["properties"];

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
}


} // namespace Blast


