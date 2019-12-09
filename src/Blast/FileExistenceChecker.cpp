

#include <Blast/FileExistenceChecker.hpp>
#include <experimental/filesystem>
#include <sys/stat.h>
#include <sys/stat.h>
#include <sys/stat.h>


namespace Blast
{


FileExistenceChecker::FileExistenceChecker(std::string filename)
   : filename(filename)
{
}


FileExistenceChecker::~FileExistenceChecker()
{
}


std::string FileExistenceChecker::get_filename()
{
   return filename;
}


bool FileExistenceChecker::exists()
{
struct stat info;
return stat(filename.c_str(), &info) == 0 && (S_ISREG(info.st_mode) || S_ISLNK(info.st_mode));

}
} // namespace Blast

