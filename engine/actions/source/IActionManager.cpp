#include "IActionManager.hpp"

using std::string;

ActionCost IActionManager::get_total_action_cost(CreaturePtr creature)
{
  string creature_id;
  uint cost = 0;

  if (creature)
  {
    creature_id = creature->get_id();
    cost = creature->get_speed().get_current() + get_current_action_cost();
  }
  
  ActionCost action_cost(creature_id, cost);  
  return action_cost;
}
