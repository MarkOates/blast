

#include <Blast/Testing/TemporaryFilenameCreator.hpp>

#include <Blast/Random.hpp>
#include <Blast/Testing/TemporaryDirectoryCreator.hpp>
#include <Blast/TimeStamper.hpp>
#include <cstdio>
#include <unistd.h>


namespace Blast
{
namespace Testing
{


TemporaryFilenameCreator::TemporaryFilenameCreator()
{
}


TemporaryFilenameCreator::~TemporaryFilenameCreator()
{
}


std::string TemporaryFilenameCreator::create_filename()
{
   static Blast::Random random(time(0)); // NOTE: Not sure how else to do this but with static
   return Blast::TimeStamper().generate_now_timestamp_utc() + "_" + random.get_random_string(26);
}

std::string TemporaryFilenameCreator::create_filename_within_guaranteed_unique_directory()
{
   Blast::Testing::TemporaryDirectoryCreator temporary_directory_creator;
   std::string unique_directory = temporary_directory_creator.create().string();
   std::string unique_filename = std::filesystem::path(create_filename()).filename().string();
   return unique_directory + "/" + unique_filename;
}


} // namespace Testing
} // namespace Blast


