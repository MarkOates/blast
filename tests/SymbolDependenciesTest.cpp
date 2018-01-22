#include <gtest/gtest.h>


#include <Blast/SymbolDependencies.hpp>


TEST(SymbolDependenciesTest, can_be_created)
{
   Blast::SymbolDependencies symbol_dependencies("std::string", "string");
}


TEST(SymbolDependenciesTest, when_created_without_arguments_sets_the_expected_values)
{
   Blast::SymbolDependencies symbol_dependencies("std::string", "string");

   ASSERT_EQ("", symbol_dependencies.get_dependency_include_directory());
   ASSERT_EQ("", symbol_dependencies.get_linked_library_name());
}


TEST(SymbolDependenciesTest, can_get_and_set_symbol)
{
   Blast::SymbolDependencies symbol_dependencies("std::string", "string");

   ASSERT_EQ("std::string", symbol_dependencies.get_symbol());
   symbol_dependencies.set_symbol("int");
   ASSERT_EQ("int", symbol_dependencies.get_symbol());
   symbol_dependencies.set_symbol("type_t");
   ASSERT_EQ("type_t", symbol_dependencies.get_symbol());
}


TEST(SymbolDependenciesTest, can_get_and_set_include_header_file)
{
   Blast::SymbolDependencies symbol_dependencies("std::string", "string");

   ASSERT_EQ("string", symbol_dependencies.get_include_header_file());
   symbol_dependencies.set_include_header_file("allegro5/allegro_bitmap.h");
   ASSERT_EQ("allegro5/allegro_bitmap.h", symbol_dependencies.get_include_header_file());
   symbol_dependencies.set_include_header_file("Blast/SymbolDependencies.hpp");
   ASSERT_EQ("Blast/SymbolDependencies.hpp", symbol_dependencies.get_include_header_file());
}


TEST(SymbolDependenciesTest, can_get_and_set_dependency_include_directory)
{
   Blast::SymbolDependencies symbol_dependencies("std::string", "string");

   symbol_dependencies.set_dependency_include_directory("./include");
   ASSERT_EQ("./include", symbol_dependencies.get_dependency_include_directory());
   symbol_dependencies.set_dependency_include_directory("~/Repos/allegro5/include");
   ASSERT_EQ("~/Repos/allegro5/include", symbol_dependencies.get_dependency_include_directory());
}


TEST(SymbolDependenciesTest, can_get_and_set_linked_library_name)
{
   Blast::SymbolDependencies symbol_dependencies("ALLEGRO_BITMAP", "allegro5/allegro.h");

   symbol_dependencies.set_linked_library_name("-lallegro_bitmap");
   ASSERT_EQ("-lallegro_bitmap", symbol_dependencies.get_linked_library_name());
   symbol_dependencies.set_linked_library_name("-lallegro_monolith");
   ASSERT_EQ("-lallegro_monolith", symbol_dependencies.get_linked_library_name());
}


TEST(SymbolDependenciesTest, get_include_directive__retuns_a_string_of_the_include_directive)
{
   Blast::SymbolDependencies symbol_dependencies("ALLEGRO_BITMAP", "allegro5/allegro.h");
   ASSERT_EQ("#include <allegro5/allegro.h>", symbol_dependencies.get_include_directive());
}


TEST(SymbolDependenciesTest, has_linked_library__returns_true_if_a_linked_library_is_present)
{
   Blast::SymbolDependencies symbol_dependencies("std::string", "string");
   ASSERT_FALSE(symbol_dependencies.has_linked_library());
}


TEST(SymbolDependenciesTest, has_linked_library__returns_false_if_a_linked_library_is_not_present)
{
   Blast::SymbolDependencies symbol_dependencies{ "al_get_font_line_height", "allegro5/allegro_font.h", "~/Repos/username/allegro5/include", "-lallegro_font" };
   ASSERT_TRUE(symbol_dependencies.has_linked_library());
}


