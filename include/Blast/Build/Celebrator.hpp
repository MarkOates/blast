#pragma once


#include <cstddef>
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

         std::string generate_full_width_output_banner(std::string message="", int width=80, char fill_char='=', std::size_t num_leading_fill_characters=4);
         std::string generate_debug_banner(int width=80);
         std::string generate_pass_banner(int width=80);
         std::string generate_fail_banner(int width=80);
         std::string build_patterned_line(int length=127);
         std::string generate_component_built_banner(int width=80);
         std::string generate_built_banner(int width=80);
      };
   }
}



