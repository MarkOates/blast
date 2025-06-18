

#include <Blast/Cpp/EnumClass.hpp>

#include <Blast/Cpp/FunctionArgument.hpp>
#include <Blast/TemplatedFile.hpp>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <unordered_set>
#include <vector>


namespace Blast
{
namespace Cpp
{


EnumClass::EnumClass(std::string name, std::vector<std::string> enumerators, bool is_class)
   : name(name)
   , enumerators(enumerators)
   , scope(DEFAULT_SCOPE)
   , type(DEFAULT_TYPE)
   , is_class(is_class)
   , start_from(0)
   , enumerators_are_bitwise(false)
   , has_to_string_method(false)
   , name_of_to_string_method(DEFAULT_NAME_OF_TO_STRING_METHOD)
   , has_from_string_method(false)
   , name_of_from_string_method(DEFAULT_NAME_OF_FROM_STRING_METHOD)
{
}


EnumClass::~EnumClass()
{
}


void EnumClass::set_name(std::string name)
{
   this->name = name;
}


void EnumClass::set_is_class(bool is_class)
{
   this->is_class = is_class;
}


void EnumClass::set_has_to_string_method(bool has_to_string_method)
{
   this->has_to_string_method = has_to_string_method;
}


void EnumClass::set_name_of_to_string_method(std::string name_of_to_string_method)
{
   this->name_of_to_string_method = name_of_to_string_method;
}


void EnumClass::set_has_from_string_method(bool has_from_string_method)
{
   this->has_from_string_method = has_from_string_method;
}


void EnumClass::set_name_of_from_string_method(std::string name_of_from_string_method)
{
   this->name_of_from_string_method = name_of_from_string_method;
}


std::string EnumClass::get_name() const
{
   return name;
}


std::vector<std::string> EnumClass::get_enumerators() const
{
   return enumerators;
}


std::string EnumClass::get_scope() const
{
   return scope;
}


std::string EnumClass::get_type() const
{
   return type;
}


bool EnumClass::get_is_class() const
{
   return is_class;
}


int EnumClass::get_start_from() const
{
   return start_from;
}


bool EnumClass::get_enumerators_are_bitwise() const
{
   return enumerators_are_bitwise;
}


bool EnumClass::get_has_to_string_method() const
{
   return has_to_string_method;
}


std::string EnumClass::get_name_of_to_string_method() const
{
   return name_of_to_string_method;
}


bool EnumClass::get_has_from_string_method() const
{
   return has_from_string_method;
}


std::string EnumClass::get_name_of_from_string_method() const
{
   return name_of_from_string_method;
}


void EnumClass::set_enumerators(std::vector<std::string> enumerators)
{
   if (!(validate_elements_are_unique(enumerators)))
   {
      std::stringstream error_message;
      error_message << "[Blast::Cpp::EnumClass::set_enumerators]: error: guard \"validate_elements_are_unique(enumerators)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Cpp::EnumClass::set_enumerators]: error: guard \"validate_elements_are_unique(enumerators)\" not met");
   }
   this->enumerators = enumerators;
   return;
}

bool EnumClass::has_name()
{
   return !name.empty();
}

void EnumClass::set_scope(std::string scope)
{
   // NOTE: this validation is not assured when the value is set during construction
   // TODO: add test for this method
   static std::set<std::string> valid_scopes = { "public", "private", "protected" };
   if (valid_scopes.count(scope) == 0)
   {
      // TODO: include incorrect type, and valid types in error message
      throw std::runtime_error("[Blast::Cpp::EnumClass::set_scope]: error: scope is invalid");
   }
   this->scope = scope;
   return;
}

void EnumClass::set_type(std::string type)
{
   // NOTE: this validation is not assured when the value is set during construction
   // TODO: add test for this method
   static std::set<std::string> valid_types = { "", "int", "int16_t", "uint16_t", "int32_t", "uint32_t" };
   if (valid_types.count(type) == 0)
   {
      // TODO: include incorrect type, and valid types in error message
      std::stringstream error_message;
      error_message << "[Blast::Cpp::EnumClass::set_type]: error: The provided type \"" << type << "\" is invalid. ";
      error_message << "Permitted types are [";
      for (auto &valid_type : valid_types)
      {
         error_message << "\"" << valid_type << "\"" << ", ";
      }
      error_message << "]";
      throw std::runtime_error(error_message.str());
   }
   this->type = type;
   return;
}

void EnumClass::set_start_from(int start_from)
{
   if (!((start_from >= 0)))
   {
      std::stringstream error_message;
      error_message << "[Blast::Cpp::EnumClass::set_start_from]: error: guard \"(start_from >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Cpp::EnumClass::set_start_from]: error: guard \"(start_from >= 0)\" not met");
   }
   // TODO: add test for this method
   validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise(enumerators_are_bitwise, start_from);
   this->start_from = start_from;
   return;
}

