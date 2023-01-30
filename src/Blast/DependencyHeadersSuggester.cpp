

#include <Blast/DependencyHeadersSuggester.hpp>

#include <Blast/StringJoiner.hpp>


namespace Blast
{


DependencyHeadersSuggester::DependencyHeadersSuggester()
   : suggested_symbol_headers(get_default_suggested_symbol_headers())
{
}


DependencyHeadersSuggester::~DependencyHeadersSuggester()
{
}


std::vector<std::string> DependencyHeadersSuggester::suggested_headers(std::string symbol)
{
   if (suggested_symbol_headers.count(symbol) == 0) return {};
   return suggested_symbol_headers[symbol];
}

std::string DependencyHeadersSuggester::suggested_headers_csv(std::string symbol)
{
   return Blast::StringJoiner(suggested_headers(symbol), ", ").join();
}

std::map<std::string, std::vector<std::string>> DependencyHeadersSuggester::get_default_suggested_symbol_headers()
{
   return std::map<std::string, std::vector<std::string>>{
      { "ALLEGRO_FONT", { "allegro5/allegro_font.h" }, },
      { "ALLEGRO_BITMAP", { "allegro5/allegro.h" }, },
      { "ALLEGRO_DISPLAY", { "allegro5/allegro.h" }, },
      { "ALLEGRO_COLOR", { "allegro5/allegro.h" }, },
      { "StageInterface", { "Hexagon/StageInterface.hpp" }, },
      { "std::function", { "functional" }, },
      { "std::min", { "algorithm" }, },
      { "std::max", { "algorithm" }, },
      { "fmod", { "cmath" }, },
   };
}


} // namespace Blast


