#pragma once


#include <string>


namespace Blast
{
   class TimeStamper
   {
   private:

   protected:


   public:
      TimeStamper();
      ~TimeStamper();

      std::string generate_now_timestamp_utc();
   };
}



