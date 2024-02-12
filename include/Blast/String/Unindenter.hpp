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

         std::string remove_spaces_at_beginning(std::size_t num_unindents=3);
      };
   }
}



