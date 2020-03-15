

#include <Blast/Project/SymlinkChecker.hpp>
#include <sstream>
#include <filesystem>
#include <filesystem>
#include <filesystem>
#include <filesystem>
#include <filesystem>


namespace Blast
{
namespace Project
{


SymlinkChecker::SymlinkChecker(std::string filename)
   : filename(filename)
{
}


SymlinkChecker::~SymlinkChecker()
{
}


bool SymlinkChecker::is_symlink()
{
std::filesystem::path path(filename);
if (!std::filesystem::exists(path))
{
   std::stringstream error_message;
   error_message << "an error occurred when trying to read_symlink_target in "
                 << "Blast/Project/SymlinkChecker: "
                 << "The file \"" << filename << "\" does not exist.";
   throw std::runtime_error(error_message.str());
}
return std::filesystem::is_symlink(path);

}

std::string SymlinkChecker::read_symlink_target()
{
if (!is_symlink())
{
   std::string error_message = "an error occurred when trying to read_symlink_target in Blast/Project/SymlinkChecker";
   throw std::runtime_error(error_message);
}
std::filesystem::path path(filename);
return std::filesystem::read_symlink(path).string();

}
} // namespace Project
} // namespace Blast


