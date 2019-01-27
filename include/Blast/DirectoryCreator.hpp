#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class DirectoryCreator
   {
   private:
      std::vector<std::string> directory_names;

   public:
      DirectoryCreator(std::vector<std::string> directory_names={});
      ~DirectoryCreator();


   bool create();
   };
}



