

#include <Blast/DirectoryCreator.hpp>
#include <sys/stat.h>
#include <sstream>
#include <string>
#include <Blast/DirectoryExistenceChecker.hpp>


namespace Blast
{


DirectoryCreator::DirectoryCreator(std::vector<std::string> directory_names)
   : directory_names(directory_names)
{
}


DirectoryCreator::~DirectoryCreator()
{
}


bool DirectoryCreator::create()
{
std::stringstream result_directories;
const std::string SEPARATOR = "/";
for (auto &directory_name : directory_names)
{
  result_directories << directory_name << SEPARATOR;
  std::string directory_to_create = result_directories.str();

  if (Blast::DirectoryExistenceChecker(directory_to_create).exists()) continue;
  int mkdir_result = mkdir(directory_to_create.c_str(), 0777);
  if (mkdir_result == -1) return false;
}
return true;

}
} // namespace Blast


