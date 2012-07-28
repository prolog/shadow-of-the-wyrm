#pragma once
#include <string>
#include "IActionManager.hpp"
#include "Creature.hpp"

class WeaponInfoManager
{
  public:
    ActionCostValue melee_weapon_info(CreaturePtr creature) const;
    ActionCostValue ranged_weapon_info(CreaturePtr creature) const;

  protected:
    friend class ActionManager;
    WeaponInfoManager();

    std::string get_melee_weapon_info(CreaturePtr creature) const;
    std::string get_ranged_weapon_info(CreaturePtr creature) const;
    ActionCostValue get_action_cost_value() const;
};
