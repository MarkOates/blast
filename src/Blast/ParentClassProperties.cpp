

#include <Blast/ParentClassProperties.hpp>

#include <sstream>


namespace Blast
{


static const std::vector<std::string> SCOPE_SPECIFIERS = { "public", "private", "protected" };


ParentClassProperties::ParentClassProperties(std::string class_name, std::string constructor_arguments, std::string scope_specifier)
   : class_name(class_name)
   , constructor_arguments(constructor_arguments)
   , scope_specifier(scope_specifier)
{
   __validate_scope_specifier(true);
}


ParentClassProperties::~ParentClassProperties()
{
}


bool ParentClassProperties::__validate_scope_specifier(bool raise_on_error)
{
   bool found = std::find(SCOPE_SPECIFIERS.begin(), SCOPE_SPECIFIERS.end(), scope_specifier) != SCOPE_SPECIFIERS.end();
   if (raise_on_error && !found)
   {
      std::stringstream error_message;
      error_message << "Invalid scope_specifier, must be one of [";
      for (auto &value : SCOPE_SPECIFIERS) error_message << "\"" << value << "\", ";
      error_message << "]";
      throw std::invalid_argument(error_message.str());
   }
   return found;
}


void ParentClassProperties::set_class_name(std::string class_name)
{
   this->class_name = class_name;
}


void ParentClassProperties::set_constructor_arguments(std::string constructor_arguments)
{
   this->constructor_arguments = constructor_arguments;
}


void ParentClassProperties::set_scope_specifier(std::string scope_specifier)
{
   this->scope_specifier = scope_specifier;
   __validate_scope_specifier(true);
}


std::string ParentClassProperties::get_class_name()
{
   return class_name;
}


std::string ParentClassProperties::get_constructor_arguments()
{
   return constructor_arguments;
}


std::string ParentClassProperties::get_scope_specifier()
{
   return scope_specifier;
}


std::string ParentClassProperties::as_class_inheritence_declaration()
{
   std::stringstream result;
   result << scope_specifier << ' ' << class_name;
   return result.str();
}


std::string ParentClassProperties::as_argument_in_initialization_list()
{
   std::stringstream result;
   result << class_name << '(' << constructor_arguments << ')';
   return result.str();
}


} // namespace Blast


