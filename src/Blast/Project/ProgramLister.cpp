

#include <Blast/Project/ProgramLister.hpp>



namespace Blast
{
namespace Project
{


ProgramLister::ProgramLister(std::string project_root)
   : project_root(project_root)
{
}


ProgramLister::~ProgramLister()
{
}


std::string ProgramLister::get_project_root()
{
   return project_root;
}


std::string ProgramLister::run()
{
return "Hello World!";
}
} // namespace Project
} // namespace Blast


