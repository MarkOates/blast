#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class ComponentBasenameExtractor
      {
      private:
         std::string filename;

      public:
         ComponentBasenameExtractor(std::string filename="");
         ~ComponentBasenameExtractor();

         std::string identify_file_type();
         std::string identify_component_basename();
         std::pair<std::string, std::string> extract_component();
      };
   }
}



