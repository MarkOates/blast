

#include <Blast/Project/ProjectSymlinkFixer.hpp>



namespace Blast
{
namespace Project
{


ProjectSymlinkFixer::ProjectSymlinkFixer()
{
}


ProjectSymlinkFixer::~ProjectSymlinkFixer()
{
}


bool ProjectSymlinkFixer::starts_with(std::string source, std::string string_to_find)
{
return source.rfind(string_to_find, 0) == 0;

}

std::string ProjectSymlinkFixer::run()
{
return "Hello World!";
}
} // namespace Project
} // namespace Blast


