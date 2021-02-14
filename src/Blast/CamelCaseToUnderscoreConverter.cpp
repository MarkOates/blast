

#include <Blast/CamelCaseToUnderscoreConverter.hpp>
#include <algorithm>
#include <cctype>
#include <cctype>


namespace Blast
{


CamelCaseToUnderscoreConverter::CamelCaseToUnderscoreConverter(std::string str)
   : str(str)
{
}


CamelCaseToUnderscoreConverter::~CamelCaseToUnderscoreConverter()
{
}


std::string CamelCaseToUnderscoreConverter::convert_to_underscores()
{
   std::string camelCase = str;
   // Convert lowerCamelCase and UpperCamelCase strings to lower_with_underscore.
   std::string str(1, tolower(camelCase[0]));

   // First place underscores between contiguous lower and upper case letters.
   // For example, `_LowerCamelCase` becomes `_Lower_Camel_Case`.
   for (auto it = camelCase.begin() + 1; it != camelCase.end(); ++it) {
     if (isupper(*it) && *(it-1) != '_' && islower(*(it-1))) {
       str += "_";
     }
     str += *it;
   }

   // Then convert it to lower case.
   std::transform(str.begin(), str.end(), str.begin(), ::tolower);

   return str;
}
} // namespace Blast


