#include <gtest/gtest.h>


#include <Blast/SymbolDependencies.hpp>


TEST(SymbolDependenciesTest, can_be_created)
{
   Blast::SymbolDependencies symbol_dependencies("int");
}


TEST(SymbolDependenciesTest, when_created_without_arguments_sets_the_expected_values)
{
   Blast::SymbolDependencies symbol_dependencies("int");

   ASSERT_EQ(std::vector<std::string>{}, symbol_dependencies.get_dependency_include_directories());
   ASSERT_EQ(std::vector<std::string>{}, symbol_dependencies.get_linked_library_names());
   ASSERT_EQ(std::vector<std::string>{}, symbol_dependencies.get_include_header_files());
}


TEST(SymbolDependenciesTest, can_get_and_set_symbol)
{
   Blast::SymbolDependencies symbol_dependencies("std::string", { "string" });

   ASSERT_EQ("std::string", symbol_dependencies.get_symbol());
   symbol_dependencies.set_symbol("int");
   ASSERT_EQ("int", symbol_dependencies.get_symbol());
   symbol_dependencies.set_symbol("type_t");
   ASSERT_EQ("type_t", symbol_dependencies.get_symbol());
}


TEST(SymbolDependenciesTest, can_get_and_set_include_header_files)
{
   std::vector<std::string> values = { "string" };
   Blast::SymbolDependencies symbol_dependencies("std::string", values);

   ASSERT_EQ(values, symbol_dependencies.get_include_header_files());

   values = { "allegro5/allegro.h", "allegro5/allegro_bitmap.h" };
   symbol_dependencies.set_include_header_files(values);
   ASSERT_EQ(values, symbol_dependencies.get_include_header_files());

   values = { "vector", "string" };
   symbol_dependencies.set_include_header_files(values);
   ASSERT_EQ(values, symbol_dependencies.get_include_header_files());

   values = { "Blast/SymbolDependencies.hpp" };
   symbol_dependencies.set_include_header_files(values);
   ASSERT_EQ(values, symbol_dependencies.get_include_header_files());
}


TEST(SymbolDependenciesTest, can_get_and_set_dependency_include_directories)
{
   std::vector<std::string> directories = { "string" };
   Blast::SymbolDependencies symbol_dependencies("std::string", directories);

   directories = { "./include" };
   symbol_dependencies.set_dependency_include_directories(directories);
   ASSERT_EQ(directories, symbol_dependencies.get_dependency_include_directories());

   directories = { "~/Repos/allegro5/include" };
   symbol_dependencies.set_dependency_include_directories(directories);
   ASSERT_EQ(directories, symbol_dependencies.get_dependency_include_directories());
}


TEST(SymbolDependenciesTest, can_get_and_set_linked_library_names)
{
   std::vector<std::string> names = { "-lallegro_bitmap" };
   Blast::SymbolDependencies symbol_dependencies("ALLEGRO_BITMAP", names);

   names = { "-lallegro_bitmap" };
   symbol_dependencies.set_linked_library_names(names);
   ASSERT_EQ(names, symbol_dependencies.get_linked_library_names());

   names = { "-lallegro_monolith" };
   symbol_dependencies.set_linked_library_names(names);
   ASSERT_EQ(names, symbol_dependencies.get_linked_library_names());
}


TEST(SymbolDependenciesTest, is_symbol__retuns_true_if_a_string_matches_the_current_symbol)
{
   Blast::SymbolDependencies symbol_dependencies("ALLEGRO_BITMAP", { "allegro5/allegro.h" });
   ASSERT_TRUE(symbol_dependencies.is_symbol("ALLEGRO_BITMAP"));
}


TEST(SymbolDependenciesTest, is_symbol__retuns_false_if_a_string_matches_the_current_symbol)
{
   Blast::SymbolDependencies symbol_dependencies("ALLEGRO_BITMAP", { "allegro5/allegro.h" });
   ASSERT_FALSE(symbol_dependencies.is_symbol("std::string"));
}


TEST(SymbolDependenciesTest, get_include_directives__returns_a_list_of_formatted_include_directives_for_the_symbol)
{
   Blast::SymbolDependencies symbol_dependencies("ALLEGRO_FONT", { "allegro5/allegro.h", "allegro5/allegro_font.h" });

   std::vector<std::string> expected_directives = {
      "#include <allegro5/allegro.h>",
      "#include <allegro5/allegro_font.h>",
   };

   ASSERT_EQ(expected_directives, symbol_dependencies.get_include_directives());
}


TEST(SymbolDependenciesTest, requires_header_files__returns_true_if_the_dependency_requires_a_header_files)
{
   Blast::SymbolDependencies symbol_dependencies{
      "al_get_font_line_height",
      { "allegro5/allegro.h", "allegro5/allegro_font.h" },
      { "~/Repos/username/allegro5/include" },
      { "-lallegro_font" }
   };
   ASSERT_TRUE(symbol_dependencies.requires_header_files());
}


TEST(SymbolDependenciesTest, requires_header_files__returns_false_if_the_dependency_does_not_require_a_header_files)
{
   Blast::SymbolDependencies symbol_dependencies("int");
   ASSERT_FALSE(symbol_dependencies.requires_header_files());
}


TEST(SymbolDependenciesTest, requires_linked_libraries__returns_true_if_a_linked_library_is_required)
{
   Blast::SymbolDependencies symbol_dependencies("std::string", { "string" });
   ASSERT_FALSE(symbol_dependencies.requires_linked_libraries());
}


TEST(SymbolDependenciesTest, requires_linked_libraries__returns_false_if_a_linked_library_is_not_required)
{
   Blast::SymbolDependencies symbol_dependencies{
      "al_get_font_line_height",
      { "allegro5/allegro.h", "allegro5/allegro_font.h" },
      { "~/Repos/username/allegro5/include" },
      { "-lallegro_font" }
   };
   ASSERT_TRUE(symbol_dependencies.requires_linked_libraries());
}


