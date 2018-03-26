#pragma once


#include <Blast/Action/Base.hpp>
#include <vector>


namespace Blast
{
   namespace Action
   {
      class Queue : public Base
      {
      private:
         std::vector<Action::Base *> actions;

      public:
         Queue(std::string name, std::vector<Action::Base *> actions = {});
         ~Queue();

         bool execute() override;

         std::vector<Action::Base *> get_actions();
         bool add_action(Action::Base *action);
         bool clear();
      };
   }
}


