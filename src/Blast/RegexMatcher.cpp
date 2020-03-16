

#include <Blast/RegexMatcher.hpp>
#include <regex>
#include <regex>
#include <regex>
#include <regex>
#include <regex>


namespace Blast
{


RegexMatcher::RegexMatcher(std::string source_string, std::string regex_expression, std::vector<std::regex_constants::syntax_option_type> options)
   : source_string(source_string)
   , regex_expression(regex_expression)
   , options(options)
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


std::vector<std::regex_constants::syntax_option_type> RegexMatcher::get_options()
{
   return options;
}


std::vector<std::pair<int, int>> RegexMatcher::get_match_info()
{
std::vector<std::pair<int, int>> results;

std::string subject(source_string);
try
{
   //std::regex re("\\w+"); // find words
   //std::regex re(regex_expression, std::regex::icase);
   std::regex re(regex_expression);

   std::sregex_iterator next(subject.begin(), subject.end(), re);
   std::sregex_iterator end;
   while (next != end)
   {
      std::smatch match = *next;
      //std::cout << " - string: " << match.str() << std::endl;
      //std::cout << "   position: " << match.position() << std::endl;
      //std::cout << "   length: " << match.str().size() << std::endl;
      results.push_back(std::pair<int, int>(match.position(), match.str().size()));
      next++;
   }
}
catch (std::regex_error& e)
{
   throw std::runtime_error("There was a syntax error in the regular expression");
}

return results;

}
} // namespace Blast


