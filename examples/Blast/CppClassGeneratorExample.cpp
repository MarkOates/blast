

#include <Blast/CppClassGenerator.hpp>

#include <iostream>


int main(int argc, char **argv)
{
   std::vector<Blast::SymbolDependencies> symbol_dependencies = {
      // some simple examples of dependencies (that do not need libraries to link against when compiled)
      { "int" },
      { "std::string", { "string" } },
      { "std::vector<std::string>", { "vector", "string" } },
      { "std::stringstream", { "sstream" } },
      { "std::cout", { "iostream" } },
      // some more complex examples
      { "ALLEGRO_BITMAP*", { "allegro5/allegro.h" }, { "~/Repos/username/allegro5/include" }, { "-lallegro" } },
      { "al_get_font_line_height", { "allegro5/allegro.h", "allegro5/allegro_font.h" }, { "~/Repos/username/allegro5/include" }, { "-lallegro_font" } },
      { "FSEventStreamRef", { "CoreServices/CoreServices.h" }, {}, { "-framework CoreServices" } },
      // dependencies for the parent class(es)
      { "AnimalBase", { "Animal/AnimalBase.hpp" } }
   };

   Blast::CppClassGenerator class_generator(
      "Kitten",
      { "MyProject" },
      { { "AnimalBase", "\"Kitten\"" } },
      {
         //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_argument, bool has_getter, bool has_setter
         { "int", "last_id", "0", true, false, true, false },
         { "int", "id", "last_id++", false, false, true, false },
         { "std::string", "name", "\"[unnamed]\"", false, false, true, true },
         { "std::vector<std::string>", "typeo", "{}", false, true, true, true },
         { "ALLEGRO_BITMAP*", "bmp", "nullptr", false, true, true, true },
      },
      symbol_dependencies
   );

   std::cout << "////////// header file ///////////" << std::endl;
   std::cout << class_generator.generate_header_file_content();
   std::cout << "////////// source file ///////////" << std::endl;
   std::cout << class_generator.generate_source_file_content();

   return 0;
}


