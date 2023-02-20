

#include <Blast/Cpp/EnumClassFormatter.hpp>

#include <sstream>


namespace Blast
{
namespace Cpp
{


EnumClassFormatter::EnumClassFormatter(Blast::Cpp::EnumClass enum_class)
   : enum_class(enum_class)
{
}


EnumClassFormatter::~EnumClassFormatter()
{
}


std::string EnumClassFormatter::build_enum_definition()
{
   std::stringstream result;
   result << "enum";

   // Only show "class Foobar" if it is present
   if (enum_class.get_is_class() && enum_class.has_name())
   {
      result << " class";
   }
   // Only show if a type is present
   if (enum_class.has_name())
   {
      result << " " << enum_class.get_name();
   }
   // Only show ": type" if a type is present
   if (enum_class.has_type())
   {
      result << " : " << enum_class.get_type();
   }

   result << std::endl;
   result << "{" << std::endl;
   bool is_first_item = true;
   for (auto &item : enum_class.get_enumerators())
   {
      result << "   " << item;
      if (is_first_item)
      {
         result << " = 0";
         is_first_item = false;
      }
      result << ",";
      result << std::endl;
   }
   result << "};" << std::endl;
   return result.str();
}


} // namespace Cpp
} // namespace Blast


