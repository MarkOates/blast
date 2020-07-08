#pragma once


#include <Blast/Project/Component.hpp>
#include <string>


namespace Blast
{
   namespace Project
   {
      class ActionCreator
      {
      private:
         Blast::Project::Component parent_component;
         std::string action_name_snake_case;

      public:
         ActionCreator(Blast::Project::Component parent_component={}, std::string action_name_snake_case="unnamed_action");
         ~ActionCreator();


      std::string generate_action_name_camel_case();
      std::string generate_action_name_identifier_constant();
      };
   }
}



