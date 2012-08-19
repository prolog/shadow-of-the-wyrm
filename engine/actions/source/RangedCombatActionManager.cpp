#include <boost/make_shared.hpp>
#include "Conversion.hpp"
#include "FireWeaponTileSelectionKeyboardCommandMap.hpp"
#include "MessageManager.hpp"
#include "RangedCombatActionManager.hpp"
#include "RangedCombatApplicabilityChecker.hpp"
#include "TileSelectionManager.hpp"

using namespace std;
using boost::make_shared;

RangedCombatActionManager::RangedCombatActionManager()
{
}

ActionCostValue RangedCombatActionManager::fire_missile(CreaturePtr creature)
{
  ActionCostValue action_cost_value = get_action_cost_value();
  MessageManager* manager = MessageManager::instance();
  
  if (creature && manager)
  {
    RangedCombatApplicabilityChecker rcec;
    
    pair<bool, string> ranged_combat_info = rcec.can_creature_do_ranged_combat(creature);
    
    if (ranged_combat_info.first)
    {
      // We can do ranged combat.  Select the tile, and then fire.
      TileSelectionManager tsm;
      KeyboardCommandMapPtr fire_weapon_keyboard_bindings = make_shared<FireWeaponTileSelectionKeyboardCommandMap>();
      tsm.set_keyboard_command_map(fire_weapon_keyboard_bindings);
      tsm.set_show_tile_description(false);
      tsm.set_show_feature_description(false);
      tsm.set_show_item_descriptions(false);
      // Show only the creature.
      
      tsm.set_selection_key(Integer::to_string(ATTACK_TYPE_RANGED));
      
      action_cost_value = tsm.select_tile(creature, ActionTextKeys::ACTION_FIRE);
      
      // If the action advances a turn, we've selected a tile:
      if (action_cost_value)
      {
        // Do ranged combat!
        // Pew pew pew.
        int x = 1;
      }
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
  
  return action_cost_value;
}

ActionCostValue RangedCombatActionManager::get_action_cost_value() const
{
  return 1;
}
