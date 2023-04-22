

#include <Blast/Testing/TemporaryDirectoryCreator.hpp>

#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>


namespace Blast
{
namespace Testing
{


TemporaryDirectoryCreator::TemporaryDirectoryCreator()
{
}


TemporaryDirectoryCreator::~TemporaryDirectoryCreator()
{
}


std::filesystem::path TemporaryDirectoryCreator::create(uint32_t max_tries)
{
   auto tmp_dir = std::filesystem::temp_directory_path();
   unsigned long long num_attempts_made = 0;
   std::random_device dev;
   std::mt19937 prng(dev());
   std::uniform_int_distribution<uint64_t> rand(0);
   std::filesystem::path path;
   bool directory_created = false;

   while (true)
   {
       std::stringstream ss;
       ss << std::hex << rand(prng);
       path = tmp_dir / ss.str();

       directory_created = std::filesystem::create_directory(path);

       if (directory_created)
       {
           break;
       }
       if (num_attempts_made == max_tries)
       {
           throw std::runtime_error("Could not find non-existing directory");
       }
       num_attempts_made++;
   }
   return path;
}


} // namespace Testing
} // namespace Blast


