

#include <Blast/CppClassGenerator.hpp>

#include <iostream>


int main(int argc, char **argv)
{
   std::vector<Blast::SymbolDependencies> symbol_dependencies = {
      // some simple examples of dependencies (that do not need libraries to link against when compiled)
      { "int" },
      { "std::string", "string" },
      { "std::vector", "vector" },
      { "std::stringstream", "sstream" },
      { "std::cout", "iostream" },
      // some more complex examples
      { "ALLEGRO_BITMAP", "allegro5/allegro.h", "~/Repos/username/allegro5/include", "-lallegro" },
      { "al_get_font_line_height", "allegro5/allegro_font.h", "~/Repos/username/allegro5/include", "-lallegro_font" },
      { "FSEventStreamRef", "CoreServices/CoreServices.h", "", "-framework CoreServices" },
   };

   Blast::CppClassGenerator class_generator("User", {
         //std::string datatype, std::string variable_name, std::string initialization_value, bool is_static, bool is_constructor_argument, bool has_getter, bool has_setter
         { "int", "id", "last_id++", false, false, true, false },
         { "std::string", "name", "\"[unnamed]\"", false, false, true, true },
         { "std::string", "type", "\"[untyped]\"", false, true, true, true },
         { "std::vector", "typeo", "\"[untyped]\"", false, true, true, true },
         { "ALLEGRO_BITMAP", "bmp", "\"[untyped]\"", false, true, true, true },
      },
      symbol_dependencies
   );

   class_generator.constructor_declaration_elements();
   class_generator.constructor_definition_elements();
   std::cout << "////////// header file ///////////" << std::endl;
   std::cout << class_generator.generate_header_file_content();
   std::cout << "////////// source file ///////////" << std::endl;
   std::cout << class_generator.generate_source_file_content();

   return 0;
}


