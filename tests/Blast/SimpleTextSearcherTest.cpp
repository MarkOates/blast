
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

TEST(Blast_SimpleTextSearcherTest,
   would_be_include_in_results__will_return_true_if_the_element_would_be_included_in_the_results_if_present)
{
   std::vector<std::string> elements = { "Foo", "Bar", "", " ", "FooBar" };
   Blast::SimpleTextSearcher simple_text_searcher("Foo", elements);

   EXPECT_EQ(true, simple_text_searcher.would_be_included_in_results("Foo"));
   EXPECT_EQ(true, simple_text_searcher.would_be_included_in_results("FooBar"));
   EXPECT_EQ(true, simple_text_searcher.would_be_included_in_results("FooBarFlex"));
}

TEST(Blast_SimpleTextSearcherTest,
   would_be_include_in_results__will_return_false_if_the_element_would_not_be_included_in_the_results_if_present)
{
   std::vector<std::string> elements = { "Foo", "Bar", "", " ", "FooBar" };
   Blast::SimpleTextSearcher simple_text_searcher("Foo", elements);

   EXPECT_EQ(false, simple_text_searcher.would_be_included_in_results("NonMatching"));
   EXPECT_EQ(false, simple_text_searcher.would_be_included_in_results("Bar"));
   EXPECT_EQ(false, simple_text_searcher.would_be_included_in_results(""));
   EXPECT_EQ(false, simple_text_searcher.would_be_included_in_results(" "));
}

