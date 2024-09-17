#pragma once
#include "AttackSpeedCalculator.hpp"

class RangedAttackSpeedCalculator : public AttackSpeedCalculator
{
  public:
    virtual ~RangedAttackSpeedCalculator() = default;

    ActionCostValue calculate(CreaturePtr creature) override;
};
