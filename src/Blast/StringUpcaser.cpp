

#include <Blast/StringUpcaser.hpp>
#include <algorithm>
#include <cctype>


namespace Blast
{


StringUpcaser::StringUpcaser(std::string original_text)
   : original_text(original_text)
{
}


StringUpcaser::~StringUpcaser()
{
}


std::string StringUpcaser::upcase()
{
   std::string result = original_text;
   std::transform(result.begin(), result.end(), result.begin(), std::toupper);
   return result;
}
} // namespace Blast


