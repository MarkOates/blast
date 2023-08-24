
#include <gtest/gtest.h>

#include <Blast/Project/ComponentDependencyLister.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

static std::string TEST_PROJECT_ROOT_DIRECTORY = "tests/fixtures/test_project/";

TEST(Blast_Project_ComponentDependencyListerTest, can_be_created_without_blowing_up)
{
   Blast::Project::ComponentDependencyLister component_dependency_lister;
}

TEST(Blast_Project_ComponentDependencyListerTest,
   DISABLED__list_component_dependency__with_a_nullptr_component__throws_an_error)
{
   Blast::Project::ComponentDependencyLister component_dependency_lister;
   std::string expected_error_message = "[Blast::Project::ComponentDependencyLister error] " \
                                        "cannot list_component_dependency_names with a nullptr component";
   ASSERT_THROW_WITH_MESSAGE(component_dependency_lister.list_component_dependency_names(),
                             std::runtime_error,
                             expected_error_message);
}

TEST(Blast_Project_ComponentDependencyListerTest,
   list_component_dependency_names__with_a_component_that_does_not_exist__throws_an_error)
{
   Blast::Project::Component component("Component/That/Does/Not/Exist", TEST_PROJECT_ROOT_DIRECTORY);
   Blast::Project::ComponentDependencyLister component_dependency_lister(&component);
   std::string expected_error_message = "[Blast::Project::ComponentDependencyLister error] " \
                                        "cannot list_component_dependency_names; The component " \
                                        "\"Component/That/Does/Not/Exist\" does not exist";
   ASSERT_THROW_WITH_MESSAGE(component_dependency_lister.list_component_dependency_names(),
                             std::runtime_error,
                             expected_error_message);
}

// TODO: more test coverage for edge cases: cout on missing quintessence, warning message as list item

TEST(Blast_Project_ComponentDependencyListerTest, DISABLED__list_component_dependency__returns_the_expected_response)
{
   Blast::Project::Component component("Nested/ComponentC", TEST_PROJECT_ROOT_DIRECTORY);
   Blast::Project::ComponentDependencyLister component_dependency_lister(&component);
   std::vector<std::string> expected_component_dependency_names = {
         "Nested/ComponentC",
         "Nested/ComponentC2",
         "Nested/ComponentC3",
         "Nested/ComponentC4",
      };
   std::vector<std::string> actual_component_dependency_names =
      component_dependency_lister.list_component_dependency_names();
   ASSERT_EQ(expected_component_dependency_names, actual_component_dependency_names);
}


