#pragma once
#include <string>
#include "AttackTypes.hpp"
#include "Ammunition.hpp"
#include "IActionManager.hpp"
#include "Creature.hpp"
#include "Weapon.hpp"

class WeaponInfoAction : public IActionManager
{
  public:
    ActionCostValue weapon_info(CreaturePtr creature, const WeaponStyle attack_type) const;
    std::pair<std::string, std::string> get_wielded_and_offhand_text(CreaturePtr creature) const;
    std::string get_ranged_text(CreaturePtr creature) const;

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    friend class ActionManager;
    friend class AttackDumper;

    WeaponInfoAction();

    ActionCostValue melee_weapon_info(CreaturePtr creature) const;
    ActionCostValue ranged_weapon_info(CreaturePtr creature) const;

    std::string get_melee_weapon_info(CreaturePtr creature, WeaponPtr weapon, const AttackType attack_type, const Damage& damage) const;
    std::string get_ranged_weapon_info(CreaturePtr creature, WeaponPtr ranged_weapon, WeaponPtr ammunition) const;
};