void EnumClass::set_enumerators_are_bitwise(bool enumerators_are_bitwise)
{
   // TODO: add test for this method
   validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise(enumerators_are_bitwise, start_from);
   this->enumerators_are_bitwise = enumerators_are_bitwise;
   return;
}

bool EnumClass::has_type()
{
   return (!type.empty());
}

bool EnumClass::is_private()
{
   return scope == "private";
}

bool EnumClass::is_protected()
{
   return scope == "protected";
}

bool EnumClass::is_public()
{
   return scope == "public";
}

Blast::Cpp::Function EnumClass::build_to_string_method()
{
   if (!(validate(name)))
   {
      std::stringstream error_message;
      error_message << "[Blast::Cpp::EnumClass::build_to_string_method]: error: guard \"validate(name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Cpp::EnumClass::build_to_string_method]: error: guard \"validate(name)\" not met");
   }
   if (!(validate_permit_upper(name_of_to_string_method)))
   {
      std::stringstream error_message;
      error_message << "[Blast::Cpp::EnumClass::build_to_string_method]: error: guard \"validate_permit_upper(name_of_to_string_method)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Cpp::EnumClass::build_to_string_method]: error: guard \"validate_permit_upper(name_of_to_string_method)\" not met");
   }
   // TODO: finish implementing this function
   if (enumerators.empty())
   {
      throw std::runtime_error(
         "[Blast::Cpp::EnumClass::build_to_string_method]: error: "
            "\"enumerators\" cannot be empty because the first enumerator is used as a default value. Feel free "
               "improve this feature possibly by expanding the \"to_string: \" feature with additional data, "
               "adding a \"to_string_default_argument\", or another better idea."
      );
   }

   std::string argument_default_value = name + "::" + enumerators[0]; // NOTE: Using the first enum as the default argument
   Blast::Cpp::Function result(
      "std::string",
      name_of_to_string_method,
      std::vector<Blast::Cpp::FunctionArgument>({
         Blast::Cpp::FunctionArgument(name, "value", argument_default_value),
         Blast::Cpp::FunctionArgument("bool", "throw_on_error", "true"),
      }),
      build_to_string_method_body(),
      true, // is_static
      false // is_const (false, static methods cannot be const)
   );
   return result;
}

std::string EnumClass::build_to_string_method_body()
{
   // TODO: improve this function, consider using a static list of names rather that defining them in this method
   std::stringstream result;
   for (auto &enumerator : enumerators)
   {
      result << "if (value == " << name << "::" << enumerator << ") return \"" << to_lower(enumerator) << "\";" << std::endl;
   }
   result << "// TODO: Implement \"throw_on_error\" argument" << std::endl;
   result << "return \"\";" << std::endl;
   //Blast::TemplatedFile templated_file(
      //"return \"unimplemented\";",
      //{}
   //);
   //return templated_file.generate_content();
   return result.str();
}

