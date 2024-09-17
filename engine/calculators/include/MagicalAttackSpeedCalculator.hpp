#pragma once
#include "AttackSpeedCalculator.hpp"

class MagicalAttackSpeedCalculator : public AttackSpeedCalculator
{
  public:
    virtual ~MagicalAttackSpeedCalculator() = default;

    ActionCostValue calculate(CreaturePtr creature) override;
};

