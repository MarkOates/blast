

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
   // note: the 4th argument casts std::toupper with a specific signature.  This is to prevent
   // a compile error on Windows that is unable to resolve which "std::toupper" function to use
   // see https://stackoverflow.com/a/16792532
   std::transform(
      result.begin(),
      result.end(),
      result.begin(),
      static_cast<int(*)(int)>(std::toupper)
   );
   return result;
}


} // namespace Blast


