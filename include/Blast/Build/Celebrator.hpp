#pragma once


#include <string>


namespace Blast
{
   namespace Build
   {
      class Celebrator
      {
      private:

      public:
         Celebrator();
         ~Celebrator();


      std::string generate_output_banner(int width=80);
      };
   }
}



