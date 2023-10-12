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

         std::string create();
      };
   }
}



