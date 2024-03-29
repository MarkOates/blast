

#include <Blast/RegexMatcher.hpp>

#include <regex>


namespace Blast
{


RegexMatcher::RegexMatcher(std::string source_string, std::string regex_expression, std::vector<std::regex_constants::syntax_option_type> options)
   : source_string(source_string)
   , regex_expression(regex_expression)
   , options(options)
   , re({})
   , compiled(false)
{
}


RegexMatcher::~RegexMatcher()
{
}


void RegexMatcher::set_source_string(std::string source_string)
{
   this->source_string = source_string;
}


std::string RegexMatcher::get_source_string() const
{
   return source_string;
}


std::string RegexMatcher::get_regex_expression() const
{
   return regex_expression;
}


std::vector<std::regex_constants::syntax_option_type> RegexMatcher::get_options() const
{
   return options;
}


void RegexMatcher::set_regex_expression(std::string regex_expression)
{
   this->regex_expression = regex_expression;
   compiled = false;
   return;
}

void RegexMatcher::set_options(std::vector<std::regex_constants::syntax_option_type> options)
{
   this->options = options;
   compiled = false;
   return;
}

void RegexMatcher::compile()
{
   if (std::find(options.begin(), options.end(), std::regex::icase) != options.end())
   {
      re = std::regex(regex_expression, std::regex::icase);
   }
   else
   {
      re = std::regex(regex_expression);
   }
   compiled = true;
   return;
}

std::vector<std::pair<int, int>> RegexMatcher::get_match_info()
{
   if (!compiled) compile();

   std::vector<std::pair<int, int>> results;

   //std::string subject(source_string);
   try
   {
      //std::regex re("\\w+"); // find words
      //std::regex re;
      //if (std::find(options.begin(), options.end(), std::regex::icase) != options.end())
      //{
         //re = std::regex(regex_expression, std::regex::icase);
      //}
      //else
      //{
         //re = std::regex(regex_expression);
      //}

      std::sregex_iterator next(source_string.begin(), source_string.end(), re);
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


