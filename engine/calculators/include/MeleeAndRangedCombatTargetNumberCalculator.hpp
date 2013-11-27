#pragma once
#include "CombatTargetNumberCalculator.hpp"

class MeleeAndRangedCombatTargetNumberCalculator : public CombatTargetNumberCalculator
{
  public:
    MeleeAndRangedCombatTargetNumberCalculator(AttackType attack_type);

    virtual int calculate(CreaturePtr attacking_creature, CreaturePtr attacked_creature) override;
};
