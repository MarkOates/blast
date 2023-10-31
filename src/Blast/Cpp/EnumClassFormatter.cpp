

#include <Blast/Cpp/EnumClassFormatter.hpp>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>


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


std::string EnumClassFormatter::build_enum_definition(int indent_num_spaces)
{
   if (!((indent_num_spaces >= 0)))
   {
      std::stringstream error_message;
      error_message << "[EnumClassFormatter::build_enum_definition]: error: guard \"(indent_num_spaces >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EnumClassFormatter::build_enum_definition: error: guard \"(indent_num_spaces >= 0)\" not met");
   }
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
   int start_from = enum_class.get_start_from();
   for (auto &item : enum_class.get_enumerators())
   {
      result << std::string(indent_num_spaces, ' ') << item;
      if (is_first_item)
      {
         result << " = " << start_from;
         is_first_item = false;
      }
      result << ",";
      result << std::endl;
   }
   result << "};" << std::endl;
   return result.str();
}

std::string EnumClassFormatter::output_nth_bit_as_hex_string(int n)
{
   if (!((n >= 0)))
   {
      std::stringstream error_message;
      error_message << "[EnumClassFormatter::output_nth_bit_as_hex_string]: error: guard \"(n >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("EnumClassFormatter::output_nth_bit_as_hex_string: error: guard \"(n >= 0)\" not met");
   }
   std::stringstream output;
   int i=0;
   if (n == 0) i = 0;
   else
   {
      i = (1 << (n-1));
   }
   output << "0x" << std::setfill('0') << std::setw(4) << std::hex << i;
   return output.str();
}


} // namespace Cpp
} // namespace Blast


