#pragma once
#include "CombatTargetNumberCalculator.hpp"

class MagicalCombatTargetNumberCalculator : public CombatTargetNumberCalculator
{
  public:
    MagicalCombatTargetNumberCalculator();

    virtual int calculate(CreaturePtr attacking_creature, CreaturePtr attacked_creature) override;
    virtual int calculate_pct_chance_pass_through_untargetted_square(CreaturePtr attacking_creature, CreaturePtr creature_in_tile) override;
};
