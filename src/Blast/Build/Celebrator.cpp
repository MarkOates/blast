

#include <Blast/Build/Celebrator.hpp>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


namespace Blast
{
namespace Build
{


Celebrator::Celebrator()
{
}


Celebrator::~Celebrator()
{
}


std::string Celebrator::generate_full_width_output_banner(std::string message, int width, char fill_char, std::size_t num_leading_fill_characters)
{
   std::string decorated_message = std::string(num_leading_fill_characters, fill_char) + " " + message + " ";

   std::stringstream stream;
   stream
     << std::left
     << std::setfill(fill_char)
     << std::setw(width)
     << decorated_message
     ;
   return stream.str();
}

std::string Celebrator::generate_pass_banner(int width)
{
   char fill_char = ' ';

   std::vector<std::string> lines = {
     "|---------- ruler ----------------------------------------------------------------------------------------------|",
     "▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒",
     "▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒     █▀▀▀▀▄  █▀▀▀▀█  █▀▀▀▀▀  █▀▀▀▀▀    ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒",
     "▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒     █▄▄▄▄▀  █▄▄▄▄█  ▀▀▀▀▀█  ▀▀▀▀▀█    ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒",
     "▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒     ▀       ▀    ▀  ▀▀▀▀▀▀  ▀▀▀▀▀▀    ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒",
     "▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒",
   };

   int banner_width = 0;

   // HACK
   // OK, the lengths of the strings are not being reported properly, probably because they might be wchars or the string
   // is using extended chars.  For now... as a hack... I'm going to manually set the length to 113.  See this stack
   // overflow for more info: https://stackoverflow.com/questions/4063146/getting-the-actual-length-of-a-utf-8-encoded-stdstring
   // Also, this webpage with a function to validate a utf8 string: http://www.zedwood.com/article/cpp-is-valid-utf8-string-function
   //banner_width = 113;

   if (!lines.empty())
   {
     // NOTE: assuming the first line is the ruler used to determine the length (see previous HACK comment) so will be
     // using the length of the first line until the number of "code points" can be calculated. Also, will be popping
     // off the first line because of this.
     banner_width = lines[0].length();
     lines.erase(lines.begin());
   }

   std::string CONSOLE_COLOR_GREEN = "\033[32m";
   std::string CONSOLE_COLOR_DEFAULT = "\033[0m";

   // DEBUG
   // TODO: Add a "debug_output" option, and add a --debug flag to the programs/build_celebrator

   int left_padding_width = std::max(0, (width - banner_width) / 2);
   std::string left_padding_str(left_padding_width, ' ');
   //std::cout << "banner_width: " << banner_width << std::endl;
   //std::cout << "width: " << width << std::endl;
   //std::cout << "left_padding_width: " << left_padding_width << std::endl;
   //std::cout << "left_padding: #" << left_padding_str << "#" << std::endl;

   std::stringstream stream;
   stream << CONSOLE_COLOR_GREEN;
   for (auto &line : lines)
   {
     stream
       << left_padding_str
       << line
       << std::endl
       ;
   }
   stream << CONSOLE_COLOR_DEFAULT;
   return stream.str();
}

std::string Celebrator::generate_component_built_banner(int width)
{
   char fill_char = ' ';

   std::vector<std::string> lines = {
     "|---------- ruler --------------------------------------------------------------------------------------|",
     "▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓",
     "▓▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒                                     ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒▓",
     "▓▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒           COMPONENT BUILT           ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒▓",
     "▓▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒                                     ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒▓",
     "▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓▒▓",
   };

   int banner_width = 0;

   // HACK
   // OK, the lengths of the strings are not being reported properly, probably because they might be wchars or the string
   // is using extended chars.  For now... as a hack... I'm going to manually set the length to 113.  See this stack
   // overflow for more info: https://stackoverflow.com/questions/4063146/getting-the-actual-length-of-a-utf-8-encoded-stdstring
   // Also, this webpage with a function to validate a utf8 string: http://www.zedwood.com/article/cpp-is-valid-utf8-string-function
   //banner_width = 113;

   if (!lines.empty())
   {
     // NOTE: assuming the first line is the ruler used to determine the length (see previous HACK comment) so will be
     // using the length of the first line until the number of "code points" can be calculated. Also, will be popping
     // off the first line because of this.
     banner_width = lines[0].length();
     lines.erase(lines.begin());
   }

   std::string CONSOLE_COLOR_GREEN = "\033[32m";
   std::string CONSOLE_COLOR_DEFAULT = "\033[0m";

   // DEBUG
   // TODO: Add a "debug_output" option, and add a --debug flag to the programs/build_celebrator

   int left_padding_width = std::max(0, (width - banner_width) / 2);
   std::string left_padding_str(left_padding_width, ' ');
   //std::cout << "banner_width: " << banner_width << std::endl;
   //std::cout << "width: " << width << std::endl;
   //std::cout << "left_padding_width: " << left_padding_width << std::endl;
   //std::cout << "left_padding: #" << left_padding_str << "#" << std::endl;

   std::stringstream stream;
   stream << CONSOLE_COLOR_GREEN;
   for (auto &line : lines)
   {
     stream
       << left_padding_str
       << line
       << std::endl
       ;
   }
   stream << CONSOLE_COLOR_DEFAULT;
   return stream.str();
}


} // namespace Build
} // namespace Blast


