

#include <Blast/BuildSystem/ReportRenderer.hpp>

#include <Blast/BuildSystem/ReportRenderers/Base.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Blast
{
namespace BuildSystem
{


ReportRenderer::ReportRenderer(Blast::BuildSystem::Builds::Base* build)
   : build(build)
{
}


ReportRenderer::~ReportRenderer()
{
}


void ReportRenderer::set_build(Blast::BuildSystem::Builds::Base* build)
{
   this->build = build;
}


Blast::BuildSystem::Builds::Base* ReportRenderer::get_build() const
{
   return build;
}


std::string ReportRenderer::build_text_report()
{
   if (!(build))
   {
      std::stringstream error_message;
      error_message << "[ReportRenderer::build_text_report]: error: guard \"build\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ReportRenderer::build_text_report: error: guard \"build\" not met");
   }
   std::string result;

   if (build->is_type(Blast::BuildSystem::Builds::Base::TYPE))
   {
      Blast::BuildSystem::ReportRenderers::Base base_report_renderer;
      base_report_renderer.set_build(build);

      result = base_report_renderer.render_text();
   }
   else
   {
      std::stringstream error_message;
      error_message << "Blast::BuildSystem::ReportRenderer::build_report error: "
                    << "Cannot build_report() on a report that is of unknown type \"" << build->get_type() << "\".";
      throw std::runtime_error(error_message.str());
   }

   return result;
}


} // namespace BuildSystem
} // namespace Blast


