#pragma once


#include <set>
#include <string>


namespace Blast
{
   namespace Cpp
   {
      class EnumClass
      {
      private:
         std::string enum_name;
         std::set<std::string> elements;

      protected:


      public:
         EnumClass(std::string enum_name="[unset-enum_name]", std::set<std::string> elements={});
         ~EnumClass();

         void set_enum_name(std::string enum_name);
         void set_elements(std::set<std::string> elements);
         std::string get_enum_name() const;
         std::set<std::string> get_elements() const;
      };
   }
}



