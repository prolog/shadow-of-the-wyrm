#pragma once
#include <memory>
#include "ActionCost.hpp"
#include "Creature.hpp"
#include "Weapon.hpp"

class AttackSpeedCalculator
{
  public:
    virtual ActionCostValue calculate(CreaturePtr creature) = 0;

  protected:
    virtual ActionCostValue calculate_speed_for_weapon(CreaturePtr creature, WeaponPtr weapon, const bool ranged = false);
    virtual int calculate_exotic_attack_speed_multiplier(CreaturePtr creature, const SkillType skill_type);
};

using AttackSpeedCalculatorPtr = std::shared_ptr<AttackSpeedCalculator>;

