

#include <Blast/Project/SymlinkChecker.hpp>
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


