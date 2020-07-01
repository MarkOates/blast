

#include <Blast/TaoTeChingQuoteGenerator.hpp>



namespace Blast
{


TaoTeChingQuoteGenerator::TaoTeChingQuoteGenerator(std::vector<std::string> quotes)
   : quotes(quotes)
{
}


TaoTeChingQuoteGenerator::~TaoTeChingQuoteGenerator()
{
}


std::string TaoTeChingQuoteGenerator::pluck_quote()
{
return "Hello World!";

}

std::vector<std::string> TaoTeChingQuoteGenerator::generate_default_quotes_list()
{
return {};

}
} // namespace Blast


