#pragma once


#include <string>


namespace Blast
{
   class RailsInflector
   {
      public:
         enum inflection_operation_t
         {
            PLURALIZE,
            SINGULARIZE
         };

      private:
         std::string term;
         inflection_operation_t inflection_operation;

      public:
         RailsInflector(std::string term, inflection_operation_t inflection_operation);
         ~RailsInflector();

         std::string inflect();
   };
}


