

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


std::string DependencyHeadersSuggester::generate_autofill_suggestion_for_symbol(std::string symbol)
{
   std::string header = __replace(symbol, "::", "/") + ".hpp";
   return header;
}

std::vector<std::string> DependencyHeadersSuggester::find_suggested_headers(std::string symbol, bool autogenerate_a_header_if_one_is_not_present)
{
   if (suggested_symbol_headers.count(symbol) == 0)
   {
      if (autogenerate_a_header_if_one_is_not_present) return { generate_autofill_suggestion_for_symbol(symbol) };
      return {};
   }
   return suggested_symbol_headers[symbol];
}

std::string DependencyHeadersSuggester::find_suggested_headers_csv(std::string symbol, bool autogenerate_a_header_if_one_is_not_present)
{
   return Blast::StringJoiner(
         find_suggested_headers(symbol, autogenerate_a_header_if_one_is_not_present),
         ", "
      ).join();
}

std::map<std::string, std::vector<std::string>> DependencyHeadersSuggester::get_default_suggested_symbol_headers()
{
   return std::map<std::string, std::vector<std::string>>{
      { "StageInterface", { "Hexagon/StageInterface.hpp" }, },
      { "std::function", { "functional" }, },
      { "std::min", { "algorithm" }, },
      { "std::max", { "algorithm" }, },
      { "fmod", { "cmath" }, },

      // Allegro
      { "ALLEGRO_EVENT", { "allegro5/allegro.h" }, },
      { "ALLEGRO_FONT", { "allegro5/allegro_font.h" }, },
      { "ALLEGRO_BITMAP", { "allegro5/allegro.h" }, },
      { "ALLEGRO_DISPLAY", { "allegro5/allegro.h" }, },
      { "ALLEGRO_COLOR", { "allegro5/allegro.h" }, },
      { "ALLEGRO_STATE", { "allegro5/allegro.h" }, },
      { "al_color_html", { "allegro5/allegro_color.h" }, },
      { "al_draw_rectangle", { "allegro5/allegro_primitives.h" }, },
      { "al_draw_filled_rectangle", { "allegro5/allegro_primitives.h" }, },
      { "al_draw_circle", { "allegro5/allegro_primitives.h" }, },
      { "al_draw_filled_circle", { "allegro5/allegro_primitives.h" }, },
   };
}

std::string DependencyHeadersSuggester::__replace(std::string str, std::string from, std::string to)
{
   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos) {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
   return str;
}


} // namespace Blast


