#pragma once
#include "MagicalCombatTargetNumberCalculator.hpp"

class WandsCombatTargetNumberCalculator : public MagicalCombatTargetNumberCalculator
{
  public:
    WandsCombatTargetNumberCalculator();

  protected:
    SkillType get_attacker_skill() const override;
};
