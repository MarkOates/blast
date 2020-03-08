

#include <Blast/Project/SymlinkChecker.hpp>
#include <filesystem>
#include <filesystem>
#include <filesystem>
#include <unistd.h>
#include <string>


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
return std::filesystem::exists(path) && std::filesystem::is_symlink(path);

}

std::string SymlinkChecker::read_symlink_target()
{
char buff[512];
ssize_t len = ::readlink(filename.c_str(), buff, sizeof(buff)-1);
if (len != -1) {
   buff[len] = '\0';
   return std::string(buff);
}
throw std::runtime_error("an error occurred when trying to read_symlink_target in Blast/Project/SymlinkChecker");

}
} // namespace Project
} // namespace Blast


