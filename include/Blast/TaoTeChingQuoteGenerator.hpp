#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class TaoTeChingQuoteGenerator
   {
   private:
      std::vector<std::string> quotes;

   public:
      TaoTeChingQuoteGenerator(std::vector<std::string> quotes=TaoTeChingQuoteGenerator::generate_default_quotes_list());
      ~TaoTeChingQuoteGenerator();


   std::string pluck_quote();
   static std::vector<std::string> generate_default_quotes_list();
   };
}



