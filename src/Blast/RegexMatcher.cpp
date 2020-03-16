

#include <Blast/RegexMatcher.hpp>



namespace Blast
{


RegexMatcher::RegexMatcher(std::string source_string, std::string regex_expression)
   : source_string(source_string)
   , regex_expression(regex_expression)
{
}


RegexMatcher::~RegexMatcher()
{
}


std::string RegexMatcher::get_source_string()
{
   return source_string;
}


std::string RegexMatcher::get_regex_expression()
{
   return regex_expression;
}


std::vector<std::pair<int, int>> RegexMatcher::get_match_info()
{
return {};

}
} // namespace Blast


