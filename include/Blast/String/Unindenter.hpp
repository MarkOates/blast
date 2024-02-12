#pragma once


#include <cstddef>
#include <string>


namespace Blast
{
   namespace String
   {
      class Unindenter
      {
      private:
         std::string content;

      protected:


      public:
         Unindenter(std::string content="[unset-content]");
         ~Unindenter();

         std::string unindent(std::size_t num_unindents=2);
      };
   }
}



