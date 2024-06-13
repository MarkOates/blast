

#include <Blast/ReleaseInfoCppFileGenerator.hpp>

#include <Blast/Cpp/ClassGenerator.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Blast
{


ReleaseInfoCppFileGenerator::ReleaseInfoCppFileGenerator(Blast::ReleaseInfo release_info)
   : release_info(release_info)
   , cpp_class("")
   , initialized(false)
{
}


ReleaseInfoCppFileGenerator::~ReleaseInfoCppFileGenerator()
{
}


Blast::ReleaseInfo ReleaseInfoCppFileGenerator::get_release_info() const
{
   return release_info;
}


void ReleaseInfoCppFileGenerator::set_release_info(Blast::ReleaseInfo release_info)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Blast::ReleaseInfoCppFileGenerator::set_release_info]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::ReleaseInfoCppFileGenerator::set_release_info]: error: guard \"(!initialized)\" not met");
   }
   this->release_info = release_info;
   return;
}

void ReleaseInfoCppFileGenerator::initialize()
{
   cpp_class = build_cpp_class();
   initialized = true;
   return;
}

Blast::Cpp::Class ReleaseInfoCppFileGenerator::build_cpp_class()
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
      "ReleaseInfo",
      {},
      {},
      build_cpp_class_attribute_properties(), // attribute_properties
      {}, // enum_classes
      {}, // functions
      build_cpp_class_symbol_dependencies(), // symbol_dependencies
      {} // function_body_symbol_dependencies
   );
}

std::vector<Blast::Cpp::ClassAttributes> ReleaseInfoCppFileGenerator::build_cpp_class_attribute_properties()
{
   std::vector<Blast::Cpp::ClassAttributes> result = {
      build_cpp_class_attribute(
         "std::string",
         "version",
         release_info.build_project_version_string()
      ),
      build_cpp_class_attribute(
         "std::string",
         "allegro_flare_version_git_hash",
         release_info.get_allegro_flare_version_git_hash()
      ),
      build_cpp_class_attribute(
         "std::string",
         "blast_version_git_hash",
         release_info.get_blast_version_git_hash()
      ),
   };
   return result;
}

Blast::Cpp::ClassAttributes ReleaseInfoCppFileGenerator::build_cpp_class_attribute(std::string datatype, std::string variable_name, std::string initialization_value)
{
   if (!(is_valid_datatype(datatype)))
   {
      std::stringstream error_message;
      error_message << "[Blast::ReleaseInfoCppFileGenerator::build_cpp_class_attribute]: error: guard \"is_valid_datatype(datatype)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::ReleaseInfoCppFileGenerator::build_cpp_class_attribute]: error: guard \"is_valid_datatype(datatype)\" not met");
   }
   std::string sanitized_initialization_value = (datatype == "std::string") ? wrap_in_quotes(initialization_value) : initialization_value;

   return Blast::Cpp::ClassAttributes(
         datatype, //std::string datatype,
         variable_name, //std::string variable_name,
         sanitized_initialization_value, //std::string initialization_value,
         true, //bool is_static,
         false, //bool is_constructor_parameter,
         true, //bool has_getter,
         false, //bool has_expicit_getter,
         false, //bool has_getter_ref,
         false, //bool has_setter,
         false, //bool has_explicit_setter,
         false, //bool is_constexpr
         false //bool is_exposed
      );
}

std::vector<Blast::Cpp::SymbolDependencies> ReleaseInfoCppFileGenerator::build_cpp_class_symbol_dependencies()
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

std::string ReleaseInfoCppFileGenerator::wrap_in_quotes(std::string str)
{
   return "\"" + str + "\"";
}

bool ReleaseInfoCppFileGenerator::is_valid_datatype(std::string str)
{
   return (str == "std::string" || str == "int");
}

std::string ReleaseInfoCppFileGenerator::header_file_content()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Blast::ReleaseInfoCppFileGenerator::header_file_content]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::ReleaseInfoCppFileGenerator::header_file_content]: error: guard \"initialized\" not met");
   }
   Blast::Cpp::ClassGenerator generator(cpp_class);
   return generator.generate_header_file_content();
}

std::string ReleaseInfoCppFileGenerator::source_file_content()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Blast::ReleaseInfoCppFileGenerator::source_file_content]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::ReleaseInfoCppFileGenerator::source_file_content]: error: guard \"initialized\" not met");
   }
   Blast::Cpp::ClassGenerator generator(cpp_class);
   return generator.generate_source_file_content();
}


} // namespace Blast


