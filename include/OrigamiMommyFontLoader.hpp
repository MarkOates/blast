#pragma once


#include <map>
#include <string>
#include <vector>


class OrigamiMommyFontLoader
{
private:

protected:


public:
   OrigamiMommyFontLoader();
   ~OrigamiMommyFontLoader();

   std::map<char, std::vector<std::string>> load();
};



