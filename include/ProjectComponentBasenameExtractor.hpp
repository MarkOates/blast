#pragma once


#include <string>
#include <utility>


class ProjectComponentBasenameExtractor
{
private:
   std::string filename;

protected:


public:
   ProjectComponentBasenameExtractor(std::string filename="");
   ~ProjectComponentBasenameExtractor();

   std::string identify_file_type();
   std::string identify_component_basename();
   std::pair<std::string, std::string> extract_component();
};



