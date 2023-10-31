#pragma once


#include <Blast/Cpp/EnumClass.hpp>
#include <string>


namespace Blast
{
   namespace Cpp
   {
      class EnumClassFormatter
      {
      private:
         Blast::Cpp::EnumClass enum_class;

      protected:


      public:
         EnumClassFormatter(Blast::Cpp::EnumClass enum_class={});
         ~EnumClassFormatter();

         std::string build_enum_definition(int indent_num_spaces=3);
         static int convert_to_bit_set_position(int n=0);
         static std::string output_nth_bit_as_hex_string(int n=0);
      };
   }
}



