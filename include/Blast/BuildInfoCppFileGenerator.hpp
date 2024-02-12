#pragma once


#include <Blast/BuildInfo.hpp>
#include <Blast/Cpp/Class.hpp>
#include <Blast/Cpp/ClassAttributes.hpp>
#include <Blast/Cpp/Function.hpp>
#include <Blast/Cpp/SymbolDependencies.hpp>
#include <string>
#include <vector>


namespace Blast
{
   class BuildInfoCppFileGenerator
   {
   private:
      Blast::BuildInfo build_info;
      Blast::Cpp::Class cpp_class;
      bool initialized;

   protected:


   public:
      BuildInfoCppFileGenerator(Blast::BuildInfo build_info={});
      ~BuildInfoCppFileGenerator();

      Blast::BuildInfo get_build_info() const;
      void set_build_info(Blast::BuildInfo build_info={});
      void initialize();
      Blast::Cpp::Class build_cpp_class();
      std::vector<Blast::Cpp::Function> build_cpp_class_functions();
      std::vector<Blast::Cpp::ClassAttributes> build_cpp_class_attribute_properties();
      Blast::Cpp::Function build_get_cpp_version_function();
      Blast::Cpp::ClassAttributes build_cpp_class_attribute(std::string datatype="std::string", std::string variable_name="variable", std::string initialization_value="variable");
      std::vector<Blast::Cpp::SymbolDependencies> build_cpp_class_symbol_dependencies();
      std::string wrap_in_quotes(std::string str="");
      bool is_valid_datatype(std::string str="");
      std::string header_file_content();
      std::string source_file_content();
   };
}



