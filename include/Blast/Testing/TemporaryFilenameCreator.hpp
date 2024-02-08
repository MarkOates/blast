#pragma once


#include <string>


namespace Blast
{
   namespace Testing
   {
      class TemporaryFilenameCreator
      {
      private:

      protected:


      public:
         TemporaryFilenameCreator();
         ~TemporaryFilenameCreator();

         std::string create_filename();
         std::string create_filename_within_guaranteed_unique_directory();
      };
   }
}



