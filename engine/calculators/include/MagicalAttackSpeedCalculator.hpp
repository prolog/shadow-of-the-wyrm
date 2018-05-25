#pragma once
#include "AttackSpeedCalculator.hpp"

class MagicalAttackSpeedCalculator : public AttackSpeedCalculator
{
  public:
    ActionCostValue calculate(CreaturePtr creature) override;
};

