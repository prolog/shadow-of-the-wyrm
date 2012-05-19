#pragma once
#include "CombatTargetNumberCalculator.hpp"

class MagicalCombatTargetNumberCalculator : public CombatTargetNumberCalculator
{
  public:
    MagicalCombatTargetNumberCalculator();

    virtual int calculate(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
};
