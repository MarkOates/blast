#pragma once


#include <string>


namespace Blast
{
   namespace Project
   {
      class ComponentCreator
      {
      private:

      protected:


      public:
         ComponentCreator();
         ~ComponentCreator();

         std::string get_quintessence_file_default_content();
         std::string generate();
      };
   }
}



