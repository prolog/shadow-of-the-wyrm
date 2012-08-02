#pragma once
#include "DamageCalculator.hpp"

class MagicalDamageCalculator : public DamageCalculator
{
  public:
    MagicalDamageCalculator();
    
    virtual int calculate(CreaturePtr defending_creature, const Damage& damage, const int base_damage, const float soak_multiplier);
    virtual Damage calculate_base_damage_object(CreaturePtr creature);
    virtual Damage calculate_base_damage_with_bonuses_or_penalties(CreaturePtr creature);
};
