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
         static constexpr const char* DEFAULT_CLASS_NAME = (char*)"";
         static constexpr const char* DEFAULT_NAME_OF_TO_STRING_METHOD = (char*)"to_string";
         static constexpr const char* DEFAULT_SCOPE = (char*)"private";
         static constexpr const char* DEFAULT_TYPE = (char*)"uint32_t";

      private:
         std::string class_name;
         std::vector<std::string> enumerators;
         std::string scope;
         std::string type;
         std::string name_of_to_string_method;

      protected:


      public:
         EnumClass(std::string class_name=DEFAULT_CLASS_NAME, std::vector<std::string> enumerators={}, std::string scope=DEFAULT_SCOPE, std::string type=DEFAULT_TYPE);
         ~EnumClass();

         void set_class_name(std::string class_name);
         void set_name_of_to_string_method(std::string name_of_to_string_method);
         std::string get_class_name() const;
         std::vector<std::string> get_enumerators() const;
         std::string get_scope() const;
         std::string get_type() const;
         std::string get_name_of_to_string_method() const;
         void set_enumerators(std::vector<std::string> enumerators={});
         bool has_class_name();
         void set_scope(std::string scope="[unset-scope]");
         void set_type(std::string type="[unset-type]");
         bool is_private();
         bool is_protected();
         bool is_public();
         Blast::Cpp::Function build_to_string_method();
         std::string build_to_string_method_body();
         static bool validate(std::string method_name="[unset-method_name]");
         static bool validate_elements_are_unique(std::vector<std::string> elements={});
      };
   }
}