Blast::Cpp::Function EnumClass::build_from_string_method()
{
   if (!(validate(name)))
   {
      std::stringstream error_message;
      error_message << "[Blast::Cpp::EnumClass::build_from_string_method]: error: guard \"validate(name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Cpp::EnumClass::build_from_string_method]: error: guard \"validate(name)\" not met");
   }
   if (!(validate_permit_upper(name_of_from_string_method)))
   {
      std::stringstream error_message;
      error_message << "[Blast::Cpp::EnumClass::build_from_string_method]: error: guard \"validate_permit_upper(name_of_from_string_method)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Cpp::EnumClass::build_from_string_method]: error: guard \"validate_permit_upper(name_of_from_string_method)\" not met");
   }
   // TODO: finish implementing this function
   if (enumerators.empty())
   {
      throw std::runtime_error(
         "[Blast::Cpp::EnumClass::build_from_string_method]: error: "
            "\"enumerators\" cannot be empty because the first enumerator is used as a default value. Feel free "
               "improve this feature possibly by expanding the \"to_string: \" feature with additional data, "
               "adding a \"to_string_default_argument\", or another better idea."
      );
   }
   std::string argument_default_value = "\"[unset-value]\"";
   //std::string argument_default_value = enumerators[0]; // NOTE: Using the first enum as the default argument
   Blast::Cpp::Function result(
      name, //"std::string",
      name_of_from_string_method,
      std::vector<Blast::Cpp::FunctionArgument>({
         //Blast::Cpp::FunctionArgument("std::string", "value"),
         Blast::Cpp::FunctionArgument("std::string", "value", argument_default_value),
         Blast::Cpp::FunctionArgument("bool", "throw_on_error", "true"),
      }),
      build_from_string_method_body(),
      true, // is_static
      false // is_const (false, static methods cannot be const)
   );
   return result;
}

std::string EnumClass::build_from_string_method_body()
{
   // TODO: improve this function, consider using a static list of names rather that defining them in this method
   std::stringstream result;
   for (auto &enumerator : enumerators)
   {
      std::string string_value = to_lower(enumerator);
      std::stringstream enum_value;
      enum_value << name << "::" << enumerator;
      result << "if (value == \"" << string_value << "\") return " << enum_value.str() << ";" << std::endl;
   }
   result << "throw std::runtime_error(\"Blast/Cpp/EnumClass: ERROR: Could not find enum for \\\" + value + \\\"\");";
   result << std::endl;
   //result << "return << " << name << "::" << \"error\";" << std::endl;
   //Blast::TemplatedFile templated_file(
      //"return \"unimplemented\";",
      //{}
   //);
   //return templated_file.generate_content();
   return result.str();
}

bool EnumClass::validate(std::string method_name)
{
   // TODO: test this function

   // Check if string is at least 3 characters long
   if (method_name.length() < 3) {
      return false;
   }

   // Check if string has only lowercase and underscore characters
   for (char c : method_name) {
      if (!std::islower(c) && c != '_' && !std::isupper(c)) {
         return false;
      }
   }
   return true;
}

bool EnumClass::validate_permit_upper(std::string method_name)
{
   // TODO: test this function

   // Check if string is at least 3 characters long
   if (method_name.length() < 3) {
      return false;
   }

   // Check if string has only lowercase and underscore characters
   for (char c : method_name) {
      if (!std::islower(c) && c != '_') {
         return false;
      }
   }
   return true;
}

std::string EnumClass::to_lower(std::string value)
{
   std::string result;
   result.reserve(value.size());

   for (char c : value)
   {
      result += std::tolower(static_cast<unsigned char>(c));
   }

   return result;
}

bool EnumClass::is_power_of_two(uint32_t n)
{
   // TODO: Test this
    if (n == 0) return true;
    return (n > 0) && ((n & (n - 1)) == 0);
}

bool EnumClass::validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise(bool enumerators_are_bitwise, int start_from)
{
   if (!(start_from >= 0))
   {
      std::stringstream error_message;
      error_message << "[Blast::Cpp::EnumClass::validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise]: error: guard \"start_from >= 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Blast::Cpp::EnumClass::validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise]: error: guard \"start_from >= 0\" not met");
   }
   // TODO: Test this
   if (!enumerators_are_bitwise) return true;
   if (!is_power_of_two(start_from))
   {
      throw std::runtime_error(
         "[Blast::Cpp::EnumClass::validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise]: error: "
            "\"enumerators_are_bitwise\" is set to true, and thus \"start_from\" must be a power of two but it "
            "is not."
      );
   }
   return true;
}

bool EnumClass::validate_elements_are_unique(std::vector<std::string> elements)
{
   // TODO: move this function into an isolated class, or class with a set of validation functions
   std::unordered_set<std::string> unique_set;
   for (const auto& element : elements)
   {
      if (!unique_set.insert(element).second)
      {
          return false;
      }
   }
   return true;
}


} // namespace Cpp
} // namespace Blast


