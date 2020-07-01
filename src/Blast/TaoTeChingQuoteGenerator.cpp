

#include <Blast/TaoTeChingQuoteGenerator.hpp>
#include <algorithm>
#include <iterator>
#include <random>
#include <random>


namespace Blast
{


TaoTeChingQuoteGenerator::TaoTeChingQuoteGenerator(std::vector<std::string> quotes)
   : quotes(quotes)
{
}


TaoTeChingQuoteGenerator::~TaoTeChingQuoteGenerator()
{
}


std::string TaoTeChingQuoteGenerator::pick_quote()
{
if (quotes.empty()) return "";
std::vector<std::string> result;
std::sample(quotes.begin(), quotes.end(), std::back_inserter(result), 1, std::mt19937{std::random_device{}()});
return result[0];

}

std::vector<std::string> TaoTeChingQuoteGenerator::default_quotes_list()
{
return {
  "Hello World!",
};

}
} // namespace Blast


