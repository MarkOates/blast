

#include <Blast/Project/ComponentListerNew.hpp>



namespace Blast
{
namespace Project
{


ComponentListerNew::ComponentListerNew(std::string project_root_directory)
   : project_root_directory(project_root_directory)
{
}


ComponentListerNew::~ComponentListerNew()
{
}


std::string ComponentListerNew::run()
{
return "Hello World!";
}
} // namespace Project
} // namespace Blast


