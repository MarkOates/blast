

#include <Blast/Project/ActionCreator.hpp>



namespace Blast
{
namespace Project
{


ActionCreator::ActionCreator(Blast::Project::Component parent_component, std::string action_name_snake_case)
   : parent_component(parent_component)
   , action_name_snake_case(action_name_snake_case)
{
}


ActionCreator::~ActionCreator()
{
}


std::string ActionCreator::generate_action_name_camel_case()
{
   return "UnnamedAction";
}

std::string ActionCreator::generate_action_name_identifier_constant()
{
   return "UnnamedAction";
}
} // namespace Project
} // namespace Blast


