

#include <Blast/VersionInfoCppFileGenerator.hpp>

#include <Blast/Cpp/ClassGenerator.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Blast
{


VersionInfoCppFileGenerator::VersionInfoCppFileGenerator(Blast::ReleaseInfo release_info)
   : release_info(release_info)
   , cpp_class("")
   , initialized(false)
{
}


VersionInfoCppFileGenerator::~VersionInfoCppFileGenerator()
{
}


Blast::ReleaseInfo VersionInfoCppFileGenerator::get_release_info() const
{
   return release_info;
}


void VersionInfoCppFileGenerator::set_release_info(Blast::ReleaseInfo release_info)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[VersionInfoCppFileGenerator::set_release_info]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionInfoCppFileGenerator::set_release_info: error: guard \"(!initialized)\" not met");
   }
   this->release_info = release_info;
   return;
}

void VersionInfoCppFileGenerator::initialize()
{
   cpp_class = build_cpp_class();
   initialized = true;
   return;
}

Blast::Cpp::Class VersionInfoCppFileGenerator::build_cpp_class()
{
   //return Blast::Cpp::Class(
      //std::string class_name="UnnamedClass",
      //std::vector<std::string> namespaces={},
      //std::vector<Blast::Cpp::ParentClassProperties> parent_classes_properties={},
      //std::vector<Blast::Cpp::ClassAttributes> attribute_properties={},
      //std::vector<Blast::Cpp::EnumClass> enum_classes={},
      //std::vector<Blast::Cpp::Function> functions={},
      //std::vector<Blast::Cpp::SymbolDependencies> symbol_dependencies={},
      //std::vector<Blast::Cpp::SymbolDependencies> function_body_symbol_dependencies={}
   //);
   return Blast::Cpp::Class(
      "ThisVersionInfo",
      {},
      {},
      build_cpp_class_attribute_properties(), // attribute_properties
      {}, // enum_classes
      {}, // functions
      build_cpp_class_symbol_dependencies(), // symbol_dependencies
      {} // function_body_symbol_dependencies
   );
}

std::vector<Blast::Cpp::ClassAttributes> VersionInfoCppFileGenerator::build_cpp_class_attribute_properties()
{
   std::vector<Blast::Cpp::ClassAttributes> result = {
      build_cpp_class_attribute("std::string", "version", "0.0.0"),
   };
   return result;
}

Blast::Cpp::ClassAttributes VersionInfoCppFileGenerator::build_cpp_class_attribute(std::string datatype, std::string variable_name, std::string initialization_value)
{
   return Blast::Cpp::ClassAttributes(
         datatype, //std::string datatype,
         variable_name, //std::string variable_name,
         initialization_value, //std::string initialization_value,
         true, //bool is_static,
         false, //bool is_constructor_parameter,
         true, //bool has_getter,
         false, //bool has_expicit_getter,
         false, //bool has_getter_ref,
         false, //bool has_setter,
         false //bool is_constexpr
      );
}

std::vector<Blast::Cpp::SymbolDependencies> VersionInfoCppFileGenerator::build_cpp_class_symbol_dependencies()
{
   std::vector<Blast::Cpp::SymbolDependencies> result = {
      Blast::Cpp::SymbolDependencies(
         "std::string", // std::string symbol,
         { "string" }, // std::vector<std::string> include_header_files={},
         {}, // std::vector<std::string> dependency_include_directories={},
         {} // std::vector<std::string> linked_library_names={}
      ),
      Blast::Cpp::SymbolDependencies(
         "int", // std::string symbol,
         {}, // std::vector<std::string> include_header_files={},
         {}, // std::vector<std::string> dependency_include_directories={},
         {} // std::vector<std::string> linked_library_names={}
      ),
   };
   return result;
}

std::string VersionInfoCppFileGenerator::header_file_content()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VersionInfoCppFileGenerator::header_file_content]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionInfoCppFileGenerator::header_file_content: error: guard \"initialized\" not met");
   }
   Blast::Cpp::ClassGenerator generator(cpp_class);
   return generator.generate_header_file_content();
}

std::string VersionInfoCppFileGenerator::source_file_content()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[VersionInfoCppFileGenerator::source_file_content]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VersionInfoCppFileGenerator::source_file_content: error: guard \"initialized\" not met");
   }
   Blast::Cpp::ClassGenerator generator(cpp_class);
   return generator.generate_source_file_content();
}


} // namespace Blast


