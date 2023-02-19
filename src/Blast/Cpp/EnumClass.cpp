

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


EnumClass::EnumClass(std::string class_name, std::vector<std::string> enumerators, std::string scope)
   : class_name(class_name)
   , enumerators(enumerators)
   , scope(scope)
   , name_of_to_string_method(DEFAULT_NAME_OF_TO_STRING_METHOD)
{
}


EnumClass::~EnumClass()
{
}


void EnumClass::set_class_name(std::string class_name)
{
   this->class_name = class_name;
}


void EnumClass::set_name_of_to_string_method(std::string name_of_to_string_method)
{
   this->name_of_to_string_method = name_of_to_string_method;
}


std::string EnumClass::get_class_name() const
{
   return class_name;
}


std::vector<std::string> EnumClass::get_enumerators() const
{
   return enumerators;
}


std::string EnumClass::get_scope() const
{
   return scope;
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

bool EnumClass::has_class_name()
{
   return !class_name.empty();
}

void EnumClass::set_scope(std::string scope)
{
   // NOTE: this validation is not assured when the value is set during construction
   static std::set<std::string> valid_scopes = { "public", "private", "protected" };
   if (valid_scopes.count(scope) == 0)
   {
      throw std::runtime_error("[Blast::Cpp::EnumClass::set_scope]: error: scope is invalid");
   }
   this->scope = scope;
   return;
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
   if (!(validate(class_name)))
   {
      std::stringstream error_message;
      error_message << "[EnumClass::build_to_string_method]: error: guard \"validate(class_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EnumClass::build_to_string_method: error: guard \"validate(class_name)\" not met");
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
         Blast::Cpp::FunctionArgument(class_name, "value"),
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


