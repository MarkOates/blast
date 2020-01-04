

#include <Blast/Project/SymlinkChecker.hpp>
#include <sys/stat.h>
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
struct stat p_statbuf;

if (lstat(filename.c_str(), &p_statbuf) < 0)
{
   throw std::runtime_error("[Project/SymlinkChecker error:] An error occurred while attempting to is_symlink");
}

return (S_ISLNK(p_statbuf.st_mode) == 1);

}

std::string SymlinkChecker::read_symlink_target()
{
char linkname[256];
// from https://linux.die.net/man/2/readlink
//ssize_t readlink(const char *path, char *buf, size_t bufsiz);
ssize_t r;
r = readlink(filename.c_str(), linkname, 256);
return linkname;

}
} // namespace Project
} // namespace Blast


