

#include <Blast/DirectoryCreator.hpp>
#include <sys/stat.h>
#include <sstream>
#include <Blast/DirectoryExistenceChecker.hpp>


namespace Blast
{


DirectoryCreator::DirectoryCreator(std::string directory_name)
   : directory_name(directory_name)
{
}


DirectoryCreator::~DirectoryCreator()
{
}


bool DirectoryCreator::create()
{
if (Blast::DirectoryExistenceChecker(directory_name).exists()) return true;
int mkdir_result = mkdir(directory_name.c_str(), 0777);
return mkdir_result != -1;

}
} // namespace Blast


