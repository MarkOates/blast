

#include <Blast/Action/Base.hpp>


namespace Blast
{
namespace Action
{


Base::Base(std::string action_name)
  : action_name(action_name)
{}


Base::~Base() {}


std::string Base::get_action_name()
{
   return action_name;
}


} // namespace Action
} // namespace Blast


