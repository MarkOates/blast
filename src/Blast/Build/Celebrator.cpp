

#include <Blast/Build/Celebrator.hpp>

#include <iomanip>
#include <sstream>
#include <string>


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


} // namespace Build
} // namespace Blast


