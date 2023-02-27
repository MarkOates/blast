

#include <Blast/BuildSystem/BuildStageRenderer.hpp>

#include <Blast/BuildSystem/BuildStageRenderers/Base.hpp>
#include <Blast/BuildSystem/BuildStageRenderers/ShellCommand.hpp>
#include <Blast/Errors.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Blast
{
namespace BuildSystem
{


BuildStageRenderer::BuildStageRenderer(Blast::BuildSystem::BuildStages::Base* build_stage)
   : build_stage(build_stage)
{
}


BuildStageRenderer::~BuildStageRenderer()
{
}


void BuildStageRenderer::set_build_stage(Blast::BuildSystem::BuildStages::Base* build_stage)
{
   this->build_stage = build_stage;
}


Blast::BuildSystem::BuildStages::Base* BuildStageRenderer::get_build_stage() const
{
   return build_stage;
}


std::string BuildStageRenderer::build_text_report()
{
   if (!(build_stage))
   {
      std::stringstream error_message;
      error_message << "[BuildStageRenderer::build_text_report]: error: guard \"build_stage\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("BuildStageRenderer::build_text_report: error: guard \"build_stage\" not met");
   }
   std::string result;

   if (build_stage->is_type(Blast::BuildSystem::BuildStages::Base::TYPE))
   {
     // do nothing for this case
   }
   else if (build_stage->is_type(Blast::BuildSystem::BuildStages::ShellCommand::TYPE))
   {
      Blast::BuildSystem::BuildStages::ShellCommand* typed_build_stage =
         dynamic_cast<Blast::BuildSystem::BuildStages::ShellCommand*>(build_stage);

      Blast::BuildSystem::BuildStageRenderers::ShellCommand renderer;
      renderer.set_shell_command_build_stage(typed_build_stage);

      result = renderer.render_text();
   }
   else
   {
      std::stringstream error_message;
      error_message << "Cannot build report that is of unknown type \"" << build_stage->get_type() << "\".";
      std::cout << Blast::Errors::build_error_message(
         "Blast::BuildSystem::BuildStageRenderer::build_text_report()",
         error_message.str()
      );
      //throw std::runtime_error(error_message.str());
   }

   return result;
}


} // namespace BuildSystem
} // namespace Blast


