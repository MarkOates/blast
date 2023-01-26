#pragma once


#include <ncurses_art/Backends/Base.hpp>
#include <string>


namespace ncurses_art
{
   namespace Backends
   {
      class Ncurses : public ncurses_art::Backends::Base
      {
      public:
         static constexpr char* TYPE = (char*)"Backends/Ncurses";

      private:
         std::string property;

      protected:


      public:
         Ncurses(std::string property="[unset-property]");
         ~Ncurses();

         std::string get_property() const;
         bool property_is(std::string possible_type="");
      };
   }
}



