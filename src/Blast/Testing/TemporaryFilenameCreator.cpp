

#include <Blast/Testing/TemporaryFilenameCreator.hpp>

#include <Blast/Errors.hpp>
#include <Blast/Testing/TemporaryDirectoryCreator.hpp>
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
   // NOTE: this method was previously called "create"
   //return std::tmpnam(nullptr);
   char template_name[] = "tempfile_XXXXXX";
   int mkstemp_file_descriptor = mkstemp(template_name);

   if (mkstemp_file_descriptor == -1)
   {
       // Handle error, e.g., throw an exception or return an error code
      Blast::Errors::throw_error(
         "Blast::Testing::TemporaryFilenameCreator",
         "When attempting to make a temp file"
      );
   }

   // Close the file descriptor since we only needed it to create the file
   close(mkstemp_file_descriptor);

   return template_name;
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


