

#include <Blast/Project/ComponentCreator.hpp>

#include <sstream>


namespace Blast
{
namespace Project
{


ComponentCreator::ComponentCreator()
{
}


ComponentCreator::~ComponentCreator()
{
}


std::string ComponentCreator::get_quintessence_file_default_content()
{
   std::stringstream QUINTESSENCE_FILE_CONTENT;
   QUINTESSENCE_FILE_CONTENT
      << "functions:" << std::endl
      << "  - name: run" << std::endl
      << "    type: std::string" << std::endl
      << "    body: return \"Hello World!\";" << std::endl;
   return QUINTESSENCE_FILE_CONTENT.str();
}

std::string ComponentCreator::generate()
{
   return "Hello World!";
}


} // namespace Project
} // namespace Blast


