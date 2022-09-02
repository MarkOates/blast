#pragma once


#include <string>


namespace ncurses_art
{
   namespace Backends
   {
      class Base
      {
      public:
         static constexpr char* TYPE = "Backends/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=ncurses_art::Backends::Base::TYPE);
         ~Base();

         std::string get_type() const;
         bool is_type(std::string possible_type="");
      };
   }
}



