

#include <Blast/DirectoryCreator.hpp>
#include <filesystem>
#include <sstream>
#include <string>
#include <Blast/DirectoryExistenceChecker.hpp>


namespace Blast
{


DirectoryCreator::DirectoryCreator(std::vector<std::string> directory_components, bool path_is_absolute)
   : directory_components(directory_components)
   , path_is_absolute(path_is_absolute)
{
}


DirectoryCreator::~DirectoryCreator()
{
}


bool DirectoryCreator::create()
{
std::stringstream result_directories;
const std::string SEPARATOR = "/";
if (path_is_absolute) result_directories << "/";
for (auto &directory_component : directory_components)
{
  result_directories << directory_component << SEPARATOR;
  std::string directory_to_create = result_directories.str();

  if (Blast::DirectoryExistenceChecker(directory_to_create).exists()) continue;
  bool directory_created = std::__fs::filesystem::create_directories(directory_to_create.c_str());
  if (!directory_created)
  {
     std::stringstream error_message;
     error_message << "Could not create directory \"" << directory_to_create << "\"" << std::endl;
     throw std::runtime_error(error_message.str());
  }
}
return true;

}
} // namespace Blast


