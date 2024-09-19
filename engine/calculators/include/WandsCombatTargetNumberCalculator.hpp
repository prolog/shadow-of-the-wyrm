#pragma once
#include "MagicalCombatTargetNumberCalculator.hpp"

class WandsCombatTargetNumberCalculator : public MagicalCombatTargetNumberCalculator
{
  public:
    WandsCombatTargetNumberCalculator();
    virtual ~WandsCombatTargetNumberCalculator() = default;

  protected:
    SkillType get_attacker_skill() const override;
};
