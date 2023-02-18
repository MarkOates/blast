

#include <Blast/Cpp/EnumClass.hpp>

#include <Blast/Cpp/FunctionArgument.hpp>
#include <Blast/TemplatedFile.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>


namespace Blast
{
namespace Cpp
{


EnumClass::EnumClass(std::string enum_name, std::set<std::string> elements)
   : enum_name(enum_name)
   , elements(elements)
   , name_of_to_string_method(DEFAULT_NAME_OF_TO_STRING_METHOD)
{
}


EnumClass::~EnumClass()
{
}


void EnumClass::set_enum_name(std::string enum_name)
{
   this->enum_name = enum_name;
}


void EnumClass::set_elements(std::set<std::string> elements)
{
   this->elements = elements;
}


void EnumClass::set_name_of_to_string_method(std::string name_of_to_string_method)
{
   this->name_of_to_string_method = name_of_to_string_method;
}


std::string EnumClass::get_enum_name() const
{
   return enum_name;
}


std::set<std::string> EnumClass::get_elements() const
{
   return elements;
}


std::string EnumClass::get_name_of_to_string_method() const
{
   return name_of_to_string_method;
}


Blast::Cpp::Function EnumClass::build_to_string_method()
{
   if (!(validate(enum_name)))
   {
      std::stringstream error_message;
      error_message << "[EnumClass::build_to_string_method]: error: guard \"validate(enum_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EnumClass::build_to_string_method: error: guard \"validate(enum_name)\" not met");
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
         Blast::Cpp::FunctionArgument(enum_name, "value"),
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


} // namespace Cpp
} // namespace Blast


