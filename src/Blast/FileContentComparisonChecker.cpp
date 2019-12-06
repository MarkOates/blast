

#include <Blast/FileContentComparisonChecker.hpp>

#include <iostream>


namespace Blast
{
   FileContentComparisonChecker::FileContentComparisonChecker(std::string filename, std::string file_content_for_comparison)
      : filename(filename)
      , file_content_for_comparison(file_content_for_comparison)
   {
   }


   FileContentComparisonChecker::~FileContentComparisonChecker()
   {
   }


   bool FileContentComparisonChecker::file_exists()
   {
      return std::filesystem::exists(filename);
   }


   bool FileContentComparisonChecker::is_equal()
   {
      if (!file_exists()) return false;

      std::ifstream t(filename);
      std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());

      return str == file_content_for_comparison;
   }
}


