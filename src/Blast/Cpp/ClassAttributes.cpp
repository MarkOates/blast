

#include <Blast/Cpp/ClassAttributes.hpp>

#include <sstream>


namespace Blast
{


namespace Cpp
{


ClassAttributes::ClassAttributes(
      std::string datatype,
      std::string variable_name,
      std::string initialization_value,
      bool is_static,
      bool is_constructor_parameter,
      bool has_getter,
      bool has_explicit_getter,
      bool has_getter_ref,
      bool has_setter,
      bool has_explicit_setter,
      bool is_constexpr,
      bool is_exposed
   )
   : datatype(datatype)
   , variable_name(variable_name)
   , initialization_value(initialization_value)
   , is_static(is_static)
   , is_constructor_parameter(is_constructor_parameter)
   , has_getter(has_getter)
   , has_explicit_getter(has_explicit_getter)
   , has_getter_ref(has_getter_ref)
   , has_setter(has_setter)
   , has_explicit_setter(has_explicit_setter)
   , is_constexpr(is_constexpr)
   , is_exposed(is_exposed)
{
}


ClassAttributes::~ClassAttributes()
{
}


std::string ClassAttributes::as_constructor_argument_in_declaration()
{
   if (!is_constructor_parameter) return "";
   if (is_static)
   {
      std::stringstream error_message;
      error_message << "Class attribute \"" << variable_name << "\" cannot be a constructor argument in a declaration; is static.";
      throw std::runtime_error(error_message.str());
   }

   std::stringstream result;
   result << datatype << " " << variable_name << "=" << initialization_value;
   return result.str();
}


std::string ClassAttributes::as_constructor_argument_in_definition()
{
   if (!is_constructor_parameter) return "";
   if (is_static)
   {
      std::stringstream error_message;
      error_message << "Class attribute \"" << variable_name << "\" cannot be a constructor argument in a definition; is static.";
      throw std::runtime_error(error_message.str());
   }

   std::stringstream result;
   result << datatype << " " << variable_name;
   return result.str();
}


std::string ClassAttributes::as_argument_in_initialization_list()

{
   std::stringstream result;
   result << variable_name << "(";
   if (is_constructor_parameter) result << variable_name;
   else result << initialization_value;
   result << ")";
   return result.str();
}


std::string ClassAttributes::as_class_property()
{
   std::stringstream result;
   if (is_static) result << "static ";
   if (is_constexpr) result << "constexpr ";
   result << datatype << " " << variable_name;
   if (is_constexpr) result << " = " << initialization_value;
   return result.str();
}


std::string ClassAttributes::as_static_definition(std::string class_name)
{
   if (is_constexpr) return "";
   std::stringstream result;
   result << datatype << " " << class_name << "::" << variable_name << " = " << initialization_value << ";";
   return result.str();
}


std::string ClassAttributes::getter_function_symbol()
{
   std::stringstream result;
   result << "get_" << variable_name;
   return result.str();
}


bool ClassAttributes::infer_getter_with_const()
{
   if (is_static) return false;
   return true;
}


std::string ClassAttributes::getter_function_declaration()
{
   std::stringstream result;
   if (is_static) result << "static ";
   result << datatype << " " << getter_function_symbol() << "()";
   if (infer_getter_with_const()) result << " const";
   result << ";";
   return result.str();
}


std::string ClassAttributes::getter_function_definition(std::string class_name)
{
   std::stringstream result;
   result << datatype << " " << class_name << "::get_" << variable_name << "()";
   if (infer_getter_with_const()) result << " const";
   result << "\n{\n   return " << variable_name << ";\n}\n";
   return result.str();
}


std::string ClassAttributes::getter_ref_function_symbol()
{
   std::stringstream result;
   result << "get_" << variable_name << "_ref";
   return result.str();
}


std::string ClassAttributes::getter_ref_function_declaration()
{
   std::stringstream result;
   if (is_static) result << "static ";
   result << datatype << " &" << getter_ref_function_symbol() << "();";
   return result.str();
}


std::string ClassAttributes::getter_ref_function_definition(std::string class_name)
{
   std::stringstream result;
   result << datatype << " &" << class_name << "::" << getter_ref_function_symbol() << "()\n{\n   return " << variable_name << ";\n}\n";
   return result.str();
}


std::string ClassAttributes::setter_function_symbol()
{
   std::stringstream result;
   result << "set_" << variable_name;
   return result.str();
}


std::string ClassAttributes::setter_function_declaration()
{
   if (is_static) throw std::runtime_error("Setter declarations are not implemented for static properties");

   std::stringstream result;
   result << "void " << setter_function_symbol() << "(" << datatype << " " << variable_name << ");";
   return result.str();
}


std::string ClassAttributes::setter_function_definition(std::string class_name)
{
   if (is_static) throw std::runtime_error("Setter definitions are not implemented for static properties");

   std::stringstream result;
   result << "void " << class_name << "::set_" << variable_name << "(" << datatype << " " << variable_name << ")\n{\n   this->" << variable_name << " = " << variable_name << ";\n}\n";
   return result.str();
}


} // namespace Cpp


} // namespace Blast
