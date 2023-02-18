#pragma once


#include <Blast/Cpp/Function.hpp>
#include <string>
#include <vector>


namespace Blast
{
   namespace Cpp
   {
      class EnumClass
      {
      public:
         static constexpr const char* DEFAULT_NAME_OF_TO_STRING_METHOD = (char*)"to_string";

      private:
         std::string enum_name;
         std::vector<std::string> elements;
         std::string name_of_to_string_method;

      protected:


      public:
         EnumClass(std::string enum_name="[unset-enum_name]", std::vector<std::string> elements={});
         ~EnumClass();

         void set_enum_name(std::string enum_name);
         void set_elements(std::vector<std::string> elements);
         void set_name_of_to_string_method(std::string name_of_to_string_method);
         std::string get_enum_name() const;
         std::vector<std::string> get_elements() const;
         std::string get_name_of_to_string_method() const;
         Blast::Cpp::Function build_to_string_method();
         std::string build_to_string_method_body();
         static bool validate(std::string method_name="[unset-method_name]");
      };
   }
}



