#include "MessageManager.hpp"
#include "RangedCombatActionManager.hpp"
#include "RangedCombatApplicabilityChecker.hpp"

using namespace std;

RangedCombatActionManager::RangedCombatActionManager()
{
}

ActionCostValue RangedCombatActionManager::fire_missile(CreaturePtr creature)
{
  MessageManager* manager = MessageManager::instance();
  
  if (creature && manager)
  {
    RangedCombatApplicabilityChecker rcec;
    
    pair<bool, string> ranged_combat_info = rcec.can_creature_do_ranged_combat(creature);
    
    if (ranged_combat_info.first)
    {
      // We can do ranged combat.  Select the tile, and then fire.
    }
    else
    {
      // We are unable to do ranged combat, for some sort of reason.  Display the message
      // that was generated regarding this.
      if (creature->get_is_player())
      {
        manager->add_new_message(ranged_combat_info.second);
        manager->send();
      }
    }
  }
  
  return get_action_cost_value();
}

ActionCostValue RangedCombatActionManager::get_action_cost_value() const
{
  return 1;
}
