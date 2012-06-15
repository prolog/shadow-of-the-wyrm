#include "IActionManager.hpp"

using std::string;

ActionCost IActionManager::get_total_action_cost(CreaturePtr creature)
{
  string creature_id;
  uint cost = 0;

  if (creature)
  {
    creature_id = creature->get_id();
    
    uint current_action_cost = get_current_action_cost();
    
    if (current_action_cost > 0)
    {
      cost = creature->get_speed().get_current() + current_action_cost;
    }
  }
  
  ActionCost action_cost(creature_id, cost);  
  return action_cost;
}
