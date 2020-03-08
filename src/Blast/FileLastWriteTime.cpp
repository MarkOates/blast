

#include <Blast/FileLastWriteTime.hpp>
#include <filesystem>
#include <ctime>


namespace Blast
{


FileLastWriteTime::FileLastWriteTime(std::string filename)
   : filename(filename)
{
}


FileLastWriteTime::~FileLastWriteTime()
{
}


std::time_t FileLastWriteTime::last_write_time()
{
auto ftime = std::filesystem::last_write_time(filename);
#ifdef _WIN22
  return ftime; // will fail to compile
#else
  std::time_t last_write_time = decltype(ftime)::clock::to_time_t(ftime);
  return last_write_time;
#endif

}
} // namespace Blast


