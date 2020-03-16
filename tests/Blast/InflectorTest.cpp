
#include <gtest/gtest.h>

#include <Blast/Inflector.hpp>

TEST(Blast_InflectorTest, can_be_created_without_blowing_up)
{
   Blast::Inflector inflector;
}

TEST(Blast_InflectorTest, build_inflections_list__returns_the_expected_response)
{
   Blast::Inflector inflector;

   std::vector<std::pair<std::string, std::string>> some_expected_inflections = {
   };

   EXPECT_EQ(some_expected_inflections, inflector.build_inflections_list());
}

TEST(Blast_InflectorTest, pluralize__returns_the_plural_form_of_a_word)
{
   Blast::Inflector inflector("quiz");
   EXPECT_EQ("quizes", inflector.pluralize());
}
