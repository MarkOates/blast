

#include <Blast/Action/Queue.hpp>

#include <sstream>


namespace Blast
{
namespace Action
{


Queue::Queue(std::string name, std::vector<Base *> actions)
   : Base(std::string("Queue<" + name + ">"))
   , actions(actions)
{
}


Queue::~Queue()
{
   clear();
}


bool Queue::execute()
{
   bool status = true;
   for (auto &action : actions)
   {
      bool action_execution_status = false;
      try
      {
         action_execution_status = action->execute();
      }
      catch (const std::exception &err)
      {
         std::stringstream error_message;
         error_message << get_action_name() << " error: The queued action \"" << action->get_action_name() << "\" raised the following exception: ";
         error_message << "\"" << err.what() << "\"";
         throw std::runtime_error(error_message.str());
      }

      if (!action_execution_status)
      {
         std::stringstream error_message;
         error_message << get_action_name() << " error: The queued action \"" << action->get_action_name() << "\" returned false when executed.";
         throw std::runtime_error(error_message.str());
      }
   }
   return status;
}


std::vector<Action::Base *> Queue::get_actions()
{
   return actions;
}


bool Queue::add_action(Base *action)
{
   actions.push_back(action);
   return true;
}


bool Queue::clear()
{
   for (auto &action : actions) delete action;
   actions.clear();
   return true;
}


} // namespace Action
} // namespace Blast


