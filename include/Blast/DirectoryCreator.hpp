#pragma once


#include <string>


namespace Blast
{
   class DirectoryCreator
   {
   private:
      std::string directory_name;

   public:
      DirectoryCreator(std::string directory_name="");
      ~DirectoryCreator();


   bool create();
   };
}



