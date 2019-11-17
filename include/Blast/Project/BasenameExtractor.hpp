#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class BasenameExtractor
      {
      private:
         std::string filename;

      public:
         BasenameExtractor(std::string filename="");
         ~BasenameExtractor();


      std::string identify_file_type();
      std::string identify_component_basename();
      std::pair<std::string, std::string> extract_component();
      };
   }
}



