#pragma once
#include "DamageCalculator.hpp"

class PhysicalDamageCalculator : public DamageCalculator
{
  public:
    PhysicalDamageCalculator(const AttackType new_attack_type);
    
    virtual int calculate(CreaturePtr defending_creature, const Damage& damage, const int base_damage, const float soak_multiplier);
    virtual Damage calculate_base_damage_object(CreaturePtr attacking_creature);
};
