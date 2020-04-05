#include <gtest/gtest.h>


#include <Blast/RailsInflector.hpp>


TEST(RailsInflectorTest, can_be_created)
{
   Blast::RailsInflector rails_inflector("ducks", Blast::RailsInflector::SINGULARIZE);
}


// DISABLED because test is too slow
TEST(DISABLED_RailsInflectorTest, returns_the_expected_rails_inflected_singularized_form_of_a_word)
{
   std::vector<std::pair<std::string, std::string>> test_data_sets = {
      { "trees", "tree" },
      { "my favorite ducks", "my favorite duck" },
      { "geese", "geese" },
      { "data", "datum" },
   };

   for (auto &test_data_set : test_data_sets)
   {
      Blast::RailsInflector rails_inflector(std::get<0>(test_data_set), Blast::RailsInflector::SINGULARIZE);
      ASSERT_EQ(std::get<1>(test_data_set), rails_inflector.inflect());
   }
}


// DISABLED because test is too slow
TEST(DISABLED_RailsInflectorTest, returns_the_expected_rails_inflected_pluralized_form_of_a_word)
{
   std::vector<std::pair<std::string, std::string>> test_data_sets = {
      { "tree", "trees" },
      { "my favorite duck", "my favorite ducks" },
      { "geese", "geeses" },
      { "datum", "data" },
   };

   for (auto &test_data_set : test_data_sets)
   {
      Blast::RailsInflector rails_inflector(std::get<0>(test_data_set), Blast::RailsInflector::PLURALIZE);
      ASSERT_EQ(std::get<1>(test_data_set), rails_inflector.inflect());
   }
}


TEST(RailsInflectorTest, when_initialized_with_an_empty_term_raises_an_exception)
{
   ASSERT_THROW(Blast::RailsInflector("", Blast::RailsInflector::PLURALIZE), std::runtime_error);
}


// DISABLED because test is too slow
TEST(DISABLED_RailsInflectorTest, when_initialized_with_a_term_containing_unescaped_characters_is_sanitized)
{
   Blast::RailsInflector rails_inflector("\\\"duck", Blast::RailsInflector::PLURALIZE);
   ASSERT_EQ("\\\"ducks", rails_inflector.inflect());
}


