

#include <Blast/SymbolDependencies.hpp>

#include <iostream>
#include <vector>


int main(int, char**)
{
   std::vector<Blast::SymbolDependencies> symbol_dependencies = {
      // some simple examples of dependencies (that do not need libraries to link against when compiled)
      { "std::string", { "string" } },
      { "std::vector<std::vector>", { "string", "vector" } },
      { "std::stringstream", { "sstream" } },
      { "std::cout", { "iostream" } },
      // some more complex examples
      { "ALLEGRO_BITMAP", { "allegro5/allegro.h" }, { "~/Repos/username/allegro5/include" }, "-lallegro" },
      { "al_get_font_line_height", { "allegro5/allegro.h", "allegro5/allegro_font.h" }, { "~/Repos/username/allegro5/include" }, "-lallegro_font" },
      { "FSEventStreamRef", { "CoreServices/CoreServices.h" }, {}, "-framework CoreServices" },
   };

   for (auto &symbol_dependency : symbol_dependencies)
   {
      std::cout
         << "Using \""
         << symbol_dependency.get_symbol()
         << "\" requires that you have the include directives [ ";
         for (auto &include_directive : symbol_dependency.get_include_directives())
            std::cout << "\"" << include_directive << "\", ";
         std::cout << " ]";

      if (symbol_dependency.has_linked_library())
      {
         std::cout
            << " and link with \""
            << symbol_dependency.get_linked_library_name()
            << "\".";
      }

      std::cout << std::endl;
   }

   return 0;
}


