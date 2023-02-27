

#include <Blast/BuildSystem/BuildFactory.hpp>

#include <Blast/BuildSystem/BuildStageFactory.hpp>
#include <sstream>


namespace Blast
{
namespace BuildSystem
{


BuildFactory::BuildFactory()
   : build_stage_factory({})
{
}


BuildFactory::~BuildFactory()
{
}


Blast::BuildSystem::Builds::Base* BuildFactory::create_placeholder_build()
{
   Blast::BuildSystem::Builds::Base *build = new Blast::BuildSystem::Builds::Base;
   build->set_build_stages({
      build_stage_factory.create_shell_command_build_stage(),
      build_stage_factory.create_shell_command_build_stage("echo \"Having a good day?\""),
   });
   return build;
}

Blast::BuildSystem::Builds::Base* BuildFactory::create_shell_command_build(std::string shell_command)
{
   Blast::BuildSystem::Builds::Base *build = new Blast::BuildSystem::Builds::Base;
   build->set_build_stages({
      build_stage_factory.create_shell_command_build_stage(shell_command),
   });
   return build;
}


} // namespace BuildSystem
} // namespace Blast


