

#include <Blast/Project/Win64ReleaseBuilder.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>


namespace Blast
{
namespace Project
{


Win64ReleaseBuilder::Win64ReleaseBuilder(std::string projects_folder)
   : projects_folder(projects_folder)
   , win64_release_builder_shell_script_filename("blast/scripts/build_win64_release.sh")
{
}


Win64ReleaseBuilder::~Win64ReleaseBuilder()
{
}


std::string Win64ReleaseBuilder::build_full_path_to_win64_release_builder_script()
{
   return projects_folder + win64_release_builder_shell_script_filename;
}

void Win64ReleaseBuilder::run()
{
   std::string script_path = build_full_path_to_win64_release_builder_script();
   Blast::ShellCommandExecutorWithCallback executor(script_path);
}


} // namespace Project
} // namespace Blast


