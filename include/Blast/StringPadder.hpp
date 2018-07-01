#pragma once


#include <string>


namespace Blast
{
   class StringPadder
   {
   private:
      std::string string;
      int padding;
      char character;

   public:
      StringPadder(std::string string="", int padding=0, char character=' ');
      ~StringPadder();

      std::string pad();
   };
} // namespace Blast


