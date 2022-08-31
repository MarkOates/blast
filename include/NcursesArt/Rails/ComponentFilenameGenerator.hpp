#pragma once


#include <string>


namespace NcursesArt
{
   namespace Rails
   {
      class ComponentFilenameGenerator
      {
      private:
         std::string component_basename;

      protected:


      public:
         ComponentFilenameGenerator(std::string component_basename="unnamed/component");
         ~ComponentFilenameGenerator();

         std::string get_component_basename() const;
         std::string get_model_filename();
      };
   }
}



