

#include <Blast/Project/ComponentCreator.hpp>



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
   std::string const QUINTESSENCE_FILE_CONTENT = R"END(functions:
     - name: run
       type: std::string
       body: return "Hello World!";
   )END";
   return QUINTESSENCE_FILE_CONTENT;
}

std::string ComponentCreator::generate()
{
   return "Hello World!";
}
} // namespace Project
} // namespace Blast


