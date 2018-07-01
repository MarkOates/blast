

#include <Blast/StringPadder.hpp>


namespace Blast
{


StringPadder::StringPadder(std::string string, int padding, char character)
   : string(string)
   , padding(padding)
   , character(character)
{
}


StringPadder::~StringPadder()
{
}


std::string StringPadder::pad()
{
   std::string s = string;
   if (padding > s.length()) s.append(padding - s.length(), character);
   return s;
}


} // namespace Blast



