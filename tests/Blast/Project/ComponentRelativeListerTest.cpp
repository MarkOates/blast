
#include <gtest/gtest.h>

#include <Blast/Project/ComponentRelativeLister.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

TEST(Blast_Project_ComponentRelativeListerTest, can_be_created_without_blowing_up)
{
   Blast::Project::ComponentRelativeLister component_relative_lister;
}

TEST(Blast_Project_ComponentRelativeListerTest,
   list_component_relatives__with_a_nullptr_component__throws_an_error)
{
   Blast::Project::ComponentRelativeLister component_relative_lister;
   std::string expected_error_message = "[Blast::Project::ComponentRelativeLister error] " \
                                        "cannot list_component_relative_names with a nullptr component";
   ASSERT_THROW_WITH_MESSAGE(component_relative_lister.list_component_relative_names(),
                             std::runtime_error,
                             expected_error_message);
}

TEST(Blast_Project_ComponentRelativeListerTest, list_component_relatives__returns_the_expected_response)
{
   Blast::Project::Component component("Some/Component");
   Blast::Project::ComponentRelativeLister component_relative_lister(&component);
   std::vector<std::string> expected_component_relative_names;
   std::vector<std::string> actual_component_relative_names =
      component_relative_lister.list_component_relative_names();
   ASSERT_EQ(expected_component_relative_names, actual_component_relative_names);
}
