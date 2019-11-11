#pragma once


#include <string>
#include <fstream>
#include <streambuf>


namespace Blast
{
   class FileContentComparisonChecker
   {
   private:
      std::string filename;
      std::string file_content_for_comparison;

   public:
      FileContentComparisonChecker(std::string filename="", std::string file_content_for_comparison="");
      ~FileContentComparisonChecker();

      bool file_exists();
      bool is_equal();
   };
}


