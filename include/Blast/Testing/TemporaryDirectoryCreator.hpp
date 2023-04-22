#pragma once


#include <cstdint>
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

         std::filesystem::path create(uint32_t max_tries=100000);
      };
   }
}



