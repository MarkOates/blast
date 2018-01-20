

#include <Blast/ClassAttributeProperties.hpp>

#include <sstream>


ClassAttributeProperties::ClassAttributeProperties(std::string datatype, std::string variable_name, std::string initialization_value, bool is_constructor_parameter, bool has_getter, bool has_setter)
   : datatype(datatype)
   , variable_name(variable_name)
   , initialization_value(initialization_value)
   , is_constructor_parameter(is_constructor_parameter)
   , has_getter(has_getter)
   , has_setter(has_setter)
{
}


ClassAttributeProperties::~ClassAttributeProperties()
{
}


std::string ClassAttributeProperties::as_constructor_argument_in_declaration()
{
   if (!is_constructor_parameter) return "";

   std::stringstream result;
   result << datatype << " " << variable_name << "=" << initialization_value;
   return result.str();
}


std::string ClassAttributeProperties::as_constructor_argument_in_definition()
{
   if (!is_constructor_parameter) return "";

   std::stringstream result;
   result << datatype << " " << variable_name;
   return result.str();
}


std::string ClassAttributeProperties::as_argument_in_initialization_list()

{
   std::stringstream result;
   result << variable_name << "(";
   if (is_constructor_parameter) result << variable_name;
   else result << initialization_value;
   result << ")";
   return result.str();
}


