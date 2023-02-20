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
         static constexpr const char* DEFAULT_TYPE = (char*)"";

      private:
         std::string name;
         std::vector<std::string> enumerators;
         std::string scope;
         std::string type;
         bool is_class;
         std::string name_of_to_string_method;

      protected:


      public:
         EnumClass(std::string name=DEFAULT_CLASS_NAME, std::vector<std::string> enumerators={}, std::string scope=DEFAULT_SCOPE, std::string type=DEFAULT_TYPE, bool is_class=false);
         ~EnumClass();

         void set_name(std::string name);
         void set_is_class(bool is_class);
         void set_name_of_to_string_method(std::string name_of_to_string_method);
         std::string get_name() const;
         std::vector<std::string> get_enumerators() const;
         std::string get_scope() const;
         std::string get_type() const;
         bool get_is_class() const;
         std::string get_name_of_to_string_method() const;
         void set_enumerators(std::vector<std::string> enumerators={});
         bool has_name();
         void set_scope(std::string scope="[unset-scope]");
         void set_type(std::string type="[unset-type]");
         bool has_type();
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



