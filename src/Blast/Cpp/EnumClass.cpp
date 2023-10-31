

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
   , name_of_to_string_method(DEFAULT_NAME_OF_TO_STRING_METHOD)
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


void EnumClass::set_name_of_to_string_method(std::string name_of_to_string_method)
{
   this->name_of_to_string_method = name_of_to_string_method;
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


std::string EnumClass::get_name_of_to_string_method() const
{
   return name_of_to_string_method;
}


void EnumClass::set_enumerators(std::vector<std::string> enumerators)
{
   if (!(validate_elements_are_unique(enumerators)))
   {
      std::stringstream error_message;
      error_message << "[EnumClass::set_enumerators]: error: guard \"validate_elements_are_unique(enumerators)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EnumClass::set_enumerators: error: guard \"validate_elements_are_unique(enumerators)\" not met");
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
      error_message << "[EnumClass::set_start_from]: error: guard \"(start_from >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EnumClass::set_start_from: error: guard \"(start_from >= 0)\" not met");
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
      error_message << "[EnumClass::build_to_string_method]: error: guard \"validate(name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EnumClass::build_to_string_method: error: guard \"validate(name)\" not met");
   }
   if (!(validate(name_of_to_string_method)))
   {
      std::stringstream error_message;
      error_message << "[EnumClass::build_to_string_method]: error: guard \"validate(name_of_to_string_method)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EnumClass::build_to_string_method: error: guard \"validate(name_of_to_string_method)\" not met");
   }
   // TODO: finish implementing this function
   Blast::Cpp::Function result(
      "std::string",
      name_of_to_string_method,
      std::vector<Blast::Cpp::FunctionArgument>({
         Blast::Cpp::FunctionArgument(name, "value"),
         Blast::Cpp::FunctionArgument("bool", "throw_on_error", "true"),
      })
   );
   return result;
}

std::string EnumClass::build_to_string_method_body()
{
   // TODO: implement this function, which will use a template
   Blast::TemplatedFile templated_file(
      "return \"unimplemented\";",
      {}
   );
   return "";
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
      error_message << "[EnumClass::validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise]: error: guard \"start_from >= 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EnumClass::validate_start_from_is_a_power_of_two_if_enumerators_are_bitwise: error: guard \"start_from >= 0\" not met");
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


