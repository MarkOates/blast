#pragma once


#include <filesystem>


namespace Blast
{
   namespace Testing
   {
      class TemporaryDirectoryCreator
      {
      private:

      protected:


      public:
         TemporaryDirectoryCreator();
         ~TemporaryDirectoryCreator();

         std::filesystem::path create(int max_tries=100000);
      };
   }
}



