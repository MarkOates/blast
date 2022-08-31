#pragma once


#include <string>
#include <utility>


namespace Blast
{
   namespace Project
   {
      class ComponentBasenameExtractor
      {
      private:
         std::string filename;

      protected:


      public:
         ComponentBasenameExtractor(std::string filename="");
         ~ComponentBasenameExtractor();

         std::string identify_file_type();
         std::string identify_component_basename();
         std::pair<std::string, std::string> extract_component();
      };
   }
}



