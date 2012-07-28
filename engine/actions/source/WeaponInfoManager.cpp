#include "WeaponInfoManager.hpp"

using std::string;

WeaponInfoManager::WeaponInfoManager()
{
}

// Get the actual melee weapon info.  Output it to the message manager if the
// creature is the player.
ActionCostValue WeaponInfoManager::melee_weapon_info(CreaturePtr creature) const
{
  if (creature)
  {
  }

  return get_action_cost_value();
}

ActionCostValue WeaponInfoManager::ranged_weapon_info(CreaturePtr creature) const
{
  if (creature)
  {
    
  }
  
  return get_action_cost_value();
}

string WeaponInfoManager::get_melee_weapon_info(CreaturePtr creature) const
{
  return "";
}

string WeaponInfoManager::get_ranged_weapon_info(CreaturePtr creature) const
{
  return "";
}

// Getting weapon info is always no-cost
ActionCostValue WeaponInfoManager::get_action_cost_value() const
{
  return 0;
}
