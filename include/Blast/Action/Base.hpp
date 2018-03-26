#pragma once


#include <string>


namespace Blast
{
   namespace Action
   {
      class Base
      {
      private:
         std::string action_name;

      public:
         Base(std::string action_name);
         virtual ~Base();

         std::string get_action_name();

         virtual bool execute() = 0;
      };
   }
}


