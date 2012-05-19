#pragma once
#include "DamageCalculator.hpp"

class MagicalDamageCalculator : public DamageCalculator
{
  public:
    virtual int calculate(CreaturePtr defending_creature, const Damage& damage, const int base_damage, const float soak_multiplier);
};
