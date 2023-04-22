

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
   std::filesystem::path tmp_directory_base_path = std::filesystem::temp_directory_path();
   unsigned long long num_attempts_made = 0;
   std::random_device random_device;
   std::mt19937 random_number_engine(random_device());
   std::uniform_int_distribution<uint64_t> random_number_generator(0);
   std::filesystem::path path;
   bool directory_created = false;

   while (true)
   {
       std::stringstream ss;
       ss << std::hex << random_number_generator(random_number_engine);
       path = tmp_directory_base_path / ss.str();

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


