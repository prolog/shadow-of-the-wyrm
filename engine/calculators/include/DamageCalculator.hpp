#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "CalendarTypes.hpp"

class DamageCalculator
{
  public:
    DamageCalculator(const AttackType new_attack_type, const PhaseOfMoonType pom);
    virtual ~DamageCalculator();
  
    virtual int calculate(CreaturePtr defending_creature, const bool slays_creatures_race, const Damage& damage, const int base_damage, const float soak_multiplier) = 0;
    virtual Damage calculate_base_damage_object(CreaturePtr attacking_creature) = 0;
    virtual Damage calculate_base_damage_with_bonuses_or_penalties(CreaturePtr attacking_creature) = 0;
    
  protected:
    double get_phase_of_moon_multiplier(const DamageType dt, const PhaseOfMoonType pom) const;

    AttackType attack_type;
    PhaseOfMoonType pom_type;
};

using DamageCalculatorPtr = std::shared_ptr<DamageCalculator>;
