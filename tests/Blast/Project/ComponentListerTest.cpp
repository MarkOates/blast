
#include <gtest/gtest.h>

#include <Blast/Project/ComponentLister.hpp>

TEST(Blast__Project__ComponentLister, can_be_created_without_arguments)
{
   Blast::Project::ComponentLister lister;
}

TEST(Blast__Project__ComponentLister, will_return_the_components_in_a_project)
{
   std::vector<std::string> expected_components = {
      "ASCIICharacterRenderer",
      "Checkbox",
      "EpicDarkFont",
      "GithubRepoStatusFetcher",
      "HostnameExtractor",
      "OrigamiMommyFontLoader",
      "ProjectComponentBasenameExtractor",
      "ProjectFilenameGenerator",
      "ProjectListBuilder",
      "Question",
      "Quiz",
      "QuizYAMLLoader",
      "ShellCommandExecutorWithCallback",
      "SmallFontLoader",
      "StringSplitter",
      "StringTrimmer",
      "StringVectorIntersection",
   };

  std::string project_folder_name = "ncurses-art";
  std::string full_folder_name = std::string("/Users/markoates/Repos/") + project_folder_name;
  Blast::Project::ComponentLister lister(full_folder_name);
  std::vector<std::string> actual_components = lister.components();

  ASSERT_EQ(expected_components, actual_components);
}


