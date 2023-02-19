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

         std::string build_enum_definition();
      };
   }
}



