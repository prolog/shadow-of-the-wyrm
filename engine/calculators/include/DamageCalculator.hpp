#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "CalendarTypes.hpp"

class DamageCalculator
{
  public:
    DamageCalculator(const AttackType new_attack_type, const PhaseOfMoonType pom);
    virtual ~DamageCalculator();
  
    virtual int calculate(CreaturePtr defending_creature, const bool sneak_attack, const bool slays_creatures_race, const Damage& damage, const int base_damage, const float soak_multiplier) = 0;
    virtual Damage calculate_base_damage_object(CreaturePtr attacking_creature) = 0;
    virtual Damage calculate_base_damage_with_bonuses_or_penalties(CreaturePtr attacking_creature) = 0;

    int get_item_status_effect_bonus(const ItemStatus status);

  protected:

    double get_phase_of_moon_multiplier(const DamageType dt, const PhaseOfMoonType pom) const;
    double get_sneak_attack_multiplier(const bool attacker_hidden) const;

    AttackType attack_type;
    PhaseOfMoonType pom_type;
};

using DamageCalculatorPtr = std::unique_ptr<DamageCalculator>;
