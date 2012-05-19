#pragma once
#include "Creature.hpp"

class DamageCalculator
{
  public:
    virtual int calculate(CreaturePtr defending_creature, const Damage& damage, const int base_damage, const float soak_multiplier) = 0;
};

typedef boost::shared_ptr<DamageCalculator> DamageCalculatorPtr;
