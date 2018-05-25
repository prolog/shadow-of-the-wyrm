#pragma once
#include "AttackSpeedCalculator.hpp"

class NullAttackSpeedCalculator : public AttackSpeedCalculator
{
  public:
    ActionCostValue calculate(CreaturePtr creature) override;
};
