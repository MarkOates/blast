

#include <Blast/BuildInfoCppFileGenerator.hpp>

#include <Blast/Cpp/ClassGenerator.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Blast
{


BuildInfoCppFileGenerator::BuildInfoCppFileGenerator(Blast::BuildInfo build_info)
   : build_info(build_info)
   , cpp_class("")
   , initialized(false)
{
}


BuildInfoCppFileGenerator::~BuildInfoCppFileGenerator()
{
}


Blast::BuildInfo BuildInfoCppFileGenerator::get_build_info() const
{
   return build_info;
}


void BuildInfoCppFileGenerator::set_build_info(Blast::BuildInfo build_info)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[BuildInfoCppFileGenerator::set_build_info]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BuildInfoCppFileGenerator::set_build_info: error: guard \"(!initialized)\" not met");
   }
   this->build_info = build_info;
   return;
}

void BuildInfoCppFileGenerator::initialize()
{
   cpp_class = build_cpp_class();
   initialized = true;
   return;
}

Blast::Cpp::Class BuildInfoCppFileGenerator::build_cpp_class()
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
      "BuildInfo", // TODO: consider changing this to ThisBuildInfo
      {},
      {},
      build_cpp_class_attribute_properties(), // attribute_properties
      {}, // enum_classes
      {}, // functions
      build_cpp_class_symbol_dependencies(), // symbol_dependencies
      {} // function_body_symbol_dependencies
   );
}

std::vector<Blast::Cpp::ClassAttributes> BuildInfoCppFileGenerator::build_cpp_class_attribute_properties()
{
   std::vector<Blast::Cpp::ClassAttributes> result = {
      build_cpp_class_attribute("std::string", "time_of_build", build_info.get_time_of_build()),
      build_cpp_class_attribute("std::string", "building_platform_os_name", build_info.get_building_platform_os_name()),
      build_cpp_class_attribute("std::string", "building_platform_os_version", build_info.get_building_platform_os_version()),
      build_cpp_class_attribute("std::string", "building_platform_chipset", build_info.get_building_platform_chipset()),
      build_cpp_class_attribute("std::string", "compiler_name", build_info.get_compiler_name()),
      build_cpp_class_attribute("std::string", "compiler_version", build_info.get_compiler_version()),
      build_cpp_class_attribute("std::string", "allegro_version_num", build_info.get_allegro_version_num()),
      build_cpp_class_attribute("std::string", "allegro_version_git_branch", build_info.get_allegro_version_git_branch()),
      build_cpp_class_attribute("std::string", "allegro_version_git_hash", build_info.get_allegro_version_git_hash()),
      build_cpp_class_attribute(
         "std::string",
         "allegro_version_git_latest_commit_date_and_time",
         build_info.get_allegro_version_git_latest_commit_date_and_time()
      ),
      build_cpp_class_attribute(
         "int",
         "allegro_version_git_num_commits",
         std::to_string(build_info.get_allegro_version_git_num_commits())
      ),
   };
   return result;
}

Blast::Cpp::ClassAttributes BuildInfoCppFileGenerator::build_cpp_class_attribute(std::string datatype, std::string variable_name, std::string initialization_value)
{
   if (!(is_valid_datatype(datatype)))
   {
      std::stringstream error_message;
      error_message << "[BuildInfoCppFileGenerator::build_cpp_class_attribute]: error: guard \"is_valid_datatype(datatype)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BuildInfoCppFileGenerator::build_cpp_class_attribute: error: guard \"is_valid_datatype(datatype)\" not met");
   }
   return Blast::Cpp::ClassAttributes(
         datatype, //std::string datatype,
         variable_name, //std::string variable_name,
         (datatype == "std::string") ? wrap_in_quotes(initialization_value) : initialization_value, //std::string initialization_value,
         true, //bool is_static,
         false, //bool is_constructor_parameter,
         true, //bool has_getter,
         false, //bool has_expicit_getter,
         false, //bool has_getter_ref,
         false, //bool has_setter,
         false //bool is_constexpr
      );
}

std::vector<Blast::Cpp::SymbolDependencies> BuildInfoCppFileGenerator::build_cpp_class_symbol_dependencies()
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

std::string BuildInfoCppFileGenerator::wrap_in_quotes(std::string str)
{
   return "\"" + str + "\"";
}

bool BuildInfoCppFileGenerator::is_valid_datatype(std::string str)
{
   return (str == "std::string" || str == "int");
}

std::string BuildInfoCppFileGenerator::header_file_content()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BuildInfoCppFileGenerator::header_file_content]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BuildInfoCppFileGenerator::header_file_content: error: guard \"initialized\" not met");
   }
   Blast::Cpp::ClassGenerator generator(cpp_class);
   return generator.generate_header_file_content();
}

std::string BuildInfoCppFileGenerator::source_file_content()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[BuildInfoCppFileGenerator::source_file_content]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BuildInfoCppFileGenerator::source_file_content: error: guard \"initialized\" not met");
   }
   Blast::Cpp::ClassGenerator generator(cpp_class);
   return generator.generate_source_file_content();
}


} // namespace Blast


