#pragma once


#include <Blast/Cpp/Function.hpp>
#include <cstdint>
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
         static constexpr const char* DEFAULT_NAME_OF_FROM_STRING_METHOD = (char*)"from_string";
         static constexpr const char* DEFAULT_SCOPE = (char*)"private";
         static constexpr const char* DEFAULT_TYPE = (char*)"";

      private:
         std::string name;
         std::vector<std::string> enumerators;
         std::string scope;
         std::string type;
         bool is_class;
         int start_from;
         bool enumerators_are_bitwise;
         std::string name_of_to_string_method;
         std::string name_of_from_string_method;

      protected:


      public:
         EnumClass(std::string name=DEFAULT_CLASS_NAME, std::vector<std::string> enumerators={}, bool is_class=false);
         ~EnumClass();

         void set_name(std::string name);
         void set_is_class(bool is_class);
         void set_name_of_to_string_method(std::string name_of_to_string_method);
         void set_name_of_from_string_method(std::string name_of_from_string_method);
         std::string get_name() const;
         std::vector<std::string> get_enumerators() const;
         std::string get_scope() const;
         std::string get_type() const;
         bool get_is_class() const;
         int get_start_from() const;
         bool get_enumerators_are_bitwise() const;
         std::string get_name_of_to_string_method() const;
         std::string get_name_of_from_string_method() const;
         void set_enumerators(std::vector<std::string> enumerators={});
         bool has_name();
         void set_scope(std::string scope="[unset-scope]");
         void set_type(std::string type="[unset-type]");
         void set_start_from(int start_from=0);
         void set_enumerators_are_bitwise(bool enumerators_are_bitwise=false);
         bool has_type();
         bool is_private();
         bool is_protected();
         bool is_public();
         Blast::Cpp::Function build_to_string_method();
         std::string build_to_string_method_body();
         Blast::Cpp::Function build_from_string_method();
         std::string build_from_string_method_body();
         static bool validate(std::string method_name="[unset-method_name]");
         static bool validate_permit_upper(std::string method_name="[unset-method_name]");
         std::string to_lower(std::string value="[unset-value]");
         static bool is_power_of_two(uint32_t n=0);
         static bool validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise(bool enumerators_are_bitwise=false, int start_from=false);
         static bool validate_elements_are_unique(std::vector<std::string> elements={});
      };
   }
}



