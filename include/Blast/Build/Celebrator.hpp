#pragma once


#include <string>


namespace Blast
{
   namespace Build
   {
      class Celebrator
      {
      private:

      protected:


      public:
         Celebrator();
         ~Celebrator();

         std::string generate_full_width_output_banner(std::string message="", int width=80);
         std::string generate_pass_banner(int width=80);
      };
   }
}



