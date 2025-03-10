#pragma once
#include <memory>
#include "AttackTypes.hpp"
#include "Creature.hpp"

class CombatTargetNumberCalculator
{
  public:
    CombatTargetNumberCalculator(const AttackType new_attack_type) : attack_type(new_attack_type) {};
    virtual ~CombatTargetNumberCalculator() = default;

    virtual int calculate(CreaturePtr attacking_creature, CreaturePtr attacked_creature) = 0;

    virtual int calculate_pct_chance_pass_through_untargetted_square(CreaturePtr attacking_creature, CreaturePtr creature_in_tile) = 0;

  protected:
    AttackType attack_type;
};

using CombatTargetNumberCalculatorPtr = std::unique_ptr<CombatTargetNumberCalculator>;
