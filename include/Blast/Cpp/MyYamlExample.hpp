#pragma once


#include <string>


namespace Blast
{
   namespace Cpp
   {
      class MyYamlExample
      {
      private:
         std::string person_name;

      public:
         MyYamlExample(std::string person_name="foo-default-value");
         ~MyYamlExample();

         void set_person_name(std::string person_name);

         std::string get_person_name();
      std::string my_function(std::string person_name="Jhonny McNoName");
      };
   }
}



