

#include <Blast/Build/Celebrator.hpp>

#include <iomanip>
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


std::string Celebrator::generate_full_width_output_banner(std::string message, int width)
{
   char fill_char = '=';
   std::string decorated_message = "==== " + message + " ";

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
     "▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒",
     "▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒     █▀▀▀▀▄  █▀▀▀▀█  █▀▀▀▀▀  █▀▀▀▀▀    ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒",
     "▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒     █▄▄▄▄▀  █▄▄▄▄█  ▀▀▀▀▀█  ▀▀▀▀▀█    ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒",
     "▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒     ▀       ▀    ▀  ▀▀▀▀▀▀  ▀▀▀▀▀▀    ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒",
     "▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒ ▒",
   };

   std::stringstream stream;
   stream
     << std::left
     << std::setfill(fill_char)
     << std::setw(width)
     ;
   for (auto &line : lines)
   {
     stream
       << line
       << std::endl
       ;
   }
   return stream.str();
}


} // namespace Build
} // namespace Blast


