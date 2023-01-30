
#include <gtest/gtest.h>

#include <Blast/DependencyHeadersSuggester.hpp>


TEST(Blast_DependencyHeadersSuggesterTest, can_be_created_without_blowing_up)
{
   Blast::DependencyHeadersSuggester dependency_headers_suggester;
}


TEST(Blast_DependencyHeadersSuggesterTest,
   find_suggested_headers_csv__returns_an_expected_suggested_headers)
{
   Blast::DependencyHeadersSuggester dependency_headers_suggester;
   std::string expected_headers = "algorithm";
   EXPECT_EQ(expected_headers, dependency_headers_suggester.find_suggested_headers_csv("std::max"));
}


