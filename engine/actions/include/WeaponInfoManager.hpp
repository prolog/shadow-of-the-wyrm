#pragma once
#include <string>
#include "Ammunition.hpp"
#include "IActionManager.hpp"
#include "Creature.hpp"
#include "Weapon.hpp"

class WeaponInfoManager
{
  public:
    ActionCostValue melee_weapon_info(CreaturePtr creature) const;
    ActionCostValue ranged_weapon_info(CreaturePtr creature) const;

  protected:
    friend class ActionManager;
    WeaponInfoManager();

    std::string get_melee_weapon_info(CreaturePtr creature, WeaponPtr weapon, const AttackType attack_type, const Damage& damage) const;
    std::string get_ranged_weapon_info(CreaturePtr creature, WeaponPtr ranged_weapon, WeaponPtr ammunition) const;
    ActionCostValue get_action_cost_value() const;
};
