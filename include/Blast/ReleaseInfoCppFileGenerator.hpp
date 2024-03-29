#pragma once


#include <Blast/Cpp/Class.hpp>
#include <Blast/Cpp/ClassAttributes.hpp>
#include <Blast/Cpp/SymbolDependencies.hpp>
#include <Blast/ReleaseInfo.hpp>
#include <string>
#include <vector>


namespace Blast
{
   class ReleaseInfoCppFileGenerator
   {
   private:
      Blast::ReleaseInfo release_info;
      Blast::Cpp::Class cpp_class;
      bool initialized;

   protected:


   public:
      ReleaseInfoCppFileGenerator(Blast::ReleaseInfo release_info={});
      ~ReleaseInfoCppFileGenerator();

      Blast::ReleaseInfo get_release_info() const;
      void set_release_info(Blast::ReleaseInfo release_info={});
      void initialize();
      Blast::Cpp::Class build_cpp_class();
      std::vector<Blast::Cpp::ClassAttributes> build_cpp_class_attribute_properties();
      Blast::Cpp::ClassAttributes build_cpp_class_attribute(std::string datatype="std::string", std::string variable_name="variable", std::string initialization_value="variable");
      std::vector<Blast::Cpp::SymbolDependencies> build_cpp_class_symbol_dependencies();
      std::string wrap_in_quotes(std::string str="");
      bool is_valid_datatype(std::string str="");
      std::string header_file_content();
      std::string source_file_content();
   };
}



