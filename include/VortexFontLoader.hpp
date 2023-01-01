#pragma once


#include <map>
#include <string>
#include <vector>


class VortexFontLoader
{
private:

protected:


public:
   VortexFontLoader();
   ~VortexFontLoader();

   std::string sanitize_string(std::string unfiltered_phrase="");
   std::map<char, std::vector<std::string>> load();
};



