

#include <Blast/BuildSystem/BuildStageFactory.hpp>




namespace Blast
{
namespace BuildSystem
{


BuildStageFactory::BuildStageFactory()
{
}


BuildStageFactory::~BuildStageFactory()
{
}


Blast::BuildSystem::BuildStages::ShellCommand* BuildStageFactory::create_shell_command_build_stage(std::string shell_command)
{
   //std::string shell_command = "echo \"Hi friend\"";
   Blast::BuildSystem::BuildStages::ShellCommand* build_stage =
      new Blast::BuildSystem::BuildStages::ShellCommand(shell_command);
   return build_stage;
}


} // namespace BuildSystem
} // namespace Blast


