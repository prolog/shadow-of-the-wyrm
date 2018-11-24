#pragma once
#include "AttackSpeedCalculator.hpp"

class RangedAttackSpeedCalculator : public AttackSpeedCalculator
{
  public:
    ActionCostValue calculate(CreaturePtr creature) override;
};
