#pragma once
#include "ISpeedCalculator.hpp"

// This is an abstract class.  It is the parent class for the speed
// calculators for primary and secondary melee attacks, and simply
// defines a common function that can be used to get the attack speed
// for unarmed combat.
class IPhysicalAttackSpeedCalculator : public ISpeedCalculator
{
  public:
    ActionCostValue calculate(CreaturePtr creature);
    ActionCostValue calculate_unarmed_attack_speed(CreaturePtr creature);
    virtual ActionCostValue calculate_weapon_speed(CreaturePtr creature) = 0;

  protected:
    virtual bool has_weapon_equipped(CreaturePtr creature) = 0;
};
