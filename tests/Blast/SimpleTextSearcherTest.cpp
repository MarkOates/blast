
#include <gtest/gtest.h>

#include <Blast/SimpleTextSearcher.hpp>

TEST(Blast_SimpleTextSearcherTest, can_be_created_without_blowing_up)
{
   Blast::SimpleTextSearcher simple_text_searcher;
}

TEST(Blast_SimpleTextSearcherTest, results__returns_an_empty_result_set_when_the_search_text_is_empty)
{
   std::vector<std::string> elements = { "Foo", "Bar", "", " " };
   Blast::SimpleTextSearcher simple_text_searcher("", elements);

   std::vector<std::string> expected_results = std::vector<std::string>{};

   EXPECT_EQ(expected_results, simple_text_searcher.results());
}

TEST(Blast_SimpleTextSearcherTest, results__returns_elements_matching_the_search_text)
{
   std::vector<std::string> elements = { "Foo", "Bar", "", " ", "FooBar" };
   Blast::SimpleTextSearcher simple_text_searcher("Foo", elements);

   std::vector<std::string> expected_results = std::vector<std::string>{ "Foo", "FooBar" };

   EXPECT_EQ(expected_results, simple_text_searcher.results());
}
