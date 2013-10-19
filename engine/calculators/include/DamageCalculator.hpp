#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"

class DamageCalculator
{
  public:
    DamageCalculator(const AttackType new_attack_type);
    virtual ~DamageCalculator();
  
    virtual int calculate(CreaturePtr defending_creature, const bool slays_creatures_race, const Damage& damage, const int base_damage, const float soak_multiplier) = 0;
    virtual Damage calculate_base_damage_object(CreaturePtr attacking_creature) = 0;
    virtual Damage calculate_base_damage_with_bonuses_or_penalties(CreaturePtr attacking_creature) = 0;
    
  protected:
    AttackType attack_type;
};

typedef boost::shared_ptr<DamageCalculator> DamageCalculatorPtr;
