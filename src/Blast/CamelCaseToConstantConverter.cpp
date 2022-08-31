

#include <Blast/CamelCaseToConstantConverter.hpp>

#include <algorithm>
#include <cctype>


namespace Blast
{


CamelCaseToConstantConverter::CamelCaseToConstantConverter(std::string str)
   : str(str)
{
}


CamelCaseToConstantConverter::~CamelCaseToConstantConverter()
{
}


std::string CamelCaseToConstantConverter::convert_to_constant()
{
   std::string camelCase = str;
   // Convert lowerCamelCase and UpperCamelCase strings to lower_with_underscore.
   std::string str(1, tolower(camelCase[0]));

   // First place underscores between contiguous lower and upper case letters.
   // For example,  becomes .
   for (auto it = camelCase.begin() + 1; it != camelCase.end(); ++it) {
     if (isupper(*it) && *(it-1) != '_' && islower(*(it-1))) {
       str += "_";
     }
     str += *it;
   }

   // Then convert it to lower case.
   std::transform(str.begin(), str.end(), str.begin(), ::toupper);

   return str;
}


} // namespace Blast


