#pragma once
#include "DamageCalculator.hpp"

class PhysicalDamageCalculator : public DamageCalculator
{
  public:
    PhysicalDamageCalculator(const AttackType new_attack_type, const PhaseOfMoonType new_pom);
    
    virtual int calculate(CreaturePtr defending_creature, const bool slays_creatures_race, const Damage& damage, const int base_damage, const float soak_multiplier) override;
    virtual Damage calculate_base_damage_object(CreaturePtr attacking_creature) override;
    virtual Damage calculate_base_damage_with_bonuses_or_penalties(CreaturePtr attacking_creature) override;
    virtual int get_statistic_based_damage_modifier(CreaturePtr attacking_creature);
    
  protected:
    static const int DAMAGE_STAT_BASELINE;
    static const int DAMAGE_STAT_DIVISOR;
    static const float INCORPOREAL_SOAK_MULTIPLIER;
};
